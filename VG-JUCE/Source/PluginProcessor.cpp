/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h" // Includes the header file for the plugin processor class.
#include "PluginEditor.h"    // Includes the header file for the plugin editor class.

constexpr float BP_FREQ = 2950.0f; // Defines a constant for the band-pass filter frequency.

//==============================================================================
// Constructor for the plugin processor class.
VirtualGramoAudioProcessor::VirtualGramoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties() // Initialises the audio processor with bus properties.
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::discreteChannels(MAX_CHANNELS), true) // Adds the number of input busses
#endif
        .withOutput("Output", juce::AudioChannelSet::discreteChannels(MAX_CHANNELS), true) // Adds the number of output busses
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParameters()) // Initialises the AudioProcessorValueTreeState for parameter management.
#endif
{
    gramoVoice();
}

VirtualGramoAudioProcessor::~VirtualGramoAudioProcessor()
{
    // Destructor for the plugin processor class. Cleans up resources if necessary.
}

//==============================================================================
// Returns the name of the plugin.
const juce::String VirtualGramoAudioProcessor::getName() const
{
    return JucePlugin_Name; // Uses the name defined in the JUCE plugin configuration.
}

// Determines if the plugin accepts MIDI input.
bool VirtualGramoAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true; // Returns true if the plugin is configured to accept MIDI input.
#else
    return false; // Returns false otherwise.
#endif
}

// Determines if the plugin produces MIDI output.
bool VirtualGramoAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true; // Returns true if the plugin is configured to produce MIDI output.
#else
    return false; // Returns false otherwise.
#endif
}

// Determines if the plugin is a MIDI effect.
bool VirtualGramoAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true; // Returns true if the plugin is a MIDI effect.
#else
    return false; // Returns false otherwise.
#endif
}

// Returns the tail length of the plugin in seconds.
double VirtualGramoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0; // No tail length is defined for this plugin.
}

// Returns the number of programs (presets) available in the plugin.
int VirtualGramoAudioProcessor::getNumPrograms()
{
    return 1; // At least one program is required, even if not implemented.
}

// Returns the index of the current program.
int VirtualGramoAudioProcessor::getCurrentProgram()
{
    return 0; // Only one program is available, so the index is always 0.
}

// Sets the current program (not implemented in this plugin).
void VirtualGramoAudioProcessor::setCurrentProgram(int /*index*/)
{
}

// Returns the name of the program at the given index (not implemented).
const juce::String VirtualGramoAudioProcessor::getProgramName(int /*index*/)
{
    return {}; // Returns an empty string.
}

// Changes the name of the program at the given index (not implemented).
void VirtualGramoAudioProcessor::changeProgramName(int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
// Prepares the plugin for playback by initialising DSP components.
void VirtualGramoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Sets up the processing specification for DSP components.
    juce::dsp::ProcessSpec spec = { sampleRate, static_cast<juce::uint32>(samplesPerBlock),
                                    static_cast<juce::uint32>(getMainBusNumOutputChannels()) };

    filterCount = getTotalNumInputChannels(); // Sets the number of filters to the number of input channels.
	filters.resize(filterCount); // Resizes the filter vector to match the number of channels.

    chorus.prepare(spec); // Prepares the chorus effect with the processing spec.
    mix.prepare(spec);    // Prepares the wet/dry mix processor.

    // Retrieves the initial frequency value from the parameter tree.
    float frequency = apvts.getRawParameterValue("TONE")->load();

    // Prepares and configures the band-pass filters for each channel.
	for (int i = 0; i < filterCount; ++i)
	{
		filters[i].prepare(spec); // Prepares each filter with the processing spec.
		filters[i].coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency, 6.0f); // Sets the filter coefficients.
	}
}

// Releases resources when playback stops.
void VirtualGramoAudioProcessor::releaseResources()
{
    // Frees up any resources or memory used during playback.

    
}

#ifndef JucePlugin_PreferredChannelConfigurations
// Checks if the given bus layout is supported by the plugin.
bool VirtualGramoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true; // MIDI effects support all layouts.
#else
    // Allow any valid output channel configuration
    const auto& outputSet = layouts.getMainOutputChannelSet();

    // Ensure the layout is valid and not empty
    if (outputSet.isDisabled())
        return false;

    // Ensures the input layout matches the output layout for non-synth plugins.
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true; // Layout is supported.
#endif
}
#endif

