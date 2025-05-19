/*
  ==============================================================================

    StylusEmulation.h
    Created: 17 May 2025 6:50:05pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class StylusEmulation  : public juce::Component, public juce::AudioSource
{
public:

    StylusEmulation();
    ~StylusEmulation() override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setVinyFilter(float frequency);
    void processPressureDifference(float pressureDiff);
    float getFilterOutput() const { return stylusFilterState[0]; }


private:

    float vinylTarget;
    float stylusOutput;
    float stylusFilterState[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StylusEmulation)
};
