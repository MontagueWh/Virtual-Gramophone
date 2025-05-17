/*
  ==============================================================================

    HornEmulation.h
    Created: 17 May 2025 6:50:39pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <../Source/Libs/stk_wrapper/stk/include/Brass.h>

//==============================================================================
/*
*/
class HornEmulation  : public juce::Component, public stk::Instrmnt, juce::AudioSource
{
public:

    HornEmulation();
    ~HornEmulation() override;

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	// Stk pure virtual methods
    void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
    void noteOff(stk::StkFloat amplitude) override;
    stk::StkFloat tick(unsigned int channel = 0) override;
    stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

    void setupBodyResonance();
    void handleImpulseResponse(double sampleRate, int samplesPerBlock);
    void updateHornParameters();

    // Waveguide synthesis variables
    stk::ADSR adsr;
    //stk::DelayA delayLine;

    // Brass synthesis variables
    stk::Brass brassHorn;
    float frequency;
    bool noteOn;

private:

    //stk::PoleZero dcBlock;

    // Bandwidth Limiting
    juce::dsp::IIR::Filter<float> lowPassFilter;

    float brassMixLevel;

    //juce::AudioFormatManager audioFormatManager;
    juce::AudioBuffer<float> iRs[11];
    juce::dsp::Convolution convolution[11];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HornEmulation)
};
