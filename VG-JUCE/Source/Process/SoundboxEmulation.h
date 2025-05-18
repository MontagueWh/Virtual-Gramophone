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

    float configureVibrato(double sampleRate);

    void startAirShift(float amplitude, float rate = 0.1f);
    void stopAirShift(float rate = 0.1f);

    float getsoundboxPressure() const { return soundboxPressure; }
    float generateNoise() const;

    void setMaxPressure(float pressure);
    float getMaxPressure() const { return maxPressure; }
    void setNoiseGain(float gain);

private:

    // soundbox air parameters
    float soundboxPressure;
    float soundboxGain;
    float sounxboxTarget;
    float maxPressure;

    float noiseGain;

    float vibratoFrequency;
    float vibratoGain;
    float vibratoPhase;
    float vibratoEffect;
	float vibratoMix;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundboxEmulation)
};
