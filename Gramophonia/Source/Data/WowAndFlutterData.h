/*
  ==============================================================================

    WowAndFlutterData.h
    Created: 9 Jul 2025 10:17:14pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include "ModulationData.h"

#include <vector>
#include <cmath>

#include <vector>
#include <cmath>

class WowAndFlutter
{
public:
    WowAndFlutter()
        : fWowPhase(0.0f),
        flutterLFO1(44100),
        flutterLFO3(44100),
        fEccentricPhase(0.0f),
        osc(),
        pitchTimeWarp(44100.0f),
        inputPos(0),
        outputPos(0),
        lastPitchFactor(1.0f)
    {
        inputBuffer.resize(BUFFER_SIZE, 0.0f);
        outputBuffer.resize(BUFFER_SIZE, 0.0f);
    }

    ~WowAndFlutter()
    {
        pitchTimeWarp.clear();
    }

    void setSampleRate(float newSampleRate)
    {
        sampleRate = newSampleRate;

        // Update sample rate on internal LFOs
        flutterLFO1.setSampleRate(sampleRate);
        flutterLFO3.setSampleRate(sampleRate);
    }

    float processSample(float input, float wowAmount, float flutterAmount, int sampleRate)
    {
        // Base modulation frequencies
        const float fWowFreq = 0.5f;
        const float fEccentricFreq = 0.555f;

        // Update flutter LFO rates according to flutterAmount
        float flutterFreq = 16.5f + (flutterAmount * 16.5f);
        flutterLFO1.setRate(flutterFreq);
        flutterLFO3.setRate(flutterFreq * 3.0f);

        // Advance LFO phases for wow and eccentric manually
        fWowPhase += twoPi * fWowFreq / sampleRate;
        if (fWowPhase >= twoPi) fWowPhase -= twoPi;

        fEccentricPhase += twoPi * fEccentricFreq / sampleRate;
        if (fEccentricPhase >= twoPi) fEccentricPhase -= twoPi;

        // Generate modulation signals
        float fWowMod = std::sin(fWowPhase) * 0.85f
            + std::sin(fWowPhase * 2.0f) * 0.15f
            + std::sin(fEccentricPhase) * 0.15f;

        // Flutter modulation via the two flutter LFO sine oscillators
        float flutter = flutterLFO1.process() * 0.7f + flutterLFO3.process() * 0.3f;
        flutter *= 1.0f - 0.3f * std::fabs(flutter * flutter);
        flutter += std::sin(fEccentricPhase) * flutterAmount * 0.35f;

        // Calculate pitch factor with wow and flutter contributions
        float pitchFactor = 1.0f + (fWowMod * wowAmount * 0.08f) + (flutter * flutterAmount * 0.03f);

        // Store input sample
        inputBuffer[inputPos++] = input;

        // Process buffer if full or pitch changed significantly
        if (inputPos >= BUFFER_SIZE || std::fabs(pitchFactor - lastPitchFactor) > 0.01f)
        {
            pitchTimeWarp.warp.setTransposeFactor(pitchFactor);

            float* inputs[1] = { inputBuffer.data() };
            float* outputs[1] = { outputBuffer.data() };
            pitchTimeWarp.warp.process(inputs, BUFFER_SIZE, outputs, BUFFER_SIZE);

            inputPos = 0;
            outputPos = 0;
            lastPitchFactor = pitchFactor;
        }

        // Output current sample from processed block
        float output = outputBuffer[outputPos];

        // Advance output position but clamp
        if (++outputPos >= BUFFER_SIZE)
            outputPos = BUFFER_SIZE - 1;

        return output;
    }

private:

    class SineLFO {
    public:
        SineLFO(float sampleRate_)
            : sampleRate(sampleRate_), phase(0.0f), rateHz(1.0f), depth(1.0f)
        {
        }

        void setSampleRate(float newSampleRate) { sampleRate = newSampleRate; }
        void setRate(float newRateHz) { rateHz = newRateHz; }
        void setDepth(float newDepth) { depth = newDepth; }

        float process()
        {
            float lfoValue = std::sin(phase) * depth;

            // Advance phase
            phase += twoPi * rateHz / sampleRate;
            if (phase >= twoPi)
                phase -= twoPi;

            return lfoValue;
        }

        void reset() { phase = 0.0f; }

    private:
        float sampleRate;
        float phase;
        float rateHz;
        float depth;

        constexpr static float twoPi = 6.28318530718f;
    };

    static const int BUFFER_SIZE = 256;

    std::vector<float> inputBuffer;
    std::vector<float> outputBuffer;
    int inputPos;
    int outputPos;
    float lastPitchFactor;

    float fWowPhase;
    float fEccentricPhase;

    SineLFO flutterLFO1;
    SineLFO flutterLFO3;

    Modulation::Osc osc;
    Modulation::PitchShiftAndTimeStretch pitchTimeWarp;

    float sampleRate;

    constexpr static float twoPi = 6.28318530718f;
};


