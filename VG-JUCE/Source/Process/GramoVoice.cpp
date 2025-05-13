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

	Stk::setSampleRate(juce::AudioProcessor::getSampleRate());
}

GramoVoice::~GramoVoice()
{
}

void GramoVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..


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
			channelData[sample] = 0.0f; // Clear the output buffer
		}
	}
}