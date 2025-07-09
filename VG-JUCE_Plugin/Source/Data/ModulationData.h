/*
  ==============================================================================

    ModulationData.h
    Created: 9 Jul 2025 10:17:49pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include "libs/stretch/SignalsmithStretch.h"

class Modulation
{
public:

    class Osc
    {
    public:
        Osc() : fPhasePos(0.0f) {}

        float incrementPhase(float freq, float sampleRate)
        {
            float fTremPhaseInc = (2 * M_PI * freq) / sampleRate; // Calculate the phase increment based on the tremolo rate and sample rate
            return fTremPhaseInc;
        }

        float progressAndWrap(float phaseIncrement, float phasePosition)
        {
            phasePosition += phaseIncrement; // Move our oscillator forward
            phasePosition = fmodf(phasePosition, 2.0f * M_PI); // Handles multiple cycles; so 2π, 4π, 6π, etc.
            return phasePosition;
        }

        float oscillate(float phasePosition, float rate, float x, float y)
        {
            float fOscSig = sin(phasePosition) * rate; // Range -1 to 1
            float fOscEffect = (fOscSig * x) + y; // Convert to the range 0 to 1

            return fOscEffect; // Return the tremolo effect value
        }

        float process(float sampleRate)
        {
            float fTremPhaseInc = (2 * M_PI) / sampleRate; // Calculate the phase increment based on the tremolo rate and sample rate

            fPhasePos = progressAndWrap(fTremPhaseInc, fPhasePos);

            float fOutput = oscillate(fPhasePos, 0.25, 0.5, 0.5);

            return fOutput;
        }

    private:

        float fPhasePos; // Phase position of the tremolo oscillator
    };

    class PitchShiftAndTimeStretch
    {
    public:
        using Stretch = signalsmith::stretch::SignalsmithStretch<float>;
        Stretch warp;

        explicit PitchShiftAndTimeStretch(float sampleRate)
        {
            warp.presetDefault(1, sampleRate); // Use only one preset
        }

        void applyEffect(float input, int inputSamples,
            float output, int outputSamples,
            float transposeFactor = 1.0f,
            float semitones = 0.0f,
            float formantSampleRate = 8000.0f, float sampleRate)
        {
            warp.setTransposeSemitones(semitones, formantSampleRate);
            warp.setTransposeFactor(transposeFactor);
            warp.process(input, inputSamples, output, outputSamples);
        }

        void clear()
        {
            warp.reset();
        }
    };
};