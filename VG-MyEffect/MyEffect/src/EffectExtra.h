#include "../include/stretch/signalsmith-stretch.h"

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

        void applyEffect(float* input, int inputSamples,
            float* output, int outputSamples,
            float transposeFactor = 1.0f,
            float semitones = 0.0f,
            float formantSampleRate = 8000.0f, float sampleRate = 44100.0f)
        {
            // Create a wrapper that makes a single pointer look like an array of channels
            struct MonoChannelWrapper {
                float* ptr;
                
                // This wrapper represents a single channel
                struct Channel {
                    float* ptr;
                    float& operator[](int i) { 
                        // Critical fix: ensure we don't go out of bounds
                        return ptr[i]; 
                    }
                };
                
                // Return the same channel regardless of the index
                Channel operator[](int) {
                    return Channel{ptr};
                }
            };
            
            // Create wrappers for input and output
            MonoChannelWrapper inputWrapper{input};
            MonoChannelWrapper outputWrapper{output};
            
            warp.setTransposeSemitones(semitones, formantSampleRate);
            warp.setTransposeFactor(transposeFactor);
            warp.process(inputWrapper, inputSamples, outputWrapper, outputSamples);
        }

        void clear()
        {
            warp.reset();
        }
    };
};

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
        // Store the incoming sample in our buffer
        inputBuffer[bufferPos] = input;
        
        // Base frequencies (Hz)
        float fWowFreq = 0.5f + (5.5f * (rand() / (float)RAND_MAX * 0.1f));      // 0.5 Hz to 6 Hz
        float fFlutterFreq = 16.5f + (flutterAmount * 16.5f * (rand() / (float)RAND_MAX * 0.1f)); // 16.5 Hz to 33 Hz

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

        // Calculate the pitch modulation factor (actual semitones now)
        float pitchFactor = 1.0f + (fWowMod * wowAmount * 0.08f) + (fFlutter * flutterAmount * 0.03f);
        
        // Process buffers when full or when pitch changes significantly
        if (bufferPos >= BUFFER_SIZE - 1 || fabs(pitchFactor - lastPitchFactor) > 0.01f) {
            processBuffer(pitchFactor, sampleRate);
            lastPitchFactor = pitchFactor;
        }
        
        // Get output sample and advance buffer position
        float output = outputBuffer[bufferPos++];
        
        // Reset buffer position if needed
        if (bufferPos >= BUFFER_SIZE) {
            bufferPos = 0;
        }
        
        return output;
    }

private:
    void processBuffer(float pitchFactor, float sampleRate) {
        // Apply pitch shifting to the entire buffer
        pitchTimeWarp.warp.setTransposeFactor(pitchFactor);
        
        // Wrapper to make our vector look like a channel array
        struct BufferWrapper {
            std::vector<float>& buffer;
            struct Channel {
                std::vector<float>& buffer;
                float& operator[](int i) { return buffer[i]; }
            };
            Channel operator[](int) { return Channel{buffer}; }
        };
        
        BufferWrapper inWrapper{inputBuffer};
        BufferWrapper outWrapper{outputBuffer};
        
        // Process with time-stretching at unity speed (pitch shift only)
        pitchTimeWarp.warp.process(inWrapper, BUFFER_SIZE, outWrapper, BUFFER_SIZE);
    }

    static const int BUFFER_SIZE = 1024; // Buffer size for block processing
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

class Dynamics
{
public:

    Dynamics() : iMeasuredLength(0), iMeasuredItems(0), fMax(0.f), fMaxOld(0) {}

    float fAmplitude = 0.f; // Current amplitude of the inputBuffer signal

    float peakDetector(float input)
    {
        fAmplitude = fabs(input); // Get the absolute value of the inputBuffer signal

        iMeasuredLength = (int)(0.02 * getSampleRate()); // Calculate the length of the measurement window based bLfoActive a 20ms duration

        if (fAmplitude > fMax) fMax = fAmplitude; // Update the maximum amplitude if the current amplitude is greater

        iMeasuredItems++; // Increment the number of measured items

        float fOutput = 0;

        if (iMeasuredItems == iMeasuredLength)
        {
            fOutput = fMax; // Output the maximum amplitude after the measurement window is complete
            fMax = iMeasuredItems = 0; // Reset the maximum amplitude and measured items count
        }

        return fOutput; // Return the fTremOutput value
    }

private:
    int iMeasuredLength, iMeasuredItems;
    float fMax, fMaxOld;
};
