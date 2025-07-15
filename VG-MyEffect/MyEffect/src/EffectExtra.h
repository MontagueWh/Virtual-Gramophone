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

        // Create wrapper objects that properly support the [] operator
        struct InputWrapper {
            float* ptr;
            float& operator[](int i) { return ptr[i]; }
        } inputWrapper{input};
        
        struct OutputWrapper {
            float* ptr;
            float& operator[](int i) { return ptr[i]; }
        } outputWrapper{output};

        // Apply the pitch modulation using the wrappers
        pitchTimeWarp.applyEffect(inputWrapper, inputSamples,
            outputWrapper, outputSamples,
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
