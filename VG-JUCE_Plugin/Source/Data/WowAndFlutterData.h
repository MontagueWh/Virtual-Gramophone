/*
  ==============================================================================

    WowAndFlutterData.h
    Created: 9 Jul 2025 10:17:14pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include "ModulationData.h"

class WowAndFlutter
{
public:
    WowAndFlutter() :
        fWowPhase(0.0f),
        fFlutterPhase(0.0f),
        fEccentricPhase(0.0f),
        osc(),
        pitchTimeWarp(44100.0f)  // Will be updated with actual sample rate in applyModulation
    {
    }

    ~WowAndFlutter()
    {
        pitchTimeWarp.clear(); // Clear the pitch shift and time stretch effect
    }

    void applyModulation(float* input, int inputSamples, float* output, int outputSamples,
        float wowAmount, float flutterAmount, float sampleRate)
    {
        // Base frequencies (Hz)
        float fWowFreq = 0.5f + (5.5f * (rand() / 100000.f));      // 0.5 Hz to 6 Hz
        float fFlutterFreq = 16.5f + (flutterAmount * 16.5f * (rand() / 10000.f)); // 16.5 Hz to 33 Hz

        // Update phases
        fWowPhase = osc.progressAndWrap(osc.incrementPhase(fWowFreq, sampleRate), fWowPhase);
        fFlutterPhase = osc.progressAndWrap(osc.incrementPhase(fFlutterFreq, sampleRate), fFlutterPhase);

        const float fEccentricFreq = 0.555f; // 33.3 RPM
        fEccentricPhase = osc.progressAndWrap(osc.incrementPhase(fEccentricFreq, sampleRate), fEccentricPhase);

        // Generate modulation signals
        float fWowMod = sin(fWowPhase) * 0.85f + sin(fWowPhase * 2.0f) * 0.15f;
        fWowMod += sin(fEccentricPhase) * 0.15f;

        float fFlutter = sin(fFlutterPhase) * 0.7f + sin(fFlutterPhase * 3.0f) * 0.3f;
        fFlutter *= 1.0f - 0.3f * fabsf(fFlutter * fFlutter);
        fFlutter += sin(fEccentricPhase) * flutterAmount * 0.35f;

        // Combine modulations and scale for pitch shifting
        // Convert to semitones (small values for subtle pitch variations)
        float fPitchMod = (fWowMod * wowAmount * 0.15f) +
            (fFlutter * flutterAmount * 0.05f);

        // Apply pitch modulation using pitchTimeWarp
        // Base fTransposeFactor is 1.0 (no shift), modulated by our wow and flutter
        float fTransposeFactor = 1.0f + fPitchMod;

        // Apply the pitch modulation
        pitchTimeWarp.applyEffect(*input, inputSamples,
            *output, outputSamples,
            fTransposeFactor,  // Modulated pitch factor
            0.0f,            // No additional semitone shift
            8000.0f);        // Standard formant sample rate
    }

private:
    float fWowPhase;
    float fFlutterPhase;
    float fEccentricPhase;
    Modulation::Osc osc;
    Modulation::PitchShiftAndTimeStretch pitchTimeWarp;

    float fWowControl;
	float fFlutterControl;  
};