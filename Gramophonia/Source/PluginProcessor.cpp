/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr float BP_FREQ = 2950.0f;

//==============================================================================
VirtualGramoAudioProcessor::VirtualGramoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
#endif
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                          ),
      apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
}

VirtualGramoAudioProcessor::~VirtualGramoAudioProcessor()
{
}

//==============================================================================
const juce::String VirtualGramoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualGramoAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool VirtualGramoAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool VirtualGramoAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double VirtualGramoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualGramoAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualGramoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualGramoAudioProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String VirtualGramoAudioProcessor::getProgramName (int /*index*/)
{
    return {};
}

void VirtualGramoAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
void VirtualGramoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec = { sampleRate, static_cast<juce::uint32>(samplesPerBlock), 
                                    static_cast<juce::uint32>(getMainBusNumOutputChannels()) };

    chorus_.prepare (spec);

    float frequency = apvts.getRawParameterValue ("TONE")->load();
    filter_.prepare (spec);
    filter_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency, 6.0f);

    // Initialize vinyl crackle
    vinylCrackle_.setSampleRate(sampleRate);
    vinylCrackle_.reset();
}

void VirtualGramoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualGramoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // Allow any number of channels for input and output
    auto inputChannels = layouts.getMainInputChannelSet().size();
    auto outputChannels = layouts.getMainOutputChannelSet().size();

    // (Optional) Log the channel count for debugging
    DBG("Input channels available: " << inputChannels);
    DBG("Output channels available: " << outputChannels);

#if ! JucePlugin_IsSynth
    // Ensure input and output layouts match (if not a synth)
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    // Accept all layouts (with matching in/out if required)
    return true;
#endif
}
#endif

// Modified processBlock method to remove compression
void VirtualGramoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Load parameters once per processing block
    float fFrequencyControl = apvts.getRawParameterValue("TONE")->load();
    float fWowAmount = apvts.getRawParameterValue("WOW")->load();
    float fFlutterAmount = apvts.getRawParameterValue("FLUTTER")->load(); // Main flutter control
    float fVibratoDepth = apvts.getRawParameterValue("VIBRATO_DEPTH")->load(); // Controlled by flutter knob
    float fVibratoRate = apvts.getRawParameterValue("VIBRATO_RATE")->load(); // Controlled by flutter knob
    float fMixControl = apvts.getRawParameterValue("MIX")->load();
    float fInGain = apvts.getRawParameterValue("IN_GAIN")->load();
    float fOutGain = apvts.getRawParameterValue("OUT_GAIN")->load();

    // Apply input gain to all channels in one loop
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= fInGain;
        }
    }

    // If mix is 0, skip effect processing and just apply output gain
    if (fMixControl <= 0.0f)
    {
        // Apply output gain
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] *= fOutGain;
            }
        }
        return;
    }

    // Update filter coefficients
    filter_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), fFrequencyControl + 10.0f, 2.7f);

    // Create a mono wet buffer from the first channel
    juce::AudioBuffer<float> wetBuffer(1, buffer.getNumSamples());
    wetBuffer.copyFrom(0, 0, buffer, 0, 0, buffer.getNumSamples());

    // Process mono wet buffer with all effects
    float* wetData = wetBuffer.getWritePointer(0);
    for (int sample = 0; sample < wetBuffer.getNumSamples(); ++sample)
    {
        // Apply filter (using filter_ch1_ for the mono signal)
        wetData[sample] = filter_.processSample(wetData[sample]);
        
        // Apply wow and flutter effect 
        // Use flutter amount for both the wow-and-flutter module and for vibrato
        if (fWowAmount > 0.0f || fFlutterAmount > 0.0f)
            wetData[sample] = wowAndFlutter_.processSample(wetData[sample], fWowAmount, fFlutterAmount, getSampleRate());
    }
    
    // Apply chorus to wet buffer - which is our vibrato effect
    // Vibrato rate and depth are already set by the flutter control in the slider callback
    auto wetBlock = juce::dsp::AudioBlock<float>(wetBuffer);
    auto wetContext = juce::dsp::ProcessContextReplacing<float>(wetBlock);

    chorus_.setRate(fVibratoRate);
    chorus_.setDepth(fVibratoDepth);
    chorus_.setCentreDelay(1.0f);
    chorus_.setFeedback(0.0f);
    chorus_.setMix(1.0f);

    chorus_.process(wetContext);
    
    // Apply vinyl crackle effects
    float fCrackleAmount = apvts.getRawParameterValue("CRACKLE")->load();
    float fDustAmount = apvts.getRawParameterValue("DUST")->load();
    float fDustIntensity = apvts.getRawParameterValue("DUST_INTENSITY")->load();

    if (fCrackleAmount > 0.0f || fDustAmount > 0.0f)
    {
        for (int sample = 0; sample < wetBuffer.getNumSamples(); ++sample)
        {
            // Apply the vinyl crackle and dust effects
            wetData[sample] = vinylCrackle_.process(wetData[sample], 
                                                   fCrackleAmount, 
                                                   fDustIntensity, 
                                                   false); // Don't use built-in wow/flutter
        }
    }
    
    // Mix dry and wet signals (mono wet to all dry channels)
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Mix dry channel with mono wet signal and apply output gain in one step
            channelData[sample] = (channelData[sample] * (1.0f - fMixControl) + 
                              wetData[sample] * fMixControl) * fOutGain;
        }
    }
}

//==============================================================================
bool VirtualGramoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VirtualGramoAudioProcessor::createEditor()
{
    return new VirtualGramoUIEditor (*this);
}

//==============================================================================
void VirtualGramoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualGramoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout VirtualGramoAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("IN_GAIN", "Input Gain", 0.0f, 2.0f, 1.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("OUT_GAIN", "Output Gain", 0.0f, 2.0f, 1.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_DEPTH", "Vibrato Depth", 0.0f, 0.33f, 0.01f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_RATE", "Vibrato Rate", 0.5f, 4.0f, 2.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE", "Tone", 320.1f, 4700.0f, 2000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("WOW", "Wow", 0.0f, 1.0f, 0.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("FLUTTER", "Flutter", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("CRACKLE", "Crackle", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DUST", "Dust", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DUST_INTENSITY", "Dust Intensity", 0.0f, 0.7f, 0.0f));
    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualGramoAudioProcessor();
}
