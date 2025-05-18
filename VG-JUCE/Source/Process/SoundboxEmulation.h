/*
  ==============================================================================

    SoundboxEmulation.h
    Created: 18 May 2025 12:17:28pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <numbers>

//==============================================================================
/*
*/
class SoundboxEmulation : public juce::Component, public juce::AudioSource
{
public:
    SoundboxEmulation();
    ~SoundboxEmulation() override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
	void releaseResources() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setVibratoFrequency(float frequency);
    void setVibratoGain(float gain);
    float configureVibrato(double sampleRate);

private:

    // soundbox air parameters
    float soundboxPressure;
    float soundboxGain;
    float sounxboxTarget;

    float vibratoFrequency;
    float vibratoGain;
    float vibratoPhase;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundboxEmulation)
};
