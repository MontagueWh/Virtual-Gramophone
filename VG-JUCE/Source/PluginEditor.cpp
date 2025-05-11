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

    // Sets up the mix slider.
    wetDryParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetDryParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    wetDryParam.addListener(this);
    addAndMakeVisible(wetDryParam);
    wetDryAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", wetDryParam);

    // Adds the info button to the editor.
    info_button_.addToEditor(this);

    setSize(500, 300); // Sets the initial size of the editor window.
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

	std::string GramoSuite = "../Source/GramoSuite.fbx"; // Path to the FBX file
	gramoModelLoader.importModel(GramoSuite); // Import the model from the specified path

    g.setColour(juce::Colours::darkgrey);
    gramoModelLoader.renderModel(g, getLocalBounds().toFloat());


    // Draw contours
    g.setColour(juce::Colour(0xff123456));
    DrawThreePointLine(g, 73.0f, 179.0f, 62.0f, 144.0f, 8.0f, 102.0f);
    DrawThreePointLine(g, 85.0f, 189.0f, 83.0f, 133.0f, 43.0f, 48.0f);
    DrawThreePointLine(g, 92.0f, 193.0f, 105.0f, 129.0f, 113.0f, 38.0f);
    DrawThreePointLine(g, 101.0f, 201.0f, 144.0f, 126.0f, 194.0f, 55.0f);
    DrawThreePointLine(g, 108.0f, 203.0f, 176.0f, 145.0f, 258.0f, 109.0f);
    DrawThreePointLine(g, 122.0f, 209.0f, 188.0f, 179.0f, 279.0f, 171.0f);
    DrawThreePointLine(g, 136.0f, 211.0f, 174.0f, 202.0f, 252.0f, 225.0f);
    DrawThreePointLine(g, 108.0f, 203.0f, 144.0f, 215.0f, 174.0f, 245.0f);
    DrawThreePointLine(g, 108.0f, 203.0f, 73.0f, 179.0f, 25.0f, 166.0f);
    g.drawLine(juce::Line<float>(108.0f, 203.0f, 92.0f, 229.0f), LINE_THICKNESS);

    SetupSections();
    g.setFont(18.0f);
    g.drawFittedText("COMP", compressTextSection, juce::Justification::left, 1);
    g.drawFittedText("TONE", toneTextSection, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibratoTextSection, juce::Justification::left, 1);
    g.drawFittedText("DRY", wetDryTextSection, juce::Justification::left, 1);
}

// Converts a slider's value to an alpha (transparency) value.
float VirtualGramoAudioProcessorEditor::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

// Draws a line connecting three points.
void VirtualGramoAudioProcessorEditor::DrawThreePointLine(juce::Graphics& g,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3)
{
    g.drawLine(juce::Line<float>(x1, y1, x2, y2), LINE_THICKNESS);
    g.drawLine(juce::Line<float>(x2, y2, x3, y3), LINE_THICKNESS);
}

// Handles resizing and layout of GUI components.
void VirtualGramoAudioProcessorEditor::resized()
{
    info_button_.button.setBounds(getWidth() - 35, 10, 20, 20); // Positions the info button.
    info_button_.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100); // Positions the info text.
    SetupSections(); // Updates the layout sections.
    compressThreshParam.setBounds(compressSection); // Positions the compression slider.
    toneParam.setBounds(toneSection); // Positions the tone slider.
    vibratoDepthParam.setBounds(vibratoDepthSection); // Positions the vibrato slider.
    vibratoRateParam.setBounds(vibratoRateSection); // Positions the vibrato rate slider.
    wetDryParam.setBounds(wetDrySection); // Positions the mix slider.
}

// Sets up the layout sections for the GUI.
void VirtualGramoAudioProcessorEditor::SetupSections()
{
    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.
    topSection = r.removeFromTop(50); // Allocates the top section.
    pictureSection = r.removeFromLeft(310); // Allocates the picture section.

    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.
    int section_height = interfaceSection.getHeight() / 4; // Divides the interface into four sections.
    constexpr int textSectionWidth = 40; // Width for the text labels.

    // Allocates sections for sliders and their labels.
    compressSection = interfaceSection.removeFromTop(section_height);
    compressTextSection = compressSection.removeFromLeft(textSectionWidth);

	toneSection = interfaceSection.removeFromTop(section_height);
	toneTextSection = toneSection.removeFromLeft(textSectionWidth);

	vibratoDepthSection = interfaceSection.removeFromTop(section_height);
	vibratoTextSection = vibratoDepthSection.removeFromLeft(textSectionWidth);
	vibratoRateSection = interfaceSection.removeFromTop(section_height);

    wetDrySection = interfaceSection;
    wetDrySection = interfaceSection.removeFromTop(textSectionWidth);
}

// Callback for when a slider's value changes.
void VirtualGramoAudioProcessorEditor::sliderValueChanged(juce::Slider* /*slider*/)
{
    repaint(); // Repaints the editor to reflect the updated slider value.
}