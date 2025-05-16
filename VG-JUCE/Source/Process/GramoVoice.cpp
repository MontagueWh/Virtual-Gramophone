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

	float wavelength = 2.f * 0.25; // Wavelength of the sound wave
	float soundSpeed = 343.0f; // Speed of sound in air in m/s
	float freq = soundSpeed / wavelength; // Frequency of the sound wave

	OpenGLContext::attachTo(*this); // Attach OpenGL context to this component

	Stk::setSampleRate(sampleRateVal); // Or whatever default you want
	gramoHorn.setFrequency(freq); // Set the frequency of the horn
}

GramoVoice::~GramoVoice()
{
	OpenGLContext::detach(); // Detach OpenGL context from this component
}

void GramoVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Prepare to play method for the audio processor JUCE method
}
void GramoVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Prepare to play method for the audio source JUCE method
	sampleRateVal = sampleRate; // Share the sample rate with other functions

	setSampleRate(sampleRate); // Set the sample rate
	Stk::setSampleRate(sampleRate); // Set the sample rate for STK

	// Convolution setup
	juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = 1;

	convolution.prepare(spec); // Prepare the convolution processor

	handleImpulseResponse(sampleRate, samplesPerBlock); // Handle the impulse response

	// Initialise STK Brass parameters. These need replacing with working objects.
}

void GramoVoice::handleImpulseResponse(double sampleRate, int samplesPerBlock)
{
	audioFormatManager.registerBasicFormats();

	juce::File irFiles[11]; // Array of impulse response files
	irFiles[0] = "../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Initial Stage/Attack Initial Quiet.wav"; // quiet attack initial impulse response
	irFiles[1] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Initial Stage/Attack Initial Loud.wav"; // loud attack initial impulse response
	irFiles[2] = "../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Halfway Stage/Halfway Attack Quiet.wav"; // quiet halfway attack impulse response
	irFiles[3] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Halfway Stage/Halfway Attack Loud.wav"; // loud halfway attack impulse response
	irFiles[4] = "../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Decay/Decay Quiet.wav"; // quiet decay impulse response
	irFiles[5] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Decay/Decay Loud.wav"; // loud decay impulse response
	irFiles[6] = "../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Sustain/Sustain Quiet.wav"; // quiet sustain impulse response
	irFiles[7] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Sustain/Sustain Loud.wav"; // loud sustain impulse response
	irFiles[8] = "../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Release/Release Quiet.wav"; // quiet release impulse response
	irFiles[9] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Initial Stage/Release Initial Loud.wav"; // loud halfway release impulse response
	irFiles[10] = "../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Halfway Stage/Halfway Release Loud.wav"; // loud halfway release impulse response

	juce::AudioFormatReader* reader[11];
	for (int i = 0; i <= 11; i++)
	{
		audioFormatManager.createReaderFor(irFiles[i]);

		if (reader[i])
		{
			impulseResponse[i].setSize(1, reader[i]->lengthInSamples); // Always mono
			reader[i]->read(&impulseResponse[i], 0, reader[i]->lengthInSamples, 0, true, true);
			delete reader;

			convolution[i].loadImpulseResponse(
				impulseResponse[i],
				juce::dsp::Convolution::Stereo::no, // Always mono processing
				juce::dsp::Convolution::Trim::no,
				impulseResponse[i].getNumSamples());
		}
	}
}

void GramoVoice::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void GramoVoice::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::dsp::AudioBlock<float> audioBlock(buffer);
	for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
	{
		auto* channelData = audioBlock.getChannelPointer(channel);
		for (size_t sample = 0; sample < audioBlock.getNumSamples(); ++sample)
		{
			channelData[sample] = gramoPressure(channelData[sample]);
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

float GramoVoice::gramoPressure(float inputSample)
{
	// STK's internal variables
	float breathPressure = maxPressure * adsr.tick();
	breathPressure += vibratoGain * vibrato.tick();

	float mouthPressure = 0.3 * breathPressure;
	float borePressure = 0.85 * delayLine.lastOut();
	float deltaPressure = mouthPressure - borePressure; // Differential pressure.

	// Apply stylus filter
	stylusFilter.tick(deltaPressure); // Force - > position.

	deltaPressure *= deltaPressure; // Basic position to area mapping.
	if (deltaPressure > 1.0)
		deltaPressure = 1.0; // Non-linear saturation.

	// The following input scattering assumes the mouthPressure = area.
	lastFrame_[0] = deltaPressure * mouthPressure + (1.0 - deltaPressure) * borePressure;
	lastFrame_[0] = delayLine.tick(dcBlock.tick(lastFrame_[0]));

	return lastFrame_[0];
}

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

void GramoVoice::openGlCalculator()
{
	OpenGLContext::makeActive(); // Make the OpenGL context active
	
	float hornDiameter = 0.25f; // Diameter of the horn
	float hornStiffness = 4.5f; // Stiffness of the horn (brass)
	float hornLength = 0.75;
}