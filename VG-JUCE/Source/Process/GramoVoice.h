/*
  ==============================================================================

    GramoVoice.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <../Source/Libs/stk/include/Brass.h>

//==============================================================================
/*
*/
class GramoVoice : public juce::Component, public stk::Instrmnt, public juce::AudioProcessor, juce::AudioSource
{
public:
    GramoVoice();
    ~GramoVoice() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override; // Prepares the processor for playback by initialising resources
    void releaseResources() override; // Releases resources when playback stops.
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override; // Processes audio and MIDI data for each block of samples

    float gramoPressure();
	void setHornLength(float length);
	void setHornDiameter(float diameter);
	void setHornStiffness(float stiffness);
	void handleImpulseResponse(double sampleRate, int samplesPerBlock);

    void setStylusFilterCutoff(float cutoff);
    void setNonLinearity(float amount);
    void setNoiseLevel(float level);

protected:

    stk::DelayA   delayLine;
    stk::BiQuad   stylusFilter;
    stk::PoleZero dcBlock;
    stk::ADSR     adsr;
    stk::SineWave vibrato;

    float lipTarget;
    float slideTarget;
    float vibratoGain;
    float maxPressure;

private:

    stk::Brass gramoHorn;

	juce::dsp::Convolution convolution; // Convolution processor for impulse response
	juce::AudioBuffer<float> impulseResponse; // Buffer for the impulse response
	juce::AudioFormatManager audioFormatManager; // Manages audio file formats

    float startAmp = 0.8f; // Initial breath intensity
    float attackRate = 20.f; // Rate of pressure increase

    float hornLength /*= 1.37f*/; // Length of the horn in meters
    float stylusFilterCutoff;
    float nonLinearityAmount;
	float noiseLevel;
    float hornDiameter;
	float hornStiffness;

    float sampleRateVari;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GramoVoice)
};
