/*
  ==============================================================================

    HornEmulation.cpp
    Created: 17 May 2025 6:50:39pm
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HornEmulation.h"

//==============================================================================
HornEmulation::HornEmulation()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	updateHornParameters();

    // ADSR Setup for brass stk
    adsr.setTarget(1.0);
    adsr.setAttackRate(0.02);
    adsr.setDecayRate(0.2);
    adsr.setSustainLevel(0.6);


    setupBodyResonance(); // Initialise body resonance filter
}

HornEmulation::~HornEmulation()
{
}

void HornEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	Stk::setSampleRate(sampleRate);

	// Convolution setup
	juce::dsp::ProcessSpec specConvolution;
	specConvolution.sampleRate = sampleRate;
	specConvolution.maximumBlockSize = samplesPerBlockExpected;
	specConvolution.numChannels = 1;

	for (int i = 0; i <= 10; i++) convolution[i].prepare(specConvolution); // Prepare the convolution processor

	handleImpulseResponse(sampleRate, samplesPerBlockExpected); // Handle the impulse response
}

void HornEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// This function is called by the host to fill the output buffer with audio data.
}

void HornEmulation::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void HornEmulation::paint (juce::Graphics& g)
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
    g.drawText ("HornEmulation", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void HornEmulation::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void HornEmulation::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) {
    // Your implementation here
    // e.g., brassHorn.noteOn(frequency, amplitude);
}

void HornEmulation::noteOff(stk::StkFloat amplitude) {
    // Your implementation here
    // e.g., brassHorn.noteOff(amplitude);
}

stk::StkFloat HornEmulation::tick(unsigned int channel) {
    // Your implementation here
    return 0.0; // Or the actual output
}

stk::StkFrames& HornEmulation::tick(stk::StkFrames& frames, unsigned int channel) {
    // Your implementation here
    return frames;
}

void HornEmulation::setupBodyResonance()
{
	// Configure a body resonance filter (BP filter)
	stk::BiQuad bodyFilter;
	float bodyFrequency = 500.0f; // Resonant frequency in Hz
	float bodyQfactor = 1.5f; // Q factor for the body resonance filter
	bodyFilter.setResonance(bodyFrequency, bodyQfactor, true); // Set the resonance filter
}

void HornEmulation::updateHornParameters()
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

	brassHorn.setFrequency(effectiveFreq); // Set the frequency of the horn

	DBG("Horn Stiffness: " << hornStiffness);
	DBG("Horn Frequency: " << effectiveFreq);
	DBG("Horn Diameter: " << hornDiameter);
}

void HornEmulation::handleImpulseResponse(double sampleRate, int samplesPerBlock)
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
