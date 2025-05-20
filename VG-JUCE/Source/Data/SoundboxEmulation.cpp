/*
  ==============================================================================

    SoundboxEmulation.cpp
    Created: 18 May 2025 12:17:28pm
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SoundboxEmulation.h"

//==============================================================================
SoundboxEmulation::SoundboxEmulation()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    vibratoFrequency = 5.925f;
    vibratoGain = 0.1f;
    vibratoPhase = 0.0f;

    maxPressure = 0.05f;
    soundboxPressure = 0.0f;
    soundboxGain = 0.0f;
    noiseGain = 0.2f;
}

SoundboxEmulation::~SoundboxEmulation()
{
}

void SoundboxEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    vibratoEffect = configureVibrato(sampleRate);
}

void SoundboxEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.

    //vibratoMix = bufferToFill.buffer->

        // Update breath pressure
    if (soundboxPressure < soundboxGain)
        soundboxPressure += 0.001f;
    if (soundboxPressure > soundboxGain)
        soundboxPressure = soundboxGain;
}

void SoundboxEmulation::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.

    vibratoPhase = 0.0f;

	soundboxPressure = 0.0f;
}

void SoundboxEmulation::startAirShift(float amplitude, float rate)
{
    soundboxGain = amplitude * maxPressure;
}

float SoundboxEmulation::configureVibrato(double sampleRate)
{
    vibratoPhase += vibratoFrequency / sampleRate;
    if (vibratoPhase >= 1.0f) vibratoPhase -= 1.0f;
    return vibratoGain * std::sin(2.0f * std::numbers::pi * vibratoPhase);
}

float SoundboxEmulation::generateNoise() const
{
    return noiseGain * (2.0f * rand() / static_cast<float>(RAND_MAX) - 1.0f);
}
