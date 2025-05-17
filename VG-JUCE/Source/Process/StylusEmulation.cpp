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
    // components that your component contains..

}


float StylusEmulation::excitationSetup()
{
    float excitationPressure = maxPressure * adsr.tick();
    excitationPressure += vibratoGain * vibrato.tick();

    float stylusPressure = 0.3 * excitationPressure;
    float borePressure = 0.85 * delayLine.lastOut(); // the pressure exerted by compressed air within a cylindrical bore/cavity, such as the gramophone horn
    float deltaPressure = stylusPressure - borePressure; // Differential pressure.

    // Apply stylus filter
    deltaPressure = stylusFilter.tick(deltaPressure); // Force - > position.

    deltaPressure *= deltaPressure; // Basic position to area mapping.
    if (deltaPressure > 1.0) deltaPressure = 1.0; // Non-linear saturation.

    // The following input scattering assumes the stylusPressure = area.
    lastFrame_[0] = deltaPressure * stylusPressure + (1.0 - deltaPressure) * borePressure;
    lastFrame_[0] = delayLine.tick(dcBlock.tick(lastFrame_[0]));

    return lastFrame_[0];
}

float StylusEmulation::stylusPressure(float inputSample)
{
    // 1. Stylus Vibration (Filtered Noise)
    float stylusVibration = noiseSource.tick(inputSample);
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
