/*
  ==============================================================================

    brassSynthesis.h
    Created: 17 May 2025 6:50:39pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StylusEmulation.h"

//==============================================================================
/*
*/
class brassSynthesis : public juce::Component, public stk::Instrmnt, public juce::AudioSource
{
public:

    brassSynthesis();
    ~brassSynthesis() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

	// Stk pure virtual methods
    void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
    void noteOff(stk::StkFloat amplitude) override;
    stk::StkFloat tick(unsigned int channel = 0) override;
    stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

    void updateHornParameters();

    // Brass synthesis variables
    stk::Brass brassHorn;
    float frequency;
    void setSlide(float position);


    class waveguideSynthesis : public juce::Component, juce::AudioSource
    {
    public:

        waveguideSynthesis();
        ~waveguideSynthesis() override;

		void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void setupBodyResonances();
        void handleImpulseResponse(double sampleRate, int samplesPerBlock);

        // Waveguide synthesis variables
        stk::ADSR adsr;
        juce::dsp::Convolution convolution[11];

    private:

        juce::AudioFormatManager audioFormatManager;
        juce::AudioBuffer<float> iRs[11];

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(waveguideSynthesis)
    };

private:

    float slideTarget;
    float maxDelay;

    stk::Delay delayLine[2048];
    int delayLength;
    int readPtr;
    int writePtr;

    float sampleRate;
    float outputGain;
    float inputGain;
    float dryWetMix;

    float brassMixLevel;

    StylusEmulation gramoStylus;
	waveguideSynthesis waveguideSynthesis;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (brassSynthesis)
};

