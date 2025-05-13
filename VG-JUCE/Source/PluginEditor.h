/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once // Ensures the file is included only once during compilation.

#include "PluginProcessor.h" // Includes the header file for the plugin processor.
#include "UI/InfoButton.h"      // Includes the header file for the InfoButton class.
#include <JuceHeader.h>      // Includes the JUCE framework header file.
//#include <../Source/UI/GramoModelLoader.h>


//==============================================================================
/**
 * The main editor class for the plugin.
 * Inherits from juce::AudioProcessorEditor and juce::Slider::Listener.
 * Handles the GUI and user interactions for the plugin.
 */
class VirtualGramoAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    explicit VirtualGramoAudioProcessorEditor(VirtualGramoAudioProcessor&); // Constructor that takes a reference to the audio processor.
    ~VirtualGramoAudioProcessorEditor() override; // Destructor for the editor.

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
    juce::Slider compressThreshParam; // Slider for controlling the compression parameter.
    SliderAttatchmentPtr compressThreshAttach; // Attachment to link the compress slider to the parameter tree.

    juce::Slider toneParam; // Slider for controlling the tone parameter.
    SliderAttatchmentPtr toneAttach; // Attachment to link the tone slider to the parameter tree.

    juce::Slider vibratoDepthParam; // Slider for controlling the vibrato depth parameter.
    SliderAttatchmentPtr vibratoDepthAttach; // Attachment to link the vibrato slider to the parameter tree.

    juce::Slider vibratoRateParam; // Slider for controlling the vibrato rate parameter.
    SliderAttatchmentPtr vibratoRateAttach; // Attachment to link the vibrato rate slider to the parameter tree.

    juce::Slider wetDryParam; // Slider for controlling the wet/dry mix parameter.
    SliderAttatchmentPtr wetDryAttach; // Attachment to link the mix slider to the parameter tree.

    // Rectangles defining sections of the GUI layout.
    juce::Rectangle<int> topSection; // Rectangle for the top section of the GUI.
    juce::Rectangle<int> pictureSection; // Rectangle for the picture section of the GUI.
    juce::Rectangle<int> compressSection; // Rectangle for the compression slider section.
    juce::Rectangle<int> toneSection; // Rectangle for the tone slider section.
    juce::Rectangle<int> vibratoDepthSection; // Rectangle for the vibrato slider section.
    juce::Rectangle<int> vibratoRateSection; // Rectangle for the vibrato rate slider section.
    juce::Rectangle<int> wetDrySection; // Rectangle for the mix slider section.
    juce::Rectangle<int> compressTextSection; // Rectangle for the compression text label section.
    juce::Rectangle<int> toneTextSection; // Rectangle for the tone text label section.
    juce::Rectangle<int> vibratoTextSection; // Rectangle for the vibrato text label section.
    juce::Rectangle<int> wetDryTextSection; // Rectangle for the mix text label section.

	//GramoModelLoader gramoModelLoader; // Instance of the GramoModelLoader class for loading 3D models.

    VirtualGramoAudioProcessor& audioProcessor; // Reference to the audio processor instance.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualGramoAudioProcessorEditor)
        // Macro to prevent copying and enable leak detection for the class.
};
