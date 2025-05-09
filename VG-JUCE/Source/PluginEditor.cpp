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
GramophonyAudioProcessorEditor::GramophonyAudioProcessorEditor(GramophonyAudioProcessor& p)
    : AudioProcessorEditor(&p), // Initialises the base class with the processor reference.
    audioProcessor(p), // Stores a reference to the audio processor.
    info_button_(juce::Colours::darkgrey), // Initialises the info button with a dark gray colour.
	openGLContext_(*this) // Sets up the OpenGL context for rendering.
{
    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.

    // Sets up the compression slider.
    compress_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
    compress_slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
    compress_slider_.addListener(this); // Adds this editor as a listener for slider changes.
    addAndMakeVisible(compress_slider_); // Makes the slider visible in the editor.

    // Links the compression slider to the "COMPRESS" parameter in the processor's parameter tree.
    compress_slider_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMPRESS", compress_slider_);

    // Sets up the tone slider.
    tone_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    tone_slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    tone_slider_.addListener(this);
    addAndMakeVisible(tone_slider_);
    tone_slider_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TONE", tone_slider_);

    // Sets up the vibrato slider.
    vibrato_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibrato_slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibrato_slider_.addListener(this);
    addAndMakeVisible(vibrato_slider_);
    vibrato_slider_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO", vibrato_slider_);

    // Sets up the vibrato rate slider.
    vibrato_rate_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibrato_rate_slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibrato_rate_slider_.addListener(this);
    addAndMakeVisible(vibrato_rate_slider_);
    vibrato_rate_slider_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_RATE", vibrato_rate_slider_);

    // Sets up the mix slider.
    mix_slider_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mix_slider_.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    mix_slider_.addListener(this);
    addAndMakeVisible(mix_slider_);
    mix_slider_attachment_ = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mix_slider_);

    // Adds the info button to the editor.
    info_button_.addToEditor(this);

    // Attach and initialise OpenGL
    openGLContext.setRenderer(this);
    openGLContext.attachTo(*this);

    setSize(500, 300); // Sets the initial size of the editor window.
}

// Destructor for the plugin editor.
GramophonyAudioProcessorEditor::~GramophonyAudioProcessorEditor()
{
    openGLContext.detach();
    if (vertexBuffer != 0)
        openGLContext.extensions.glDeleteBuffers(1, &vertexBuffer);
    if (shaderProgram != 0)
    {
        GLuint shaders[2];
        openGLContext.extensions.glGetAttachedShaders(shaderProgram, shaders);
        for (auto shader : shaders)
            openGLContext.extensions.glDeleteShader(shader);
        openGLContext.extensions.glDeleteProgram(shaderProgram);
    }
}

//==============================================================================
// Paints the editor's GUI components.
void GramophonyAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::beige); // Fills the background with a beige color.

    g.setColour(juce::Colour(0xff123456)); // Sets the color for the title text.
    g.setFont(40.0f); // Sets the font size for the title text.
    g.drawFittedText("GRAMOPHONY", getLocalBounds(), juce::Justification::centredTop, 1); // Draws the plugin title.

    assimp::Importer::ReadFile

    objParser.load(gramoSuite.getFullPathName()); // Use getFullPathName()

    SetupSections(); // Sets up the layout sections for the GUI.

    // Draws labels for the sliders.
    g.setFont(18.0f);
    g.drawFittedText("COMP", comp_text_section_, juce::Justification::left, 1);
    g.drawFittedText("TONE", tone_text_section_, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibrato_text_section_, juce::Justification::left, 1);
    g.drawFittedText("DRY", mix_text_section_, juce::Justification::left, 1);
}

// Converts a slider's value to an alpha (transparency) value.
float GramophonyAudioProcessorEditor::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

// Draws a line connecting three points.
void GramophonyAudioProcessorEditor::DrawThreePointLine(juce::Graphics& g,
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
void GramophonyAudioProcessorEditor::resized()
{
    info_button_.button.setBounds(getWidth() - 35, 10, 20, 20); // Positions the info button.
    info_button_.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100); // Positions the info text.
    SetupSections(); // Updates the layout sections.
    compress_slider_.setBounds(comp_section_); // Positions the compression slider.
    tone_slider_.setBounds(tone_section_); // Positions the tone slider.
    vibrato_slider_.setBounds(vibrato_section_); // Positions the vibrato slider.
    vibrato_rate_slider_.setBounds(vibrato_rate_section_); // Positions the vibrato rate slider.
    mix_slider_.setBounds(mix_section_); // Positions the mix slider.
}

// Sets up the layout sections for the GUI.
void GramophonyAudioProcessorEditor::SetupSections()
{
    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.
    top_section_ = r.removeFromTop(50); // Allocates the top section.
    picture_section_ = r.removeFromLeft(310); // Allocates the picture section.

    juce::Rectangle<int> interface_section = r; // Remaining area for the interface.
    int section_height = interface_section.getHeight() / 4; // Divides the interface into four sections.
    constexpr int text_section_width = 40; // Width for the text labels.

    // Allocates sections for sliders and their labels.
    comp_section_ = interface_section.removeFromTop(section_height);
    comp_text_section_ = comp_section_.removeFromLeft(text_section_width);

    tone_section_ = interface_section.removeFromTop(section_height);
    tone_text_section_ = tone_section_.removeFromLeft(text_section_width);

    vibrato_section_ = interface_section.removeFromTop(section_height);
    vibrato_text_section_ = vibrato_section_.removeFromLeft(text_section_width);
    vibrato_rate_section_ = vibrato_section_.removeFromRight(vibrato_section_.getWidth() / 2);

    mix_section_ = interface_section;
    mix_text_section_ = mix_section_.removeFromLeft(text_section_width);
}

// Callback for when a slider's value changes.
void GramophonyAudioProcessorEditor::sliderValueChanged(juce::Slider* /*slider*/)
{
    repaint(); // Repaints the editor to reflect the updated slider value.
}
