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
    float treshold = apvts.getRawParameterValue("COMPRESS")->load();
    float frequency = apvts.getRawParameterValue("TONE")->load();
    float fWowAmount = apvts.getRawParameterValue("WOW")->load();
    float fFlutterAmount = apvts.getRawParameterValue("FLUTTER")->load();
    float mixValue = apvts.getRawParameterValue("MIX")->load(); // Get mix value directly

    // Update filter coefficients once per processing block
    filter_ch1_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), frequency + 10.0f, 2.7f);
    filter_ch2_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), frequency - 10.0f, 2.73f);

    // Calculate makeup gain once
    float makeupGain = 5.0f - (11.0f * treshold * treshold);

    // Process all samples in a single loop
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        // Input and output variables per sample
        float fIn[2] = { 0.0f, 0.0f };
        float fOut[2] = { 0.0f, 0.0f };
        float fDry[2] = { 0.0f, 0.0f };
        float fWet[2] = { 0.0f, 0.0f };

        // Read input samples
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
            fIn[channel] = buffer.getReadPointer(channel)[sample];

        // Store dry signal (unprocessed)
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
            fDry[channel] = fIn[channel];

        // Calculate mono mix for this sample (used only for wet signal)
        float fMonoMix = 0.0f;
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
            fMonoMix += fIn[channel];

        if (totalNumInputChannels > 0)
            fMonoMix /= totalNumInputChannels;

        // Process wet signal (with mono mix if needed)
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
        {
            // Start with input sample
            fWet[channel] = fIn[channel];

            // Compression
            if (fWet[channel] >= treshold)
                fWet[channel] = (fWet[channel] / 4) + (3 * treshold / 4);
            else if (fWet[channel] <= -treshold)
                fWet[channel] = (fWet[channel] / 4) - (3 * treshold / 4);

            // Apply makeup gain
            fWet[channel] *= makeupGain;

            // Apply filter
            if (channel == 0)
                fWet[channel] = filter_ch1_.processSample(fWet[channel]);
            else if (channel == 1)
                fWet[channel] = filter_ch2_.processSample(fWet[channel]);

            // Apply wow and flutter effect
            if (fWowAmount > 0.0f || fFlutterAmount > 0.0f)
                fWet[channel] = wowAndFlutter_.processSample(fWet[channel], fWowAmount, fFlutterAmount, getSampleRate());
        }

        // Mix dry and wet signals directly according to the mix parameter
        // mixValue ranges from 0.0 (fully wet) to 0.5 (equal mix)
        for (int channel = 0; channel < juce::jmin(totalNumInputChannels, 2); ++channel)
        {
            // Direct mixing of dry and wet signals
            fOut[channel] = (fDry[channel] * mixValue) + (fWet[channel] * (1.0f - mixValue));
            buffer.getWritePointer(channel)[sample] = fOut[channel];
        }
    }

    // Process with chorus effect
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);

    chorus_.setRate(apvts.getRawParameterValue("VIBRATO_RATE")->load());
    chorus_.setDepth(apvts.getRawParameterValue("VIBRATO_DEPTH")->load());
    chorus_.setCentreDelay(1.0f);
    chorus_.setFeedback(0.0f);
    chorus_.setMix(1.0f);

    chorus_.process(contextToUse);

    // No longer need to call mix_.mixWetSamples since we handle mixing directly
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

    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("COMPRESS", "Compress", 0.04f, 0.45f, 0.1f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_DEPTH", "Vibrato Depth", 0.0f, 0.33f, 0.01f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("VIBRATO_RATE", "Vibrato Rate", 0.5f, 4.0f, 2.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE", "Tone", 320.1f, 4700.0f, 2000.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("MIX", "Mix", 0.0f, 0.5f, 0.0f));
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
