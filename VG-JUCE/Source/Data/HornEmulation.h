/*
  ==============================================================================

    HornEmulation.h
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
class HornEmulation : public juce::Component, public stk::Instrmnt, public juce::AudioSource
{
public:

    HornEmulation();
    ~HornEmulation() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

	// Stk pure virtual methods
    void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;
    void noteOff(stk::StkFloat amplitude) override;
    stk::StkFloat tick(unsigned int channel = 0) override;
    stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;

    int selectConvolutionIndex(float amplitude, float adsrValue);
    float freqSetup();
    void setPitchShift(float position);

    stk::ADSR adsr;

    // Brass synthesis variables
    stk::Brass brassHorn;
    float frequency;

    float rmsLevel;
    float rmsAlpha;


    class WaveguideSynthesis : public juce::Component, juce::AudioSource
    {
    public:

        WaveguideSynthesis();
        ~WaveguideSynthesis() override;

		void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void setupBodyResonances();
        void handleImpulseResponse(double sampleRate, int samplesPerBlock);

        juce::AudioFormatReader* reader;
        juce::AudioFormatManager audioFormatManager;
        juce::AudioBuffer<float> iRs[11];
        juce::File irFiles[11];

    private:


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveguideSynthesis)
    };

private:

    float pitchShiftTarget;
    float maxDelay;

    stk::Delay delayLine[2048];
    int delayLength;
    int readPtr;
    int writePtr;

    float outputGain;
    float inputGain;

    float lowestFrequency = 8.0f;

    StylusEmulation gramoStylus;
	WaveguideSynthesis waveguideSynthesis;

    juce::dsp::Convolution convolution[11];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HornEmulation)
};

