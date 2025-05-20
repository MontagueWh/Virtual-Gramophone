/*
  ==============================================================================

    StylusEmulation.cpp
    Created: 17 May 2025 6:50:05pm
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StylusEmulation.h"

//==============================================================================
StylusEmulation::StylusEmulation()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    vinylTarget = 0.0f;
    stylusOutput = 0.0f;
    stylusFilterState[0] = 0.0f;
    stylusFilterState[1] = 0.0f;
}

StylusEmulation::~StylusEmulation()
{
}

void StylusEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
}

void StylusEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // This function is called by the host to fill the output buffer with audio data.
}

void StylusEmulation::releaseResources()
{
    // When playback stops, you can use this as an opportunity
    // to free up any spare memory, etc.

	for (int i = 0; i <= 2; i++) stylusFilterState[1] = 0.0f;
}

void StylusEmulation::paint (juce::Graphics& g)
{

}

void StylusEmulation::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
}

void StylusEmulation::processPressureDifference(float pressureDiff)
{
    float filterOutput = 0.7f * stylusFilterState[0] + 0.3f * pressureDiff;
    stylusFilterState[0] = filterOutput;
    stylusFilterState[1] = pressureDiff;
}