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

	addedNoiseSetup(spec, sampleRate, samplesPerBlock);

	// Convolution setup
	juce::dsp::ProcessSpec specConvolution;
	specConvolution.sampleRate = sampleRate;
	specConvolution.maximumBlockSize = samplesPerBlock;
	specConvolution.numChannels = 1;

	for (int i = 0; i <= 10; i++) convolution[i].prepare(specConvolution); // Prepare the convolution processor

	handleImpulseResponse(sampleRate, samplesPerBlock); // Handle the impulse response
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
			channelData[sample] = stylusPressure(channelData[sample]);
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