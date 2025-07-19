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

    mix_.prepare (spec);

    float frequency = apvts.getRawParameterValue ("TONE")->load();
    filter_ch1_.prepare (spec);
    filter_ch1_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass (sampleRate, frequency, 6.0f);

    filter_ch2_.prepare (spec);
    filter_ch2_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass (sampleRate, frequency, 6.0f);
}

void VirtualGramoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualGramoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void VirtualGramoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Load parameters once per processing block
    float fThresholdControl = apvts.getRawParameterValue("COMPRESS")->load();
    float fFrequencyControl = apvts.getRawParameterValue("TONE")->load();
    float fWowAmount = apvts.getRawParameterValue("WOW")->load();
    float fFlutterAmount = apvts.getRawParameterValue("FLUTTER")->load();
    float fMixControl = apvts.getRawParameterValue("MIX")->load();
    
    // Load gain parameters
    float fInGain = apvts.getRawParameterValue("IN_GAIN")->load();
    float fOutGain = apvts.getRawParameterValue("OUT_GAIN")->load();

    // Apply input gain at the beginning of processing
    if (fInGain != 1.0f)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] *= fInGain;
            }
        }
    }

    // Update filter coefficients once per processing block
    filter_ch1_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), fFrequencyControl + 10.0f, 2.7f);
    filter_ch2_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), fFrequencyControl - 10.0f, 2.73f);

    // Calculate makeup gain once
    float makeupGain = 5.0f - (11.0f * fThresholdControl * fThresholdControl);

    // Create a temporary buffer for wet signal processing if mix is not 0
    juce::AudioBuffer<float> wetBuffer;
    if (fMixControl > 0.0f)
    {
        wetBuffer.makeCopyOf(buffer);
        
        // Process wet buffer sample by sample
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
        {
            float* wetData = wetBuffer.getWritePointer(channel);
            
            for (int sample = 0; sample < wetBuffer.getNumSamples(); ++sample)
            {
                // Compression
                if (wetData[sample] >= fThresholdControl)
                    wetData[sample] = (wetData[sample] / 4) + (3 * fThresholdControl / 4);
                else if (wetData[sample] <= -fThresholdControl)
                    wetData[sample] = (wetData[sample] / 4) - (3 * fThresholdControl / 4);
                
                // Apply makeup gain
                wetData[sample] *= makeupGain;
                
                // Apply filter
                if (channel == 0)
                    wetData[sample] = filter_ch1_.processSample(wetData[sample]);
                else if (channel == 1)
                    wetData[sample] = filter_ch2_.processSample(wetData[sample]);
                
                // Apply wow and flutter effect
                if (fWowAmount > 0.0f || fFlutterAmount > 0.0f)
                    wetData[sample] = wowAndFlutter_.processSample(wetData[sample], fWowAmount, fFlutterAmount, getSampleRate());
            }
        }
        
        // Apply chorus to wet buffer only
        auto wetBlock = juce::dsp::AudioBlock<float>(wetBuffer);
        auto wetContext = juce::dsp::ProcessContextReplacing<float>(wetBlock);

        chorus_.setRate(apvts.getRawParameterValue("VIBRATO_RATE")->load());
        chorus_.setDepth(apvts.getRawParameterValue("VIBRATO_DEPTH")->load());
        chorus_.setCentreDelay(1.0f);
        chorus_.setFeedback(0.0f);
        chorus_.setMix(1.0f);

        chorus_.process(wetContext);
        
        // Mix dry (original buffer) and wet signals
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
        {
            float* fDry = buffer.getWritePointer(channel);
            float* fWet = wetBuffer.getWritePointer(channel);
            
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                fDry[sample] = fDry[sample] * (1.0f - fMixControl) + fWet[sample] * fMixControl;
            }
        }
    }
    
    // Apply output gain at the end of processing
    if (fOutGain != 1.0f)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] *= fOutGain;
            }
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
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("COMPRESS", "Compress", 0.04f, 0.45f, 0.1f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_DEPTH", "Vibrato Depth", 0.0f, 0.33f, 0.01f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_RATE", "Vibrato Rate", 0.5f, 4.0f, 2.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE", "Tone", 320.1f, 4700.0f, 2000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.0f));
    // Add wow and flutter parameters
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("WOW", "Wow", 0.0f, 1.0f, 0.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("FLUTTER", "Flutter", 0.0f, 1.0f, 0.0f));
    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualGramoAudioProcessor();
}
