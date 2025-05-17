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
class StylusEmulation  : public juce::Component
{
public:

    StylusEmulation();
    ~StylusEmulation() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void addedNoiseSetup(juce::dsp::ProcessSpec& spec, double sampleRate, int samplesPerBlock);
    float excitationSetup();
    float stylusPressure(float inputSample);

private:

    float vinylTarget; // instead of lipTarget, in the context of a gramophone
	float maxPressure; // Use for stylus pressure

    // Noise Source for Stylus Vibration
    stk::Noise noiseSource;
    juce::dsp::IIR::Filter<float> noiseFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StylusEmulation)
};
