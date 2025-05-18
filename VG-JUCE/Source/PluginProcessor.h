/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once // Ensures the file is included only once during compilation.

#include <JuceHeader.h> // Includes the JUCE framework header file.
#include "Process/GramoVoice.h" // Includes the GramoVoice class header file for audio processing.

static const int MAX_CHANNELS = 64;

//==============================================================================
/**
 * The main audio processor class for the plugin.
 * Inherits from juce::AudioProcessor and implements its virtual methods.
 */
class VirtualGramoAudioProcessor : public juce::AudioProcessor
{
public:

    //==============================================================================
    VirtualGramoAudioProcessor(); // Constructor for the audio processor.
    ~VirtualGramoAudioProcessor() override; // Destructor for the audio processor.

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override; // Prepares the processor for playback by initialising resources
    
    void releaseResources() override; // Releases resources when playback stops.

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override; // Checks if the given bus layout is supported by the plugin
#endif
    
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override; // Processes audio and MIDI data for each block of samples

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override; // Creates and returns the plugin editor (GUI)

    bool hasEditor() const override; // Indicates whether the plugin has an editor (GUI)

    //==============================================================================
    const juce::String getName() const override; // Returns the name of the plugin
    
    bool acceptsMidi() const override; // Determines if the plugin accepts MIDI input
	bool producesMidi() const override; // Determines if the plugin produces MIDI output
    bool isMidiEffect() const override; // Determines if the plugin is a MIDI effect

    double getTailLengthSeconds() const override; // Returns the tail length of the plugin in seconds

    //==============================================================================
    int getNumPrograms() override; // Returns the number of programs (presets) available in the plugin
    int getCurrentProgram() override; // Returns the index of the current program
    void setCurrentProgram(int index) override; // Sets the current program (preset) by index.

    const juce::String getProgramName(int index) override; // Returns the name of the program (preset) at the given index
    void changeProgramName(int index, const juce::String& newName) override; // Changes the name of the program (preset) at the given index

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override; // Saves the plugin's state to a memory block

    void setStateInformation(const void* data, int sizeInBytes) override; // Restores the plugin's state from a memory block

    juce::AudioProcessorValueTreeState apvts; // Manages the plugin's parameters using a value tree state.


    void PrepareAdditionalEffects(juce::dsp::ProcessSpec& spec, double sampleRate);
    void ProcessChorusEffect(juce::dsp::ProcessContextReplacing<float>& contextToUse);
    void ProcessCompressionAndTone(juce::AudioSampleBuffer& buffer, int channel, int sample);

private:

	//==============================================================================
    // Creates and returns the parameter layout for the plugin.
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    // DSP components used in the plugin.
    juce::dsp::Chorus<float> chorus; // Chorus effect processor.
    int filterCount;
    std::vector<juce::dsp::IIR::Filter<float>> filters;
    juce::dsp::DryWetMixer<float> mix; // Wet/dry mix processor.

	GramoVoice gramoVoice; // Instance of the GramoVoice class for audio processing.

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualGramoAudioProcessor)
        // Macro to prevent copying and enable leak detection for the class.
};