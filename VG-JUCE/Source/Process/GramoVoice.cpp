/*
  ==============================================================================

    GramoVoice.cpp
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GramoVoice.h"

//==============================================================================
GramoVoice::GramoVoice()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	float wavelength = 2.f * hornLength; // Wavelength of the sound wave
	float soundSpeed = 343.0f; // Speed of sound in air in m/s
	float freq = soundSpeed / wavelength; // Frequency of the sound wave

	gramoHorn.startBlowing(startAmp, attackRate); // send sound through the gramophone horn
	gramoHorn.noteOn(freq, startAmp); // make the gramophone horn permanently active
}

GramoVoice::~GramoVoice()
{
}

void GramoVoice::prepareToPlay(int samplesPerBlock, double sampleRate)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..

	setSampleRate(sampleRate); // Set the sample rate
	Stk::setSampleRate(sampleRate); // Set the sample rate for STK

	handleImpulseResponse(sampleRate, samplesPerBlock); // Handle the impulse response
}

void GramoVoice::handleImpulseResponse(double sampleRate, int samplesPerBlock)
{
	// This function is called to handle the impulse response of the system.
	// You can use this to apply any effects or processing to the audio signal.
	// For example, you could apply a convolution reverb effect here.

	audioFormatManager.registerBasicFormats(); // Register basic audio formats
	juce::File irFile(""); // Load the impulse response file
	juce::AudioFormatReader* reader = audioFormatManager.createReaderFor(irFile); // Create a reader for the impulse response file

	if (reader)
	{
		impulseResponse.setSize(1, reader->lengthInSamples); // Set the size of the impulse response buffer
		reader->read(&impulseResponse, 0, reader->lengthInSamples, 0, true, true); // Read the impulse response data into the buffer
		delete reader; // Delete the reader to free up memory

		// Instead, use juce::dsp::ProcessSpec to configure the convolution processor
		juce::dsp::ProcessSpec spec;
		spec.sampleRate = sampleRate;
		spec.maximumBlockSize = samplesPerBlock;
		spec.numChannels = 1; // Adjust as needed for your use case

		convolution.prepare(spec); // Prepare the convolution processor with the spec

		// Set the impulse response for the convolution processor
		/*convolution.loadImpulseResponse
			(impulseResponse,
			juce::dsp::Convolution::Stereo::no,
			juce::dsp::Convolution::Trim::no,
			impulseResponse.getNumSamples());*/

		convolution.loadImpulseResponse(impulseResponse, sampleRate, 
	}
}

void GramoVoice::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void GramoVoice::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	// This function is called by the host when it's time to process some data.
	// In this case, we are just filling the output buffer with a simple sine wave.
	for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			// do something with gramoPressure

			juce::dsp::AudioBlock<float> block(buffer); // Wrap the buffer in an AudioBlock
			juce::dsp::ProcessContextReplacing<float> context(block); // Create a process context for the block
			
			//channelData[sample] = 0.0f; // Clear the output buffer
		}
	}
}

void GramoVoice::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

}

bool GramoVoice::isBusesLayoutSupported(const BusesLayout& layouts) const
{
	const auto& outputSet = layouts.getMainOutputChannelSet();
	if (outputSet.isDisabled())
		return false;

#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true; // Allow all other valid layouts.
}

void GramoVoice::setHornLength(float length)
{
	hornLength = length; // Set the horn length

	//gramoHorn.setLength(Length); // Set the length of the horn in the STK model
}

float GramoVoice::gramoPressure()
{
	float breathPressure = maxPressure * adsr.tick(); // Apply ADSR envelope to breath pressure
	breathPressure += vibratoGain * vibrato.tick(); // Apply vibrato effect

	float mouthPressure = 0.3 * breathPressure; // Mouth pressure is 30% of breath pressure
	float borePressure = 0.85 * delayLine.lastOut(); // Bore pressure is 85% of the last output of the delay line
	float deltaPressure = mouthPressure - borePressure; // Calculate the pressure difference
	//stylusFilter.setCutoff(stylusFilterCutoff); // Use member variable
	stylusFilter.setLowPass(stylusFilterCutoff, 0.75); // Set the cutoff frequency of the stylus filter
	deltaPressure = stylusFilter.tick(deltaPressure);
	
	// Non-linear saturation.
	deltaPressure = powf(deltaPressure, 1.0f + nonLinearityAmount * 2.0f); // Apply non-linearity
	deltaPressure = juce::jlimit(0.0f, 1.0f, deltaPressure); // Limit the pressure difference to a range of 0 to 1

	// Noise shaping (simplified)
	float noise = juce::Random::getSystemRandom().nextFloat() * noiseLevel; // Generate random noise
	noise *= (1.0f - deltaPressure); // Less noise when pressure is high
	if (juce::Random::getSystemRandom().nextFloat() < 0.01f) noise *= 5.0f; // Occasional crackle
	deltaPressure += noise;

	// The following input scattering assumes the mouthPressure = area.
	lastFrame_[0] = deltaPressure * mouthPressure + (1.0 - deltaPressure) * borePressure;
	lastFrame_[0] = delayLine.tick(dcBlock.tick(lastFrame_[0]));

	return lastFrame_[0];
}

void GramoVoice::setStylusFilterCutoff(float cutoff) {stylusFilterCutoff = cutoff;} // Set the cutoff frequency of the stylus filter
void GramoVoice::setNonLinearity(float amount) { nonLinearityAmount = amount; } // Set the non-linearity amount
void GramoVoice::setNoiseLevel(float level) { noiseLevel = level; } // Set the noise level
void GramoVoice::setHornDiameter(float diameter) { hornDiameter = diameter; }
void GramoVoice::setHornStiffness(float stiffness) { hornStiffness = stiffness; }

void GramoVoice::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) {
	// Your implementation here
	// e.g., gramoHorn.noteOn(frequency, amplitude);
}

void GramoVoice::noteOff(stk::StkFloat amplitude) {
	// Your implementation here
	// e.g., gramoHorn.noteOff(amplitude);
}

stk::StkFloat GramoVoice::tick(unsigned int channel) {
	// Your implementation here
	return 0.0; // Or the actual output
}

stk::StkFrames& GramoVoice::tick(stk::StkFrames& frames, unsigned int channel) {
	// Your implementation here
	return frames;
}