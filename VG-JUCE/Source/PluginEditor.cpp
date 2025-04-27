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
    info_button_(juce::Colours::darkgrey) // Initialises the info button with a dark gray colour.
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

    setSize(500, 300); // Sets the initial size of the editor window.
}

// Destructor for the plugin editor.
GramophonyAudioProcessorEditor::~GramophonyAudioProcessorEditor()
{
}

//==============================================================================
// Paints the editor's GUI components.
void GramophonyAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::beige); // Fills the background with a beige color.

    g.setColour(juce::Colour(0xff123456)); // Sets the color for the title text.
    g.setFont(40.0f); // Sets the font size for the title text.
    g.drawFittedText("GRAMOPHONY", getLocalBounds(), juce::Justification::centredTop, 1); // Draws the plugin title.

	ObjParser.load("gramophone.obj"); // Loads the 3D model of the gramophone.

    /*// Creates the shape of a gramophone funnel.
    juce::Path funnel;
    funnel.startNewSubPath(8.0f, 102.0f);
    funnel.lineTo(43.0f, 48.0f);
    funnel.lineTo(113.0f, 38.0f);
    funnel.lineTo(194.0f, 55.0);
    funnel.lineTo(258.0f, 109.0f);
    funnel.lineTo(279.0f, 171.0f);
    funnel.lineTo(252.0f, 225.0f);
    funnel.lineTo(174.0f, 245.0f);
    funnel.lineTo(92.0f, 229.0f);
    funnel.lineTo(25.0f, 166.0f);
    funnel.closeSubPath();

    // Creates the shape of the gramophone base.
    juce::Path base;
    base.startNewSubPath(74.0f, 210.0f);
    base.lineTo(54.0f, 254.0f);
    base.lineTo(53.0f, 275.0f);
    base.lineTo(0.0F, 300.0f);
    base.lineTo(32.0F, 300.0f);
    base.lineTo(73.0f, 285.0f);
    base.lineTo(79.0f, 260.0f);
    base.lineTo(104.0F, 230.0f);
    base.closeSubPath();

    g.setColour(juce::Colour(0xff123456)); // Sets the color for the base.
    g.fillPath(base); // Fills the base shape.

    g.setColour(juce::Colours::beige); // Sets the color to beige to hide parts of the base.
    g.fillPath(funnel); // Fills the funnel shape with beige.

    // Fills the funnel with colors based on slider values.
    g.setColour(juce::Colours::orange.withAlpha(0.2f + sliderToAplhaValue(tone_slider_) / 2.0f));
    g.fillPath(funnel);
    g.setColour(juce::Colours::yellow.withAlpha(sliderToAplhaValue(compress_slider_) / 2.0f));
    g.fillPath(funnel);
    g.setColour(juce::Colours::blueviolet.withAlpha(sliderToAplhaValue(vibrato_slider_) / 4.0f));
    g.fillPath(funnel);
    g.setColour(juce::Colours::rebeccapurple.withAlpha(sliderToAplhaValue(vibrato_rate_slider_) / 3.0f));
    g.fillPath(funnel);
    g.setColour(juce::Colours::orangered.withAlpha(sliderToAplhaValue(mix_slider_) / 3.0f));
    g.fillPath(funnel);

    // Draws contours for the gramophone funnel.
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
    g.drawLine(juce::Line<float>(108.0f, 203.0f, 92.0f, 229.0f), LINE_THICKNESS);*/

    SetupSections(); // Sets up the layout sections for the GUI.

    // Draws labels for the sliders.
    g.setFont(18.0f);
    g.drawFittedText("COMP", comp_text_section_, juce::Justification::left, 1);
    g.drawFittedText("TONE", tone_text_section_, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibrato_text_section_, juce::Justification::left, 1);
    g.drawFittedText("DRY", mix_text_section_, juce::Justification::left, 1);
}

void GramophonyAudioProcessorEditor::load3DAssets()
{
    // Get the plugin's content directory
    juce::File contentDir =
        juce::File::getSpecialLocation(
            juce::File::SpecialLocationType::userApplicationDataDirectory)
        .getChildFile("YourCompanyName") // Replace "YourCompanyName"
        .getChildFile("YourPluginName")    // Replace "YourPluginName"
        .getChildFile("Content");

    // Load Gramophone Model
    juce::File gramophoneObjFile =
        contentDir.getChildFile("models").getChildFile("gramophone").getChildFile(
            "VirtualGramophoneSuite.obj");
    if (gramophoneObjFile.exists())
    {
        if (gramophoneModel.load(gramophoneObjFile).failed())
        {
            juce::Logger::writeToLog("Error loading gramophone OBJ file");
            return false;
        }
        else
        {
            juce::Logger::writeToLog("Gramophone OBJ file loaded successfully");
        }
    }
    else
    {
        juce::Logger::writeToLog(
            "Gramophone OBJ file not found: " + gramophoneObjFile.getFullPathName());
        return false;
    }

    // Load Coffee Table Model
    juce::File coffeeTableObjFile =
        contentDir.getChildFile("models").getChildFile("furniture").getChildFile(
            "CoffeeTable.obj"); // Adjust path if needed
    if (coffeeTableObjFile.exists())
    {
        if (coffeeTableModel.load(coffeeTableObjFile).failed())
        {
            juce::Logger::writeToLog("Error loading coffee table OBJ file");
            return false;
        }
        else
        {
            juce::Logger::writeToLog("Coffee table OBJ file loaded successfully");
        }
    }
    else
    {
        juce::Logger::writeToLog(
            "Coffee table OBJ file not found: " +
            coffeeTableObjFile.getFullPathName());
        return false;
    }

    // Load Coffee Table Textures
    juce::File normalMapFile =
        contentDir.getChildFile("textures").getChildFile(
            "CoffeeTableWoodBrown_T_CoffeeTableWoodBrown_Normal.png");
    if (normalMapFile.exists())
    {
        coffeeTableNormalMap = juce::ImageCache::getFromFile(normalMapFile);
        if (!coffeeTableNormalMap.isValid())
        {
            juce::Logger::writeToLog("Error loading coffee table normal map");
            return false;
        }
        else
        {
            juce::Logger::writeToLog("Coffee table normal map loaded");
        }
    }
    else
    {
        juce::Logger::writeToLog(
            "Coffee table normal map not found: " + normalMapFile.getFullPathName());
        return false;
    }

    juce::File albedoMapFile =
        contentDir.getChildFile("textures").getChildFile(
            "CoffeeTableWoodBrown_T_CoffeeTableWoodBrown_AlbedoTransparency.png");
    if (albedoMapFile.exists())
    {
        coffeeTableAlbedoMap = juce::ImageCache::getFromFile(albedoMapFile);
        if (!coffeeTableAlbedoMap.isValid())
        {
            juce::Logger::writeToLog("Error loading coffee table albedo map");
            return false;
        }
        else
        {
            juce::Logger::writeToLog("Coffee table albedo map loaded");
        }
    }
    else
    {
        juce::Logger::writeToLog(
            "Coffee table albedo map not found: " + albedoMapFile.getFullPathName());
        return false;
    }

    return true;
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
