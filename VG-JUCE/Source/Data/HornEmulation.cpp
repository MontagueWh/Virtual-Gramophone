/*
  ==============================================================================

    HornEmulation.cpp
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HornEmulation.h"

//==============================================================================
HornEmulation::HornEmulation()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	// ADSR setup
	adsr.setTarget(1.0);
	adsr.setAttackRate(0.02);
	adsr.setDecayRate(0.2);
	adsr.setSustainLevel(0.9);
	adsr.setReleaseRate(0.1);

	// Initialise member variables to avoid warning C26495
	pitchShiftTarget = 0.0f;
	maxDelay = 0.0f;
	delayLength = 0;
	readPtr = 0;
	writePtr = 0;
	outputGain = 1.0f;
	inputGain = 0.5f;
	frequency = 440.0f;  // Default A4, will be overridden

	// Initialise RMS tracking
	rmsLevel = 0.0f;
	rmsAlpha = 0.99f;  // Smoothing factor (adjust as needed)
}

HornEmulation::WaveguideSynthesis::WaveguideSynthesis()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	reader = nullptr;
	audioFormatManager.registerBasicFormats(); // Register basic audio formats
	setupBodyResonances(); // Initialise body resonances
}

HornEmulation::~HornEmulation()
{
	// Destructor for waveguide synthesis
	adsr.setTarget(10.0); // Set target to 10.0 to avoid any abrupt changes
	adsr.setAttackRate(0.1); // Set attack rate to 0.2 to simulate sound passing through the horn
	adsr.setDecayRate(0.0); //	No decay
	adsr.setSustainLevel(10.0);
	adsr.setReleaseRate(0.1); // To simulate post-audio brass vibrations
}


HornEmulation::WaveguideSynthesis::~WaveguideSynthesis()
{

}

void HornEmulation::WaveguideSynthesis::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	handleImpulseResponse(sampleRate, samplesPerBlockExpected); // Handle the impulse response
}

void HornEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	pitchShiftTarget = 0.0f;

	// Calculate delay buffer length based on lowest frequency
	maxDelay = sampleRate / lowestFrequency + 1;
	delayLength = maxDelay;

	// Initialise delay line
	for (int i = 0; i < 2048; i++)
		delayLine[i] = 0.0f;

	readPtr = 0;
	writePtr = delayLength;

	outputGain = 1.0f;
	inputGain = 0.5f;

	freqSetup(); // Set the frequency of the brass synthesis

	Stk::setSampleRate(sampleRate);

	// Convolution setup
	juce::dsp::ProcessSpec specConvolution;
	specConvolution.sampleRate = sampleRate;
	specConvolution.maximumBlockSize = samplesPerBlockExpected;
	specConvolution.numChannels = 1;

	for (int i = 0; i <= 10; i++) convolution[i].prepare(specConvolution); // Prepare the convolution processor

	waveguideSynthesis.prepareToPlay(samplesPerBlockExpected, sampleRate); // Initialise the waveguide synthesis

	for (int i = 0; i < 11; ++i) // Load impulses responses into convolution method
	{
		waveguideSynthesis.reader = waveguideSynthesis.audioFormatManager.createReaderFor(waveguideSynthesis.irFiles[i]);

		if (waveguideSynthesis.reader != nullptr)
		{
			waveguideSynthesis.iRs[i].setSize(1, static_cast<int>(waveguideSynthesis.reader->lengthInSamples));
			waveguideSynthesis.reader->read(&waveguideSynthesis.iRs[i], 0, static_cast<int>(waveguideSynthesis.reader->lengthInSamples), 0, true, true);

			convolution[i].loadImpulseResponse(
				std::move(waveguideSynthesis.iRs[i]),
				waveguideSynthesis.reader->sampleRate,
				juce::dsp::Convolution::Stereo::no,
				juce::dsp::Convolution::Trim::no,
				juce::dsp::Convolution::Normalise::yes);

			delete waveguideSynthesis.reader;
			waveguideSynthesis.reader = nullptr;
		}
	}
}

stk::StkFloat HornEmulation::tick(unsigned int channel)
{
	float input = gramoStylus.getFilterOutput(); // Get the input from the stylus

	float output = brassHorn.tick(); // Mix with waveguide synthesis output

	output *= adsr.tick(); // Mix with waveguide synthesis output

	return output;
}

stk::StkFrames& HornEmulation::tick(stk::StkFrames& frames, unsigned int channel) {
	// Process each sample in the frame
	for (unsigned int i = 0; i < frames.frames(); i++) {
		frames(i, channel) = tick();
	}
	return frames;
}

void HornEmulation::WaveguideSynthesis::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.
	bufferToFill.clearActiveBufferRegion(); // Clear the buffer region
}

void HornEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	float incomingAmplitude = 0.0f;
	int sampleCount = 0;

	// This function is called by the host to fill the output buffer with audio data.
	for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
		float* channelData = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
			// Get input from the buffer
			float inputSample = channelData[sample];

			// Process the stylus (which acts as the excitation, like lips in brass)
			gramoStylus.processPressureDifference(inputSample);

			float stylusOutput = gramoStylus.getFilterOutput();

			brassHorn.noteOn(frequency, stylusOutput); // This is conceptual - you'd need to adapt

			// Use the STK tick method to get the processed sample
			float outputSample = brassHorn.tick();

			channelData[sample] = outputSample;

			incomingAmplitude = pow(channelData[sample], 2.0f);
			sampleCount++;
		}
	}

	rmsLevel = sqrt(incomingAmplitude / sampleCount); // Calculate RMS level
	rmsLevel = (rmsAlpha * rmsLevel) + (1.0f - rmsAlpha) * incomingAmplitude; // Apply smoothing

	incomingAmplitude += brassHorn.lastOut();

	// Determine which convolution to use
	int convIndex = selectConvolutionIndex(incomingAmplitude, adsr.tick());

	// Process through the selected convolution
	auto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);
	auto context = juce::dsp::ProcessContextReplacing<float>(block);
	convolution[convIndex].process(context);
}

void HornEmulation::WaveguideSynthesis::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
	for (int i = 0; i <= 10; ++i) iRs[i].setSize(0, 0);
}

void HornEmulation::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void HornEmulation::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) {
    // Your implementation here
    // e.g., brassHorn.noteOn(frequency, amplitude);

	frequency = freqSetup(); // Set the frequency of the brass synthesis
	brassHorn.startBlowing(amplitude, 0.1);
	adsr.keyOn();
}

void HornEmulation::noteOff(stk::StkFloat amplitude) {
	brassHorn.setFrequency(freqSetup()); // Set the frequency of the brass synthesis
	brassHorn.stopBlowing(amplitude);
	adsr.keyOff(); // Release the ADSR envelope
}

void HornEmulation::WaveguideSynthesis::setupBodyResonances()
{
	// Configure a body resonance filter (BP filter)
	stk::BiQuad bodyFilter;
	float bodyFrequency = 500.0f; // Resonant frequency in Hz
	float bodyQfactor = 1.5f; // Q factor for the body resonance filter
	bodyFilter.setResonance(bodyFrequency, bodyQfactor, true); // Set the resonance filter
}

float HornEmulation::freqSetup()
{
	constexpr float brassYoungModulus = 10.0e10f; // Young's modulus for brass in Pascals
	constexpr float airDensity = 1.2f; // Density of air in kg/m^3
	constexpr float soundSpeed = 343.0f; // Speed of sound in air in m/s

	float hornDiameter = 0.25f; // Diameter of the horn
	float hornLength = 0.75;
	float hornWallThickness = 0.04f; // Wall thickness of the horn

	float hornStiffness = (brassYoungModulus * hornWallThickness) /
		(hornDiameter * hornLength); // Simplified stiffness model for a thin-walled brass tube

	// Calculate timbre modifier based on geometry
	float wavelength = 2.f * 0.25; // Wavelength of the sound wave
	float freq = soundSpeed / wavelength; // Frequency of the sound wave

	// Calculate a timbre modifier proportional to horn stiffness and geometry
	float timbreModifier = hornDiameter / (hornStiffness * hornLength); // Timbre modifier based on horn parameters
	float effectiveFreq = (freq * timbreModifier) + pitchShiftTarget; // Effective frequency based on the horn parameters
	return effectiveFreq;
}

void HornEmulation::WaveguideSynthesis::handleImpulseResponse(double sampleRate, int samplesPerBlock)
{
	audioFormatManager.registerBasicFormats();

	reader = nullptr;

	irFiles[0] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Initial Stage/Attack Initial Quiet.wav");
	irFiles[1] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Initial Stage/Attack Initial Loud.wav");
	irFiles[2] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Halfway Stage/Halfway Attack Quiet.wav");
	irFiles[3] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Halfway Stage/Halfway Attack Loud.wav");
	irFiles[4] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Decay/Decay Quiet.wav");
	irFiles[5] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Decay/Decay Loud.wav");
	irFiles[6] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Sustain/Sustain Quiet.wav");
	irFiles[7] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Sustain/Sustain Loud.wav");
	irFiles[8] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Release/Release Quiet.wav");
	irFiles[9] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Initial Stage/Release Initial Loud.wav");
	irFiles[10] = juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Halfway Stage/Halfway Release Loud.wav");
}

void HornEmulation::setPitchShift(float position)
{
	pitchShiftTarget = position * 100.0f; // Convert slide position to pitch shift

	// Update the frequency if the brass instrument is active
	// Check if ADSR is in a non-idle state (states 0-3 are active states)
	int adsrState = adsr.getState();
	if (adsrState >= 0 && adsrState <= 3) {
		// Update frequency - using the current frequency plus the pitch shift
		// Assuming 'frequency' is the current base frequency
		brassHorn.setFrequency(frequency + pitchShiftTarget);
	}
}

int HornEmulation::selectConvolutionIndex(float amplitude, float adsrValue)
{
	// Determine if we're using "loud" or "quiet" IRs
	const float LoudnessThresh = 0.3f; // Threshold for loudness
	bool isLoud = amplitude > 0.6f;

	// Get the current ADSR state (STK uses integers 0-4 for its states)
	int state = adsr.getState();

	// Default to the first IR
	int convolutionIndex = 0;

	// STK ADSR states are often: 
	// 0 = ATTACK
	// 1 = DECAY
	// 2 = SUSTAIN
	// 3 = RELEASE
	// 4 = IDLE

	switch (state) {
	case 0: // ATTACK
		// For attack, we have initial and halfway IRs for both loud and quiet
		if (adsrValue < 0.5f) {
			// Initial stage of attack
			convolutionIndex = isLoud ? 1 : 0;  // Index 1 = loud initial attack, 0 = quiet initial attack
		}
		else {
			// Halfway stage of attack
			convolutionIndex = isLoud ? 3 : 2;  // Index 3 = loud halfway attack, 2 = quiet halfway attack
		}
		break;

	case 1: // DECAY
		// For decay, we have separate IRs for loud and quiet
		convolutionIndex = isLoud ? 5 : 4;  // Index 5 = loud decay, 4 = quiet decay
		break;

	case 2: // SUSTAIN
		// For sustain, we have separate IRs for loud and quiet
		convolutionIndex = isLoud ? 7 : 6;  // Index 7 = loud sustain, 6 = quiet sustain
		break;

	case 3: // RELEASE
		// For release, we have quiet, and loud with initial and halfway stages
		if (isLoud) {
			if (adsrValue > 0.5f) {
				convolutionIndex = 9;  // Loud initial release
			}
			else {
				convolutionIndex = 10; // Loud halfway release
			}
		}
		else {
			convolutionIndex = 8;      // Quiet release
		}
		break;

	default: // IDLE or other state
		convolutionIndex = 0; // Default to first IR
		break;
	}

	return convolutionIndex;
}
