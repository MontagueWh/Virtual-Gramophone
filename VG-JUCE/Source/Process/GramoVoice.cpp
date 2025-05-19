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

    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.
    gramophoneParametersSetup(TEXT_BOX_SIZE);

	gramoStylus;
	gramoSoundbox;
	gramoHorn;
}

GramoVoice::~GramoVoice()
{
}

void GramoVoice::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	gramoStylus.prepareToPlay(samplesPerBlockExpected, sampleRate);
	gramoSoundbox.prepareToPlay(samplesPerBlockExpected, sampleRate);
	gramoHorn.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void GramoVoice::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

	// Process the audio data through the components
	gramoStylus.getNextAudioBlock(bufferToFill);
	gramoSoundbox.getNextAudioBlock(bufferToFill);
	gramoHorn.getNextAudioBlock(bufferToFill);
}

void GramoVoice::sliderValueChanged(juce::Slider* slider)
{

}

void GramoVoice::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.

	gramoStylus.releaseResources();
	gramoSoundbox.releaseResources();
	gramoHorn.releaseResources();
}

void GramoVoice::paint(juce::Graphics& g)
{
    
    g.drawFittedText("HORN STIFFNESS", hornStiffnessTextSection, juce::Justification::left, 1);
    g.drawFittedText("HORN DIAMETER", hornDiameterTextSection, juce::Justification::left, 1);
    g.drawFittedText("HORN LENGTH", hornLengthTextSection, juce::Justification::left, 1);
}

void GramoVoice::setupSections()
{
    hornStiffnessSection = interfaceSection.removeFromTop(sectionHeight);
    hornStiffnessTextSection = hornStiffnessSection.removeFromLeft(40);

    hornDiameterSection = interfaceSection.removeFromTop(sectionHeight);
    hornDiameterTextSection = hornDiameterSection.removeFromLeft(40);

    hornLengthSection = interfaceSection.removeFromTop(sectionHeight);
    hornLengthTextSection = hornLengthSection.removeFromLeft(40);
}

void GramoVoice::resized()
{
    // This method is called when the component is resized.
    // Use this to lay out any child components that you want to add.

    frequencyParam

        auto inputGainArea = row1.removeFromLeft(knobWidth);
    inputGainLabel.setBounds(inputGainArea.removeFromTop(20));
    inputGainSlider.setBounds(inputGainArea);

    auto mixArea = row1;
    mixLabel.setBounds(mixArea.removeFromTop(20));
    mixSlider.setBounds(mixArea);

    area.removeFromTop(20);

    // Second row - 3 controls
    auto row2 = area.removeFromTop(150);
    knobWidth = row2.getWidth() / 3;

    auto vibratoFreqArea = row2.removeFromLeft(knobWidth);
    vibratoFreqLabel.setBounds(vibratoFreqArea.removeFromTop(20));
    vibratoFreqSlider.setBounds(vibratoFreqArea);

    auto vibratoGainArea = row2.removeFromLeft(knobWidth);
    vibratoGainLabel.setBounds(vibratoGainArea.removeFromTop(20));
    vibratoGainSlider.setBounds(vibratoGainArea);

    auto slideArea = row2;
    slideLabel.setBounds(slideArea.removeFromTop(20));
    slideSlider.setBounds(slideArea);


    std::string GramoSuite = "../Source/UI/GramoSuite.fbx";
}

void GramoVoice::gramophoneParametersSetup(const int TEXT_BOX_SIZE)
{
    // Set up slider appearances
    pressureParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    pressureParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    pressureParam.addListener(this);

    inputGainParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    inputGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    inputGainParam.addListener(this);

    mixParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mixParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    mixParam.addListener(this);

    vibratoFreqParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    vibratoFreqParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoFreqParam.addListener(this);

    vibratoGainParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    vibratoGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoGainParam.addListener(this);

    pitchShiftParam.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    pitchShiftParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    pitchShiftParam.addListener(this);

    // Add components
    addAndMakeVisible(pressureParam);
    addAndMakeVisible(inputGainParam);
    addAndMakeVisible(mixParam);
    addAndMakeVisible(vibratoFreqParam);
    addAndMakeVisible(vibratoGainParam);
    addAndMakeVisible(pitchShiftParam);

    addAndMakeVisible(pressureLabel);
    addAndMakeVisible(inputGainLabel);
    addAndMakeVisible(mixLabel);
    addAndMakeVisible(vibratoFreqLabel);
    addAndMakeVisible(vibratoGainLabel);
    addAndMakeVisible(pitchShiftLabel);

    // Parameter attachments
    pressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PRESSURE", pressureParam);
    inputGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "INPUT_GAIN", inputGainParam);
    mixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixParam);
    vibratoFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_FREQ", vibratoFreqParam);
    vibratoGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_GAIN", vibratoGainParam);
    pitchShiftAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PITCH_SHIFT", pitchShiftParam);
}

void GramoVoice::gramophoneParametersSetup(const int TEXT_BOX_SIZE)
{
    // Add slider for the gramophone horn's stiffness
    hornStiffnessParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    hornStiffnessParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    hornStiffnessParam.addListener(this);
    addAndMakeVisible(hornStiffnessParam);
    hornStiffnessAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HORN_STIFFNESS", hornStiffnessParam);

    hornDiameterParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    hornDiameterParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    hornDiameterParam.addListener(this);
    addAndMakeVisible(hornDiameterParam);
    hornDiameterAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HORN_DIAMETER", hornDiameterParam);
}