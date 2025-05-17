/*
  ==============================================================================

    GramoVoice.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GramoVoice : public juce::Component, public juce::AudioProcessor, public juce::AudioSource
{
public:
    GramoVoice();
    ~GramoVoice() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;


    // Implement pure virtual methods from juce::AudioProcessor  
    const juce::String getName() const override { return "GramoVoice"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const juce::String& newName) override {}
    void getStateInformation(juce::MemoryBlock& destData) override {}
    void setStateInformation(const void* data, int sizeInBytes) override {}
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
	bool hasEditor() const override { return nullptr; }
	juce::AudioProcessorEditor* createEditor() override { return nullptr; }



private:

    float pitchShiftTarget; // Use for wow and flutter, instead of trombone slides
    float vibratoGain; // Use for wow and flutter

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoVoice)
};