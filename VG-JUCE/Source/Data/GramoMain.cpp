/*
  ==============================================================================

    GramoMain.cpp
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GramoMain.h"

//==============================================================================
GramoMain::GramoMain()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.


    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.

	setupStylusParams(TEXT_BOX_SIZE);
	setupSoundboxParams(TEXT_BOX_SIZE);
	setupHornParams(TEXT_BOX_SIZE);

	gramoStylus; // Initialise the stylus emulation
	gramoSoundbox; // Initialise the soundbox emulation
	gramoHorn; // Initialise the horn emulation

	//std::string GramoSuite = "../Source/UI/GramoSuite.fbx";
}

void GramoMain::setupStylusParams(const int TEXT_BOX_SIZE)
{
	// Set up for the stylus parameters
	stylusPressureParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	stylusPressureParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	stylusPressureParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(stylusPressureParam); // Makes the slider visible in the editor.
	stylusPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "stylusPressure", stylusPressureParam); // Attach the slider to the parameter tree.

	vinylFilterFreqParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	vinylFilterFreqParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	vinylFilterFreqParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(vinylFilterFreqParam); // Makes the slider visible in the editor.
	vinylFilterFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "vinylFilterFreq", vinylFilterFreqParam); // Attach the slider to the parameter tree.

	pitchShiftParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	pitchShiftParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	pitchShiftParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(pitchShiftParam); // Makes the slider visible in the editor.
	pitchShiftAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "pitchShift", pitchShiftParam); // Attach the slider to the parameter tree.
}

GramoMain::~GramoMain()
{
}

void GramoMain::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	gramoStylus.prepareToPlay(samplesPerBlockExpected, sampleRate);
	gramoSoundbox.prepareToPlay(samplesPerBlockExpected, sampleRate);
	gramoHorn.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void GramoMain::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

	// Process the audio data through the components
	gramoStylus.getNextAudioBlock(bufferToFill);
	gramoSoundbox.getNextAudioBlock(bufferToFill);
	gramoHorn.getNextAudioBlock(bufferToFill);
}

void GramoMain::releaseResources()
{
	// When playback stops, you can use this as an opportunity
	// to free up any spare memory, etc.
}

void GramoMain::paint(juce::Graphics& g)
{
    setupSections();

	g.setFont(18.0f); // Sets the font size for the text.
	g.drawFittedText("STYLUS_PRESSURE", stylusPressureTextSection, juce::Justification::left, 1); // Draws the text for the stylus pressure section.
	g.drawFittedText("VINYL_FILTER_FREQ", vinylFilterFreqTextSection, juce::Justification::left, 1); // Draws the text for the vinyl filter frequency section.
	g.drawFittedText("PITCH_SHIFT", pitchShiftTextSection, juce::Justification::left, 1); // Draws the text for the pitch shift section.
	
	g.drawFittedText("SOUNDBOX_PRESSURE", soundboxPressureTextSection, juce::Justification::left, 1); // Draws the text for the soundbox pressure section.
	g.drawFittedText("NOISE_GAIN", noiseGainTextSection, juce::Justification::left, 1); // Draws the text for the noise gain section.
	g.drawFittedText("VIBRATO_DEPTH", vibratoDepthTextSection, juce::Justification::left, 1); // Draws the text for the vibrato depth section.
	g.drawFittedText("VIBRATO_FREQ", vibratoFreqTextSection, juce::Justification::left, 1); // Draws the text for the vibrato frequency section.
	g.drawFittedText("VIBRATO_GAIN", vibratoGainTextSection, juce::Justification::left, 1); // Draws the text for the vibrato gain section.
	g.drawFittedText("VIBRATO_MIX", vibratoMixTextSection, juce::Justification::left, 1); // Draws the text for the vibrato mix section.

	g.drawFittedText("HORN_STIFFNESS", hornStiffnessTextSection, juce::Justification::left, 1); // Draws the text for the horn stiffness section.
	g.drawFittedText("HORN_DIAMETER", hornDiameterTextSection, juce::Justification::left, 1); // Draws the text for the horn diameter section.
	g.drawFittedText("HORN_LENGTH", hornLengthTextSection, juce::Justification::left, 1); // Draws the text for the horn length section.
}

void GramoMain::setupSections()
{
    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.
	pictureSection = r.removeFromBottom(200); // Allocates the picture section.
    
    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.
    int sectionHeight = interfaceSection.getHeight() / 4; // Divides the interface into four sections.
    constexpr int textSectionWidth = 40; // Width for the text labels.

	stylusUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the stylus UI sections.
	soundboxUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the soundbox UI sections.
    hornUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the horn UI sections.
}

void GramoMain::stylusUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)
{
    stylusPressureSection = interfaceSection.removeFromTop(sectionHeight);
    stylusPressureTextSection = stylusPressureSection.removeFromRight(textSectionWidth);

    vinylFilterFreqSection = interfaceSection.removeFromTop(sectionHeight);
    vinylFilterFreqTextSection = vinylFilterFreqSection.removeFromRight(textSectionWidth);

    pitchShiftSection = interfaceSection.removeFromTop(sectionHeight);
    pitchShiftTextSection = pitchShiftSection.removeFromRight(textSectionWidth);
}

void GramoMain::soundboxUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)
{
    soundboxPressureSection = interfaceSection.removeFromTop(sectionHeight);
    soundboxPressureTextSection = soundboxPressureSection.removeFromRight(textSectionWidth);

    noiseGainSection = interfaceSection.removeFromTop(sectionHeight);
    noiseGainTextSection = noiseGainSection.removeFromRight(textSectionWidth);

    vibratoDepthSection = interfaceSection.removeFromTop(sectionHeight);
    vibratoDepthTextSection = vibratoDepthSection.removeFromRight(textSectionWidth);

    vibratoFreqSection = interfaceSection.removeFromTop(sectionHeight);
    vibratoFreqTextSection = vibratoFreqSection.removeFromRight(textSectionWidth);

    vibratoGainSection = interfaceSection.removeFromTop(sectionHeight);
    vibratoGainTextSection = vibratoGainSection.removeFromRight(textSectionWidth);

    vibratoMixSection = interfaceSection.removeFromTop(sectionHeight);
    vibratoMixTextSection = vibratoMixSection.removeFromRight(textSectionWidth);
}

void GramoMain::hornUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)
{
    // Allocates sections for sliders and their labels.
    hornStiffnessSection = interfaceSection.removeFromTop(sectionHeight);
    hornStiffnessTextSection = hornStiffnessSection.removeFromRight(textSectionWidth);

    hornDiameterSection = interfaceSection.removeFromTop(sectionHeight);
    hornDiameterTextSection = hornDiameterSection.removeFromRight(textSectionWidth);

    hornLengthSection = interfaceSection.removeFromTop(sectionHeight);
    hornLengthTextSection = hornLengthSection.removeFromRight(textSectionWidth);
}

void GramoMain::setupHornParams(const int TEXT_BOX_SIZE)
{
	// Set up for the horn parameters	
	hornStiffnessParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	hornStiffnessParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	hornStiffnessParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(hornStiffnessParam); // Makes the slider visible in the editor.
	hornStiffnessAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "hornStiffness", hornStiffnessParam); // Attach the slider to the parameter tree.

	hornDiameterParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	hornDiameterParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	hornDiameterParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(hornDiameterParam); // Makes the slider visible in the editor.
	hornDiameterAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "hornDiameter", hornDiameterParam); // Attach the slider to the parameter tree.

	hornLengthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	hornLengthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	hornLengthParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(hornLengthParam); // Makes the slider visible in the editor.
	hornLengthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "hornLength", hornLengthParam); // Attach the slider to the parameter tree.
}

void GramoMain::setupSoundboxParams(const int TEXT_BOX_SIZE)
{
	// Set up for the soundbox parameters
	soundboxPressureParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	soundboxPressureParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	soundboxPressureParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(soundboxPressureParam); // Makes the slider visible in the editor.
	soundboxPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "soundboxPressure", soundboxPressureParam); // Attach the slider to the parameter tree.

	noiseGainParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	noiseGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	noiseGainParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(noiseGainParam); // Makes the slider visible in the editor.
	noiseGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "noiseGain", noiseGainParam); // Attach the slider to the parameter tree.

	vibratoDepthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	vibratoDepthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	vibratoDepthParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(vibratoDepthParam); // Makes the slider visible in the editor.
	vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "vibratoDepth", vibratoDepthParam); // Attach the slider to the parameter tree.

	vibratoFreqParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	vibratoFreqParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	vibratoFreqParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(vibratoFreqParam); // Makes the slider visible in the editor.
	vibratoFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "vibratoFreq", vibratoFreqParam); // Attach the slider to the parameter tree.

	vibratoGainParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
	vibratoGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
	vibratoGainParam.setRange(0.0f, 1.0f); // Sets the range of the slider.
	addAndMakeVisible(vibratoGainParam); // Makes the slider visible in the editor.
	vibratoGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "vibratoGain", vibratoGainParam); // Attach the slider to the parameter tree.
}

void GramoMain::resized()
{
    // This method is called when the component is resized.
    // Use this to lay out any child components that you want to add.

    setupSections();
}

void GramoMain::sliderValueChanged(juce::Slider* slider)
{
	repaint();
}