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

	updateHornParameters();
}

GramoVoice::~GramoVoice()
{
}

void GramoVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Prepare to play method for the audio processor JUCE method
}
void GramoVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Prepare to play method for the audio source JUCE method
	sampleRateVal = sampleRate;

	setSampleRate(sampleRate);
	Stk::setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock), 1 };

	for (auto& conv : convolution) conv.prepare(spec); // Prepare the convolution objects

	handleImpulseResponse(sampleRate, samplesPerBlock); // Handle the impulse response

	// Initialise STK Brass parameters. These need replacing with working objects.
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

void GramoVoice::handleImpulseResponse(double sampleRate, int samplesPerBlock)
{
	audioFormatManager.registerBasicFormats();

	juce::AudioFormatReader* reader = nullptr;

	juce::File irFiles[11] =
	{
		"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Initial Stage/Attack Initial Quiet.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Initial Stage/Attack Initial Loud.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Halfway Stage/Halfway Attack Quiet.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Halfway Stage/Halfway Attack Loud.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Decay/Decay Quiet.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Decay/Decay Loud.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Sustain/Sustain Quiet.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Sustain/Sustain Loud.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Release/Release Quiet.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Initial Stage/Release Initial Loud.wav",
		"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Halfway Stage/Halfway Release Loud.wav"
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

float GramoVoice::gramoPressure(float inputSample)
{
	// STK's internal variables
	float breathPressure = maxPressure * adsr.tick();
	breathPressure += vibratoGain * vibrato.tick();

	float mouthPressure = 0.3 * breathPressure;
	float borePressure = 0.85 * delayLine.lastOut(); // Previous output of the delay line.
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

void GramoVoice::updateHornParameters()
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

	gramoHorn.setFrequency(effectiveFreq); // Set the frequency of the horn

	DBG("Horn Stiffness: " << hornStiffness);
	DBG("Horn Frequency: " << effectiveFreq);
	DBG("Horn Diameter: " << hornDiameter);
}