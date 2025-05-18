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
}

GramoVoice::~GramoVoice()
{
}

void GramoVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Prepare to play method for the audio processor JUCE method
}

void GramoVoice::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}


void GramoVoice::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

}

void GramoVoice::paint(juce::Graphics& g)
{
	// This demo code just fills the component's background and
	// draws some placeholder text to get you started.
	g.fillAll(juce::Colours::beige);
}

void GramoVoice::sliderValueChanged(juce::Slider* slider)
{
	
}