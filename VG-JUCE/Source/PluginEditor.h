/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once // Ensures the file is included only once during compilation.

#include "PluginProcessor.h" // Includes the header file for the plugin processor.
#include "InfoButton.h"      // Includes the header file for the InfoButton class.
#include <JuceHeader.h>      // Includes the JUCE framework header file.

#include <../Source/assimp/include/assimp/Importer.hpp> //C++ importer interface
#include <../Source/assimp/include/assimp/scene.h> // Output data structure
#include <../Source/assimp/include/assimp/postprocess.h> // Post processing flags


//==============================================================================
/**
 * The main editor class for the plugin.
 * Inherits from juce::AudioProcessorEditor and juce::Slider::Listener.
 * Handles the GUI and user interactions for the plugin.
 */
class GramophonyAudioProcessorEditor : public juce::AudioProcessorEditor,
	public juce::Slider::Listener, public juce::Open
{
public:
    explicit GramophonyAudioProcessorEditor(GramophonyAudioProcessor&); // Constructor that takes a reference to the audio processor.
    ~GramophonyAudioProcessorEditor() override; // Destructor for the editor.

    //==============================================================================
    void paint(juce::Graphics&) override; // Paints the editor's GUI components.
    void DrawThreePointLine(juce::Graphics&, float x1, float y1, float x2, float y2, float x3, float y3); // Custom method to draw a line connecting three points.
    void resized() override; // Handles resizing and layout of GUI components.

private:
    float sliderToAplhaValue(juce::Slider& slider); // Converts a slider's value to an alpha (transparency) value.
    void SetupSections(); // Sets up the layout and sections of the GUI.
    void sliderValueChanged(juce::Slider* slider) override; // Callback for when a slider's value changes.

    InfoButton info_button_; // Custom button for displaying information about the plugin.

    // Type alias for a unique pointer to a SliderAttachment.
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;

    // Sliders for controlling various parameters of the plugin.
    juce::Slider compress_slider_; // Slider for controlling the compression parameter.
    SliderAttatchmentPtr compress_slider_attachment_; // Attachment to link the compress slider to the parameter tree.

    juce::Slider tone_slider_; // Slider for controlling the tone parameter.
    SliderAttatchmentPtr tone_slider_attachment_; // Attachment to link the tone slider to the parameter tree.

    juce::Slider vibrato_slider_; // Slider for controlling the vibrato depth parameter.
    SliderAttatchmentPtr vibrato_slider_attachment_; // Attachment to link the vibrato slider to the parameter tree.

    juce::Slider vibratoRate; // Slider for controlling the vibrato rate parameter.
    SliderAttatchmentPtr vibrato_rate_slider_attachment_; // Attachment to link the vibrato rate slider to the parameter tree.

    juce::Slider mix_slider_; // Slider for controlling the wet/dry mix parameter.
    SliderAttatchmentPtr mix_slider_attachment_; // Attachment to link the mix slider to the parameter tree.

    // Rectangles defining sections of the GUI layout.
    juce::Rectangle<int> top_section_; // Rectangle for the top section of the GUI.
    juce::Rectangle<int> picture_section_; // Rectangle for the picture section of the GUI.
    juce::Rectangle<int> comp_section_; // Rectangle for the compression slider section.
    juce::Rectangle<int> tone_section_; // Rectangle for the tone slider section.
    juce::Rectangle<int> vibrato_section_; // Rectangle for the vibrato slider section.
    juce::Rectangle<int> vibrato_rate_section_; // Rectangle for the vibrato rate slider section.
    juce::Rectangle<int> mix_section_; // Rectangle for the mix slider section.
    juce::Rectangle<int> comp_text_section_; // Rectangle for the compression text label section.
    juce::Rectangle<int> tone_text_section_; // Rectangle for the tone text label section.
    juce::Rectangle<int> vibrato_text_section_; // Rectangle for the vibrato text label section.
    juce::Rectangle<int> mix_text_section_; // Rectangle for the mix text label section.

	Assimp::Importer importer; // Assimp importer for loading 3D models.

    // OpenGL-related members
    juce::OpenGLContext openGLContext;
    GLuint vertexBuffer = 0;
    GLuint shaderProgram = 0;

    GramophonyAudioProcessor& audioProcessor; // Reference to the audio processor instance.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramophonyAudioProcessorEditor)
        // Macro to prevent copying and enable leak detection for the class.
};
