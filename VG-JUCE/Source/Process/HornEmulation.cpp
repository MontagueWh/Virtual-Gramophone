/*
  ==============================================================================

    brassSynthesis.cpp
    Created: 17 May 2025 6:50:39pm
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HornEmulation.h"

//==============================================================================
brassSynthesis::brassSynthesis()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	updateHornParameters();
}

brassSynthesis::waveguideSynthesis::waveguideSynthesis()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	// ADSR Setup for brass stk
	adsr.setTarget(1.0);
	adsr.setAttackRate(0.02);
	adsr.setDecayRate(0.2);
	adsr.setSustainLevel(0.6);


	setupBodyResonances(); // Initialise body resonance filter
}

brassSynthesis::~brassSynthesis()
{
}


brassSynthesis::waveguideSynthesis::~waveguideSynthesis()
{
	// Destructor for waveguide synthesis
	adsr.setTarget(0.0); // Set target to 0.0 to stop the envelope
	adsr.setDecayRate(0.0); // Set decay rate to 0.0 to stop the envelope
	adsr.setSustainLevel(0.0); // Set sustain level to 0.0 to stop the envelope
}

void brassSynthesis::waveguideSynthesis::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	Stk::setSampleRate(sampleRate);

	// Convolution setup
	juce::dsp::ProcessSpec specConvolution;
	specConvolution.sampleRate = sampleRate;
	specConvolution.maximumBlockSize = samplesPerBlockExpected;
	specConvolution.numChannels = 1;

	for (int i = 0; i <= 10; i++) convolution[i].prepare(specConvolution); // Prepare the convolution processor

	handleImpulseResponse(sampleRate, samplesPerBlockExpected); // Handle the impulse response
}

void brassSynthesis::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	pitchShiftTarget = 0.0f;

	// Calculate delay buffer length based on lowest frequency
	maxDelay = sampleRate / lowestFrequency + 1;
	delayLength = maxDelay;

	// Initialize delay line
	for (int i = 0; i < 2048; i++)
		delayLine[i] = 0.0f;

	readPtr = 0;
	writePtr = delayLength;

	outputGain = 1.0f;
	inputGain = 0.5f;
	dryWetMix = 0.7f;

	// Default frequency
	setFrequency(440.0f);
}

stk::StkFloat brassSynthesis::tick(unsigned int channel)
{
	float input = gramoStylus.getFilterOutput(); // Get the input from the stylus
	float brassOutput = brassHorn.tick(); // Mix with waveguide synthesis output
}

void brassSynthesis::waveguideSynthesis::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.
}

void brassSynthesis::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.
	for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
		float* channelData = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

		for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
			// Process input through both brass and waveguide models
			float input = channelData[sample] * inputGain;

			// Process through brass model
			float output = processSample(input);

			// Apply dry/wet mix
			channelData[sample] = input * (1.0f - dryWetMix) + output * dryWetMix;
		}
	}
}

void brassSynthesis::waveguideSynthesis::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void brassSynthesis::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void brassSynthesis::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) {
    // Your implementation here
    // e.g., brassHorn.noteOn(frequency, amplitude);
}

void brassSynthesis::noteOff(stk::StkFloat amplitude) {
	// Your implementation here
	// e.g., brassHorn.noteOff(amplitude);
}

void brassSynthesis::waveguideSynthesis::setupBodyResonances()
{
	// Configure a body resonance filter (BP filter)
	stk::BiQuad bodyFilter;
	float bodyFrequency = 500.0f; // Resonant frequency in Hz
	float bodyQfactor = 1.5f; // Q factor for the body resonance filter
	bodyFilter.setResonance(bodyFrequency, bodyQfactor, true); // Set the resonance filter
}

void brassSynthesis::updateHornParameters()
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
	float effectiveFreq = freq * timbreModifier; // Effective frequency based on the horn parameters

	brassHorn.setFrequency(effectiveFreq); // Set the frequency of the horn
}

void brassSynthesis::waveguideSynthesis::handleImpulseResponse(double sampleRate, int samplesPerBlock)
{
	audioFormatManager.registerBasicFormats();

	juce::AudioFormatReader* reader = nullptr;

	juce::File irFiles[11] =
	{
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Initial Stage/Attack Initial Quiet.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Initial Stage/Attack Initial Loud.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Halfway Stage/Halfway Attack Quiet.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Halfway Stage/Halfway Attack Loud.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Decay/Decay Quiet.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Decay/Decay Loud.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Sustain/Sustain Quiet.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Sustain/Sustain Loud.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Release/Release Quiet.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Initial Stage/Release Initial Loud.wav"),
	   juce::File("../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Halfway Stage/Halfway Release Loud.wav")
	};

	for (int i = 0; i < 11; ++i)
	{
		reader = audioFormatManager.createReaderFor(irFiles[i]);

		if (reader != nullptr)
		{
			iRs[i].setSize(1, static_cast<int>(reader->lengthInSamples));
			reader->read(&iRs[i], 0, static_cast<int>(reader->lengthInSamples), 0, true, true);

			convolution[i].loadImpulseResponse(
				std::move(iRs[i]),
				reader->sampleRate,
				juce::dsp::Convolution::Stereo::no,
				juce::dsp::Convolution::Trim::no,
				juce::dsp::Convolution::Normalise::yes);

			delete reader;
		}
	}
}
