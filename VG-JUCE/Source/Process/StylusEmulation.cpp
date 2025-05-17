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

}

StylusEmulation::~StylusEmulation()
{
}

void StylusEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlockExpected), 1};
    
    addedNoiseSetup(spec, sampleRate, samplesPerBlockExpected);
}

void StylusEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // This function is called by the host to fill the output buffer with audio data.
}

void StylusEmulation::releaseResources()
{
    // When playback stops, you can use this as an opportunity
    // to free up any spare memory, etc.
}

void StylusEmulation::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("StylusEmulation", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void StylusEmulation::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
}

float StylusEmulation::stylusPressure(float inputSample)
{
    // 1. Stylus Vibration (Filtered Noise)
	float stylusVibration = noiseSource.tick(); // Add noise to the input sample
    stylusVibration = noiseFilter.processSample(stylusVibration);
}

void StylusEmulation::addedNoiseSetup(juce::dsp::ProcessSpec& spec, double sampleRate, int samplesPerBlock)
{
    // Noise Source Setup
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    noiseFilter.prepare(spec);
    noiseFilter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 4000.0f);
}
