/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h" // Includes the header file for the plugin editor.
#include "PluginProcessor.h" // Includes the header file for the plugin processor.


constexpr float LINE_THICKNESS = 4.0f; // Defines the thickness of lines drawn in the editor.

//==============================================================================
// Constructor for the plugin editor.
VirtualGramoAudioProcessorEditor::VirtualGramoAudioProcessorEditor(VirtualGramoAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), info_button_(juce::Colours::darkgrey)
{
    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.

    additionalEffectsParamsSetup(TEXT_BOX_SIZE);
    wetDryParamSetup(TEXT_BOX_SIZE);

    gramophoneParametersSetup(TEXT_BOX_SIZE);

    // Adds the info button to the editor.
    info_button_.addToEditor(this);

	//addAndMakeVisible(gramoModelLoader); // Adds the model loader to the editor.

    setSize(1500, 1500); // Sets the initial size of the editor window.
	setResizable(true, true);
}

// Destructor for the plugin editor.
VirtualGramoAudioProcessorEditor::~VirtualGramoAudioProcessorEditor()
{
    
}

//==============================================================================
// Paints the editor's GUI components.
void VirtualGramoAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::beige);

    g.setColour(juce::Colour(0xff123456));
    g.setFont(40.0f);
    g.drawFittedText("Virtual Gramophone", getLocalBounds(), juce::Justification::centredTop, 1);

    setupSections();

    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.
    gramophoneHornParamsSetup(TEXT_BOX_SIZE);

    g.setFont(18.0f);
    g.drawFittedText("TONE", toneTextSection, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibratoTextSection, juce::Justification::left, 1);
    g.drawFittedText("DRY", wetDryTextSection, juce::Justification::left, 1);

    g.drawFittedText("HORN STIFFNESS", hornStiffnessTextSection, juce::Justification::left, 1);
    g.drawFittedText("HORN DIAMETER", hornDiameterTextSection, juce::Justification::left, 1);
    g.drawFittedText("HORN LENGTH", hornLengthTextSection, juce::Justification::left, 1);
}

// Converts a slider's value to an alpha (transparency) value.
float VirtualGramoAudioProcessorEditor::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

// Handles resizing and layout of GUI components.
void VirtualGramoAudioProcessorEditor::resized()
{
    info_button_.button.setBounds(getWidth() - 35, 10, 20, 20); // Positions the info button.
    info_button_.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100); // Positions the info text.
    setupSections(); // Updates the layout sections.
    compressThreshParam.setBounds(compressSection); // Positions the compression slider.
    toneParam.setBounds(toneSection); // Positions the tone slider.
    vibratoDepthParam.setBounds(vibratoDepthSection); // Positions the vibrato slider.
    vibratoRateParam.setBounds(vibratoRateSection); // Positions the vibrato rate slider.
    wetDryParam.setBounds(wetDrySection); // Positions the mix slider.


    frequencyLabel.setBounds(freqArea.removeFromTop(20));
    frequencySlider.setBounds(freqArea);

    auto pressureArea = row1.removeFromLeft(knobWidth);
    pressureLabel.setBounds(pressureArea.removeFromTop(20));
    pressureSlider.setBounds(pressureArea);

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

// Sets up the layout sections for the GUI.
void VirtualGramoAudioProcessorEditor::setupSections()
{    
    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.
    topSection = r.removeFromTop(50); // Allocates the top section.
    pictureSection = r.removeFromLeft(310); // Allocates the picture section.

    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.
    int sectionHeight = interfaceSection.getHeight() / 4; // Divides the interface into four sections.
    constexpr int textSectionWidth = 40; // Width for the text labels.

    // Allocates sections for sliders and their labels.
    compressSection = interfaceSection.removeFromTop(sectionHeight);
    compressTextSection = compressSection.removeFromLeft(textSectionWidth);

	toneSection = interfaceSection.removeFromTop(sectionHeight);
	toneTextSection = toneSection.removeFromLeft(textSectionWidth);

	vibratoDepthSection = interfaceSection.removeFromTop(sectionHeight);
	vibratoTextSection = vibratoDepthSection.removeFromLeft(textSectionWidth);
	vibratoRateSection = interfaceSection.removeFromTop(sectionHeight);

    wetDrySection = interfaceSection;
    wetDrySection = interfaceSection.removeFromTop(textSectionWidth);

    hornStiffnessSection = interfaceSection.removeFromTop(sectionHeight);
    hornStiffnessTextSection = hornStiffnessSection.removeFromLeft(40);

    hornDiameterSection = interfaceSection.removeFromTop(sectionHeight);
    hornDiameterTextSection = hornDiameterSection.removeFromLeft(40);

    hornLengthSection = interfaceSection.removeFromTop(sectionHeight);
    hornLengthTextSection = hornLengthSection.removeFromLeft(40);
}

void VirtualGramoAudioProcessorEditor::gramophoneParametersSetup(const int TEXT_BOX_SIZE)
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

void VirtualGramoAudioProcessorEditor::additionalEffectsParamsSetup(const int TEXT_BOX_SIZE)
{
    // Sets up the compression slider.
    compressThreshParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
    compressThreshParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
    compressThreshParam.addListener(this); // Adds this editor as a listener for slider changes.
    addAndMakeVisible(compressThreshParam); // Makes the slider visible in the editor.

    // Links the compression slider to the "COMPRESS" parameter in the processor's parameter tree.
    compressThreshAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMPRESS", compressThreshParam);

    // Sets up the tone slider.
    toneParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    toneParam.addListener(this);
    addAndMakeVisible(toneParam);
    toneAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TONE", toneParam);

    // Sets up the vibrato slider.
    vibratoDepthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibratoDepthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoDepthParam.addListener(this);
    addAndMakeVisible(vibratoDepthParam);
    vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_DEPTH", vibratoDepthParam);

    // Sets up the vibrato rate slider.
    vibratoRateParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibratoRateParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoRateParam.addListener(this);
    addAndMakeVisible(vibratoRateParam);
    vibratoRateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_RATE", vibratoRateParam);
}
void VirtualGramoAudioProcessorEditor::wetDryParamSetup(const int TEXT_BOX_SIZE)
{
    // Sets up the mix slider.
    wetDryParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetDryParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    wetDryParam.addListener(this);
    addAndMakeVisible(wetDryParam);
    wetDryAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", wetDryParam);
}

void VirtualGramoAudioProcessorEditor::gramophoneHornParamsSetup(const int TEXT_BOX_SIZE)
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

// Callback for when a slider's value changes.
void VirtualGramoAudioProcessorEditor::sliderValueChanged(juce::Slider* /*slider*/)
{
    repaint(); // Repaints the editor to reflect the updated slider value.
}