/*
  ==============================================================================

    GramoVoice.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StylusEmulation.h"
#include "HornEmulation.h"
#include "CabinetEmulation.h"

//==============================================================================
/*
*/
class GramoVoice : public juce::Component, public juce::AudioSource, public juce::Slider::Listener
{
public:
    GramoVoice();
    ~GramoVoice() override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void paint(juce::Graphics&) override;
	void sliderValueChanged(juce::Slider* slider) override;

private:

    StylusEmulation gramoStylus;
	hornEmulation gramoHorn;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoVoice)
};