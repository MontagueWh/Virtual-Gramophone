/*
  ==============================================================================

    SoundboxEmulation.cpp
    Created: 18 May 2025 12:17:28pm
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SoundboxEmulation.h"

//==============================================================================
SoundboxEmulation::SoundboxEmulation()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    vibratoFrequency = 5.925f;
    vibratoGain = 0.1f;
    vibratoPhase = 0.0f;
}

SoundboxEmulation::~SoundboxEmulation()
{
}

void SoundboxEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    configureVibrato(sampleRate);
}

void SoundboxEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        bufferToFill.buffer->clear (i, bufferToFill.startSample, bufferToFill.numSamples);
    // Process the audio data here
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float vibratoEffect = configureVibrato(getSampleRate());
        // Apply the vibrato effect to the audio buffer
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
            channelData[sample] += vibratoEffect;
        }
    }
}

void SoundboxEmulation::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.

    vibratoPhase = 0.0f;
}

void SoundboxEmulation::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SoundboxEmulation::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

float SoundboxEmulation::configureVibrato(double sampleRate)
{
    vibratoPhase += vibratoFrequency / sampleRate;
    if (vibratoPhase >= 1.0f) vibratoPhase -= 1.0f;
    return vibratoGain * std::sin(2.0f * std::numbers::pi * vibratoPhase);
}
