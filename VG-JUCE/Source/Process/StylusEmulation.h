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

    void addedNoiseSetup(juce::dsp::ProcessSpec& spec, double sampleRate, int samplesPerBlock);
    float stylusPressure(float inputSample);

    float maxPressure; // Use for stylus pressure
    stk::SineWave vibrato;
    stk::BiQuad stylusFilter;

private:

    float vinylTarget; // instead of lipTarget, in the context of a gramophone

    // Noise Source for Stylus Vibration
    stk::Noise noiseSource;
    juce::dsp::IIR::Filter<float> noiseFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StylusEmulation)
};
