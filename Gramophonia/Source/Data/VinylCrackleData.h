/*
  ==============================================================================

    VinylCrackle.h
    Created: 18 Jul 2025 7:00:52pm
    Author:  monty

  ==============================================================================
*/

#pragma once

//
//  VinylArtifacts.h
//  Vinyl Artifacts Simulation
//
//  This class simulates various vinyl record imperfections like crackle, pops, and dust.
//

#pragma once

#include <cmath>
#include <cstdlib>
#include <random>

class VinylArtifacts {
public:
    VinylArtifacts(float sampleRate = 44100.0f)
        : mSampleRate(sampleRate)
        , mCounter(0)
        , mRandomGen(std::random_device{}())
    {
        // Initialize random number generator
        mRandom.seed(static_cast<unsigned int>(time(nullptr)));
    }

    // Reset the internal state
    void reset() {
        mCounter = 0;
    }

    // Set the sample rate
    void setSampleRate(float sampleRate) {
        mSampleRate = sampleRate;
    }

    // Apply crackle effect with intensity control
    float applyCrackle(float input, float intensity) {
        mCounter++;

        // Generate random event with probability based on intensity
        int randomNumber = (mRandom() % 200) + 1;

        float output = input;
        float inputDip = input * 0.5f;

        // Occasionally introduce artifacts based on random conditions
        if (mCounter % randomNumber == 0) {
            switch (randomNumber % 5) {
            case 0:
                output = randomNumber / 100.0f; // Small pop
                break;
            case 1:
                output = hardClip(input * (1.0f + intensity), 1.0f); // Distortion pop
                break;
            case 2:
                output = alterBitDepth(inputDip, intensity); // Bit crush artifact
                break;
            case 3:
                output = applyAliasing(inputDip, intensity); // Aliasing artifact
                break;
            case 4:
                output = applyPhaseDistortion(inputDip, intensity); // Phase distortion
                break;
            }
        }

        // Add continuous subtle bit reduction for "vinyl" feel
        output = alterBitDepth(output, 0.0625f * intensity);

        // Reset counter to prevent overflow on long sessions
        if (mCounter > 1000000) {
            mCounter = 0;
        }

        return output;
    }

    // Apply dust effect - small, frequent clicks
    float applyDust(float input, float intensity) {
        // Dust is more frequent but less intense than crackle
        if ((mRandom() % 100) < (intensity * 10)) {
            float dustAmp = (mRandom() % 100) / 1000.0f * intensity;
            input += dustAmp;
        }
        return input;
    }

    // Apply wow/flutter effect - speed variations
    float applyWowFlutter(float input, float intensity, float phase) {
        // Simple wow/flutter implementation
        float speedVariation = 1.0f + (sin(phase * 0.01f) * 0.02f * intensity);
        // This is simplified - a full implementation would need a delay line
        return input * speedVariation;
    }

    // Process a sample with all vinyl effects
    float process(float input, float intensity, float dustIntensity = 0.5f, bool enableWowFlutter = false) {
        float output = input;

        // Apply different vinyl artifacts
        output = applyCrackle(output, intensity);
        output = applyDust(output, intensity * dustIntensity);

        if (enableWowFlutter) {
            output = applyWowFlutter(output, intensity, mCounter);
        }

        // Mix with dry signal based on intensity
        return (output * intensity) + (input * (1.0f - intensity));
    }

private:
    float mSampleRate;
    int mCounter;
    std::mt19937 mRandomGen;
    std::minstd_rand mRandom;

    // Helper functions
    float hardClip(float input, float control) {
        input *= control;
        if (input > 1.0f) input = 1.0f;
        else if (input < -1.0f) input = -1.0f;
        return input;
    }

    float alterBitDepth(float input, float control) {
        // Number of bits to reduce by
        float maxDepth = 24.0f * (1.0f - std::pow(control, 1.0f / 4.0f));

        // Calculate the altered sample value
        float alteredSample = round((input + 1.0f) * maxDepth) / (maxDepth + 1.0f);

        return alteredSample;
    }

    float applyAliasing(float input, float control) {
        static float lastOutput = 0.0f;
        static int sampleCounter = 0;

        // Calculate downsampling factor
        int downsampleFactor = static_cast<int>(10.0f * control) + 1;

        // Downsample by only updating output on every Nth sample
        if (sampleCounter % downsampleFactor == 0) {
            lastOutput = input;
        }

        // Increment sample counter and wrap it
        sampleCounter = (sampleCounter + 1) % downsampleFactor;

        return lastOutput;
    }

    float applyPhaseDistortion(float input, float control) {
        // Simple phase distortion
        float phaseShift = control * 0.1f;
        float phase = sin(mCounter * 0.01f) * phaseShift;
        return input * cos(phase);
    }
};