// Processes audio and MIDI data for each block of samples.
void VirtualGramoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals; // Ensures denormalized numbers are handled correctly.
    auto totalNumInputChannels = getTotalNumInputChannels(); // Gets the number of input channels.
    auto totalNumOutputChannels = getTotalNumOutputChannels(); // Gets the number of output channels.

    // Clears any output channels that don't have corresponding input channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    mix.pushDrySamples(buffer); // Pushes the dry signal into the mix processor.

    // Processes each sample in the buffer.
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {            
            // Retrieves parameter values for compression and tone.
            float threshold = apvts.getRawParameterValue("COMPRESS")->load();
            float frequency = apvts.getRawParameterValue("TONE")->load();

            // Apply compression
            float in = buffer.getReadPointer(channel)[sample];
            if (in >= threshold)
                buffer.getWritePointer(channel)[sample] = (in / 4) + (3 * threshold / 4);
            else if (in <= -threshold)
                buffer.getWritePointer(channel)[sample] = (in / 4) - (3 * threshold / 4);

            // Applies makeup gain to the signal.
            *buffer.getWritePointer(channel, sample) *= 5.0f - (11.0f * threshold * threshold);

            // Applies a band-pass filter to the signal for each channel
			for (int i = 0; i < filterCount; ++i)
			{
				filters[i].coefficients = *juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), frequency, 2.7f);
				buffer.getWritePointer(channel)[sample] = filters[i].processSample(buffer.getReadPointer(channel)[sample]);
			}
        }
    }

    // Wraps the buffer in an AudioBlock for further processing.
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);

    // Configures and processes the chorus effect.
    chorus.setRate(apvts.getRawParameterValue("VIBRATO_RATE")->load());
    chorus.setDepth(apvts.getRawParameterValue("VIBRATO")->load());
    chorus.setCentreDelay(1.0f);
    chorus.setFeedback(0.0f);
    chorus.setMix(1.0f);
    chorus.process(contextToUse);

    // Configures and applies the wet/dry mix.
    mix.setWetMixProportion(1.0f - apvts.getRawParameterValue("MIX")->load());
    mix.mixWetSamples(block);
}

//==============================================================================
// Indicates whether the plugin has an editor.
bool VirtualGramoAudioProcessor::hasEditor() const
{
    return true; // Returns true to indicate the plugin has a GUI editor.
}

// Creates and returns the plugin editor.
juce::AudioProcessorEditor* VirtualGramoAudioProcessor::createEditor()
{
    return new VirtualGramoAudioProcessorEditor(*this); // Creates an instance of the editor.
}

//==============================================================================
// Saves the plugin's state to a memory block.
void VirtualGramoAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState(); // Copies the current state of the parameters.
    std::unique_ptr<juce::XmlElement> xml(state.createXml()); // Converts the state to XML.
    copyXmlToBinary(*xml, destData); // Saves the XML to the memory block.
}

// Restores the plugin's state from a memory block.
void VirtualGramoAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes)); // Reads XML from the memory block.

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType())) // Checks if the XML tag matches the parameter tree type.
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState)); // Restores the state from the XML.
}

// Creates and returns the parameter layout for the plugin.
juce::AudioProcessorValueTreeState::ParameterLayout VirtualGramoAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters; // Stores the parameters.

    // Adds parameters for compression, vibrato, tone, and mix.
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRESS", "Compress", 0.04f, 0.45f, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("VIBRATO", "Vibrato", 0.0f, 0.33f, 0.01f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("VIBRATO_RATE", "Rate", 0.5f, 4.0f, 2.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("TONE", "Tone", 320.1f, 4700.0f, 2000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 0.5f, 0.0f));
    return { parameters.begin(), parameters.end() }; // Returns the parameter layout.
}

//==============================================================================
// Factory function to create a new instance of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualGramoAudioProcessor(); // Creates and returns a new instance of the processor.
}
