/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once // Ensures the file is included only once during compilation.

#include <JuceHeader.h> // Includes the JUCE framework header file.
#include <stk/Brass.h> // Includes the STK Brass instrument header file.

//==============================================================================
/**
 * The main audio processor class for the plugin.
 * Inherits from juce::AudioProcessor and implements its virtual methods.
 */
class GramophonyAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    GramophonyAudioProcessor(); // Constructor for the audio processor.
    ~GramophonyAudioProcessor() override; // Destructor for the audio processor.

    //==============================================================================
    // Prepares the processor for playback by initializing resources.
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    // Releases resources when playback stops.
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    // Checks if the given bus layout is supported by the plugin.
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    // Processes audio and MIDI data for each block of samples.
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    // Creates and returns the plugin editor (GUI).
    juce::AudioProcessorEditor* createEditor() override;

    // Indicates whether the plugin has an editor (GUI).
    bool hasEditor() const override;

    //==============================================================================
    // Returns the name of the plugin.
    const juce::String getName() const override;

    // Determines if the plugin accepts MIDI input.
    bool acceptsMidi() const override;

    // Determines if the plugin produces MIDI output.
    bool producesMidi() const override;

    // Determines if the plugin is a MIDI effect.
    bool isMidiEffect() const override;

    // Returns the tail length of the plugin in seconds.
    double getTailLengthSeconds() const override;

    //==============================================================================
    // Returns the number of programs (presets) available in the plugin.
    int getNumPrograms() override;

    // Returns the index of the current program.
    int getCurrentProgram() override;

    // Sets the current program (preset) by index.
    void setCurrentProgram(int index) override;

    // Returns the name of the program (preset) at the given index.
    const juce::String getProgramName(int index) override;

    // Changes the name of the program (preset) at the given index.
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    // Saves the plugin's state to a memory block.
    void getStateInformation(juce::MemoryBlock& destData) override;

    // Restores the plugin's state from a memory block.
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Manages the plugin's parameters using a value tree state.
    juce::AudioProcessorValueTreeState apvts;

private:
    // Creates and returns the parameter layout for the plugin.
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    // DSP components used in the plugin.
    juce::dsp::Chorus<float> chorus_; // Chorus effect processor.
    juce::dsp::IIR::Filter<float> filter_ch1_; // Band-pass filter for channel 1.
    juce::dsp::IIR::Filter<float> filter_ch2_; // Band-pass filter for channel 2.
    juce::dsp::DryWetMixer<float> mix_; // Wet/dry mix processor.

    Brass GramoHorn;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramophonyAudioProcessor)
        // Macro to prevent copying and enable leak detection for the class.
};