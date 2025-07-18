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
        pitchTimeWarp(44100.0f),
        bufferPos(0),
        lastPitchFactor(1.0f)
    {
        inputBuffer.resize(BUFFER_SIZE, 0.0f);
        outputBuffer.resize(BUFFER_SIZE, 0.0f);
    }

    ~WowAndFlutter()
    {
        pitchTimeWarp.clear();
    }

    float processSample(float input, float wowAmount, float flutterAmount, float sampleRate)
    {
        // Ensure buffer position is always in bounds BEFORE access
        if (bufferPos >= BUFFER_SIZE - 1) {
            processBuffer(lastPitchFactor, sampleRate);
            bufferPos = 0;
        }

        // Store the incoming sample in our buffer
        inputBuffer[bufferPos] = input;

        // Base frequencies (Hz)
        float fWowFreq = 0.5f + (5.5f * (rand() / (float)RAND_MAX * 0.1f));
        float fFlutterFreq = 16.5f + (flutterAmount * 16.5f * (rand() / (float)RAND_MAX * 0.1f));

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

        // Calculate the pitch modulation factor
        float pitchFactor = 1.0f + (fWowMod * wowAmount * 0.08f) + (fFlutter * flutterAmount * 0.03f);

        // Process buffers when full or when pitch changes significantly
        if (bufferPos >= BUFFER_SIZE - 1 || fabs(pitchFactor - lastPitchFactor) > 0.01f) {
            processBuffer(pitchFactor, sampleRate);
            // Buffer has been processed, so we reset position
            bufferPos = 0;
            lastPitchFactor = pitchFactor;
        }

        // Get output sample
        float output = outputBuffer[bufferPos];

        // Advance buffer position AFTER accessing
        bufferPos++;

        return output;
    }

private:
    void processBuffer(float pitchFactor, float sampleRate) {
        // Apply pitch shifting to the entire buffer
        pitchTimeWarp.warp.setTransposeFactor(pitchFactor);

        // Create safer buffer wrappers with proper bounds checking
        struct SafeBufferWrapper {
            std::vector<float>& buffer;
            int size;

            struct SafeChannel {
                std::vector<float>& buffer;
                int size;

                float& operator[](int i) {
                    return buffer[i < size ? i : size - 1];
                }
            };

            SafeChannel operator[](int) {
                return SafeChannel{ buffer, (int)buffer.size() };
            }
        };

        // Use the actual sizes of the buffers
        SafeBufferWrapper inWrapper{ inputBuffer, (int)inputBuffer.size() };
        SafeBufferWrapper outWrapper{ outputBuffer, (int)outputBuffer.size() };

        // Make sure the sizes we pass to process are within bounds
        int inSize = std::min(BUFFER_SIZE, (int)inputBuffer.size());
        int outSize = std::min(BUFFER_SIZE, (int)outputBuffer.size());

        // Process with time-stretching
        pitchTimeWarp.warp.process(inWrapper, inSize, outWrapper, outSize);
    }

    static const int BUFFER_SIZE = 257; // Buffer size for block processing
    std::vector<float> inputBuffer;
    std::vector<float> outputBuffer;
    int bufferPos;
    float lastPitchFactor;

    float fWowPhase;
    float fFlutterPhase;
    float fEccentricPhase;
    Modulation::Osc osc;
    Modulation::PitchShiftAndTimeStretch pitchTimeWarp;
};