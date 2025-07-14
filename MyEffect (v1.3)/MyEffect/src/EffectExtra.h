class Mod
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

        float oscillate(float phasePostion, float rate, float x, float y)
        {
            float fOscSig = sin(phasePostion) * rate; // Range -1 to 1
            float fOscEffect = (fOscSig * x) + y; // Convert to the range 0 to 1

            return fOscEffect; // Return the tremolo effect value
        }

        float process(float sampleRate)
        {
            float fTremPhaseInc = (2 * M_PI) / sampleRate; // Calculate the phase increment based on the tremolo rate and sample rate

            fPhasePos = progressAndWrap(fTremPhaseInc, fPhasePos);

            float fOsc = oscillate(fPhasePos, 0.25, 0.5, 0.5);

            float output = fOsc; // Apply tremolo effect
            return output;
        }

    private:

        float fPhasePos; // Phase position of the tremolo oscillator
    };

    class Vibrato
    {

    };
};

class WowAndFlutter
{
public:
    // Constructor initialises oscillator phases
    WowAndFlutter() :
        fWowPhase(0.0f),
        fFlutterPhase(0.0f),
        fEccentricPhase(0.0f), osc() {
    }

    float applyModulation(float input, float wowAmount, float flutterAmount, float sampleRate)
    {
        // Base frequencies (Hz)
		float fWowFreq = 0.5f + (5.5f * (rand() / 100000.f)); // Wow frequency varies between 0.5 Hz and 6 Hz
		float fFlutterFreq = 16.5 + (flutterAmount * 16.5 * (rand() / 10000.f)); // Flutter frequency varies between 16.5 Hz and 33 Hz

        fWowPhase = osc.progressAndWrap(osc.incrementPhase(fWowFreq, sampleRate), fWowPhase); // Wrap phase to keep it within [0, 2π]
		fFlutterPhase = osc.progressAndWrap(osc.incrementPhase(fFlutterFreq, sampleRate), fFlutterPhase); // Wrap phase to keep it within [0, 2π]

		const float fEccentricFreq = 0.555f; // matches a 33.3 RPM
        fEccentricPhase = osc.progressAndWrap(osc.incrementPhase(fEccentricFreq, sampleRate), fEccentricPhase); // Wrap phase to keep it within [0, 2π]

        // Generate modulation specific to gramophone stylus
        float fWowMod = sin(fWowPhase) * 0.85f + sin(fWowPhase * 2.0f) * 0.15f; // More cyclic pattern
        fWowMod += sin(fEccentricPhase) * 0.15f; // Add eccentricity to wow modulation (enmulates center record hole)

        float rawFlutter = sin(fFlutterPhase) * 0.7f + sin(fFlutterPhase * 3.0f) * 0.3f; // Gramophone flutter has more regular patterns than tape
        // Apply cubic shaping to soften the peaks.
        float fFlutterMod = rawFlutter * (1.0f - 0.3f * fabsf(rawFlutter * rawFlutter)); // The side effect is that it reduces harmonic distortion.
		fFlutterMod += sin(fEccentricPhase) * flutterAmount * 0.35f; // Add eccentricity to flutter modulation (simulates off-center record hole)

        // Combine modulation components with flutter amount reduced
        float fTotalMod = (fWowMod * wowAmount) +
            (fFlutterMod * flutterAmount);

        // Apply modulation to input with gentle waveshaping
        float output = input * (1.0f + fTotalMod); // Reduce overall modulation depth
   
        
        return output;
    }

private:
    float fWowPhase;       // Phase position for wow effect (slow)
    float fFlutterPhase;   // Phase position for flutter effect (fast)
    float fEccentricPhase; // Phase for eccentric record simulation

    Mod::Osc osc;
};

class Dynamics
{
public:

    Dynamics() : iMeasuredLength(0), iMeasuredItems(0), fMax(0.f), fMaxOld(0) {}

	float fAmplitude = 0.f; // Current amplitude of the input signal

    float peakDetector(float input)
    {
		fAmplitude = fabs(input); // Get the absolute value of the input signal

		iMeasuredLength = (int)(0.02 * getSampleRate()); // Calculate the length of the measurement window based bLfoActive a 20ms duration

		if (fAmplitude > fMax) fMax = fAmplitude; // Update the maximum amplitude if the current amplitude is greater

		iMeasuredItems++; // Increment the number of measured items

        float output = 0;

        if (iMeasuredItems == iMeasuredLength)
        {
			output = fMax; // Output the maximum amplitude after the measurement window is complete
		    fMax = iMeasuredItems = 0; // Reset the maximum amplitude and measured items count
        }

		return output; // Return the fTremOutput value
    }

private:
    int iMeasuredLength, iMeasuredItems;
    float fMax, fMaxOld;    
};