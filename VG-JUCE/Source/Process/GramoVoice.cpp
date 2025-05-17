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


/*float GramoVoice::excitationSetup()
{
	float excitationPressure = gramoStylus.maxPressure * gramoHorn.adsr.tick();
	excitationPressure += vibratoGain * gramoStylus.vibrato.tick();

	float stylusPressure = 0.3 * excitationPressure;
	float borePressure = 0.85 * gramoHorn.delayLine.lastOut(); // The pressure exerted by compressed air within a cylindrical bore/cavity, which in this case is the gramophone horn
	float deltaPressure = stylusPressure - borePressure; // Differential pressure.

	// Apply stylus filter
	deltaPressure = gramoStylus.stylusFilter.tick(deltaPressure); // Force - > position.

	deltaPressure *= deltaPressure; // Basic position to area mapping.
	if (deltaPressure > 1.0) deltaPressure = 1.0; // Non-linear saturation.

	// The following input scattering assumes the stylusPressure = area.
	lastFrame_[0] = deltaPressure * stylusPressure + (1.0 - deltaPressure) * borePressure;
	lastFrame_[0] = delayLine.tick(dcBlock.tick(lastFrame_[0]));

	return lastFrame_[0];
}*/