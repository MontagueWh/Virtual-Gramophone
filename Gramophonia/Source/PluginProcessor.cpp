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
                          .withInput ("Input", juce::AudioChannelSet::mono(), true)
#endif
                          .withOutput ("Output", juce::AudioChannelSet::mono(), true)
#endif
                          ),
      apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    // Make sure we support dynamic channel configurations
    setRateAndBufferSizeDetails(44100.0, 512);
    
    // Initialize all possible buses to handle flexible channel configurations
    bool success = true;
    
#if ! JucePlugin_IsSynth && ! JucePlugin_IsMidiEffect
    // For non-synth plugins, we need to ensure we can handle the same channel 
    // configurations on both input and output
    success &= setBusesLayout(getBusesLayout());
#endif
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
    float fFlutterAmount = apvts.getRawParameterValue("FLUTTER")->load();
    float fMixControl = apvts.getRawParameterValue("MIX")->load();
    float fInGain = apvts.getRawParameterValue("IN_GAIN")->load();
    float fOutGain = apvts.getRawParameterValue("OUT_GAIN")->load();
    float fVinylArtefacts = apvts.getRawParameterValue("VINYL_ARTIFACTS")->load();

    // Update individual vinyl artefact parameters based on master control
    constexpr float CRACKLE_SCALE = 1.0f;         // 100% of vinyl value
    constexpr float DUST_SCALE = 0.8f;            // 80% of vinyl value
    constexpr float DUST_INTENSITY_SCALE = 0.85f; // 85% of vinyl value
    
    fCrackleAmount = fVinylArtefacts * CRACKLE_SCALE;        // Set crackle amount
    fDustAmount = fVinylArtefacts * DUST_SCALE;              // Set dust amount (used internally)
    fDustIntensity = fVinylArtefacts * DUST_INTENSITY_SCALE; // Set dust intensity

    // If mix is 0, apply input and output gain in a single channel/sample loop and return
    if (fMixControl <= 0.0f)
    {
        const float combinedGain = fInGain * fOutGain;
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] *= combinedGain;
            }
        }
        return;
    }

    // Update filter coefficients for tone control
    filter_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
        getSampleRate(), fFrequencyControl + 10.0f, 2.7f);
    
    // Configure chorus if needed
    bool needsChorusProcessing = (fFlutterAmount > 0.0f);
    if (needsChorusProcessing)
    {
        chorus_.setRate(fFlutterAmount);
        chorus_.setDepth(fFlutterAmount);
        chorus_.setCentreDelay(1.0f);
        chorus_.setFeedback(0.0f);
        chorus_.setMix(1.0f);
    }

    // Process each channel
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        
        // Create a buffer for dry samples to mix later
        juce::AudioBuffer<float> dryBuffer;
        dryBuffer.setSize(1, buffer.getNumSamples());
        
        // Process wet signal
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            dryBuffer.setSample(0, i, channelData[i] * fInGain);

            // Start with input-gained sample
            float wetSample = dryBuffer.getSample(0, i);
            
            // Apply vinyl artefacts if enabled
            if (fVinylArtefacts > 0.0f)
            {
                wetSample = vinylCrackle_.process(
                    wetSample,
                    fCrackleAmount,
                    fDustIntensity,
                    false
                );
            }
            
            // Apply wow and flutter if enabled
            if (fWowAmount > 0.0f || fFlutterAmount > 0.0f)
            {
                wetSample = wowAndFlutter_.processSample(
                    wetSample,
                    fWowAmount,
                    fFlutterAmount,
                    getSampleRate()
                );
            }
            
            wetSample = filter_.processSample(wetSample);

            // Store processed wet sample back to main buffer
            channelData[i] = wetSample;
        }
        
        // Process chorus if needed (as a block effect)
        if (needsChorusProcessing)
        {
            juce::dsp::AudioBlock<float> block(buffer);
            juce::dsp::AudioBlock<float> channelBlock = block.getSingleChannelBlock(channel);
            juce::dsp::ProcessContextReplacing<float> context(channelBlock);
            chorus_.process(context);
        }
        
        // Apply mix dry/wet signals
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float drySample = dryBuffer.getSample(0, i);
            float wetSample = channelData[i];

            channelData[i] = (drySample * (1.0f - fMixControl) +
                wetSample * fMixControl) * fOutGain;
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
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE", "Tone", 320.1f, 4700.0f, 2000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("WOW", "Wow", 0.0f, 1.0f, 0.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("FLUTTER", "Flutter", 0.0f, 1.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("VINYL_ARTIFACTS", "Vinyl Artefacts", 0.0f, 1.0f, 0.0f));
    
    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualGramoAudioProcessor();
}
