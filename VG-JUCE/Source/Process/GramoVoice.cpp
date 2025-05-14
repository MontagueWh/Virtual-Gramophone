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

void GramoVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// This function is called before playback starts, and is where you can set up any
	// resources that your audio source needs. For example, you might want to allocate
	// memory for buffers or prepare any DSP objects that you are using.
}
void GramoVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..

	setSampleRate(sampleRate); // Set the sample rate
	Stk::setSampleRate(sampleRate); // Set the sample rate for STK

	handleImpulseResponse(sampleRate, samplesPerBlock); // Handle the impulse response
}

void GramoVoice::handleImpulseResponse(double sampleRate, int samplesPerBlock) {
	audioFormatManager.registerBasicFormats();
	juce::File irFile = /* your IR file path */;
	juce::AudioFormatReader* reader = audioFormatManager.createReaderFor(irFile);

	float numOutChannels = getTotalNumOutputChannels();

	if (reader) {
		impulseResponse.setSize(numOutChannels, reader->lengthInSamples);
		reader->read(&impulseResponse, 0, reader->lengthInSamples, 0, true, true);
		delete reader;

		juce::dsp::ProcessSpec spec;
		spec.sampleRate = sampleRate;
		spec.maximumBlockSize = samplesPerBlock;
		spec.numChannels = (juce::uint32)numOutChannels;

		convolution.prepare(spec);

		juce::dsp::Convolution::Stereo stereoMode = (numOutChannels == 1 && impulseResponse.getNumChannels() <= 2)
			? juce::dsp::Convolution::Stereo::no
			: juce::dsp::Convolution::Stereo::yes;

		convolution.loadImpulseResponse(
			impulseResponse,
			impulseResponse.getNumChannels() > 1, // true for multichannel
			false,                                // do not trim
			impulseResponse.getNumSamples()
		);
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