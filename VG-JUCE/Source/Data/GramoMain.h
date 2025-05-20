/*
  ==============================================================================

    GramoMain.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StylusEmulation.h"
#include "HornEmulation.h"
#include "SoundboxEmulation.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
/*
*/
class GramoMain : public juce::Component, juce::AudioSource, juce::Slider::Listener
{
public:
    GramoMain();
    void initaliseGramoVoice();
    void setupStylusParams(const int TEXT_BOX_SIZE);
    void setupSoundboxParams(const int TEXT_BOX_SIZE);
    void setupHornParams(const int TEXT_BOX_SIZE);
    ~GramoMain() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

	void paint(juce::Graphics& g) override; // Paints the editor's GUI components.
    void drawUiText(juce::Graphics& g);
    void resized() override; // Handles resizing and layout of GUI components.

    juce::Rectangle<int> pictureSection; // Rectangle for the picture section of the GUI.

    // Type alias for a unique pointer to a SliderAttachment.
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;

    // Horn parameters
    juce::Slider hornStiffnessParam; // Slider for controlling the stiffness of the gramophone's brass horn.
    SliderAttatchmentPtr hornStiffnessAttach; // Attachment to link the horn stiffness slider to the parameter tree.

    juce::Slider hornDiameterParam; // Slider for controlling the diameter of the gramophone's brass horn.
    SliderAttatchmentPtr hornDiameterAttach; // Attachment to link the horn diameter slider to the parameter tree.

    juce::Slider hornLengthParam; // Slider for controlling the length of the gramophone's brass horn.
    SliderAttatchmentPtr hornLengthAttach; // Attachment to link the horn length slider to the parameter tree.

    // Soundbox parameters
    juce::Slider soundboxPressureParam; // Slider for controlling the soundbox pressure.
    SliderAttatchmentPtr soundboxPressureAttach; // Attachment to link the soundbox pressure slider to the parameter tree.

    juce::Slider noiseGainParam; // Slider for controlling the noise gain in the soundbox.
    SliderAttatchmentPtr noiseGainAttach; // Attachment to link the noise gain slider to the parameter tree.

    juce::Slider vibratoDepthParam; // Slider for controlling the depth of the vibrato effect.
    SliderAttatchmentPtr vibratoDepthAttach; // Attachment to link the vibrato depth slider to the parameter tree.

    juce::Slider vibratoRateParam; // Slider for controlling the vibrato frequency.
    SliderAttatchmentPtr vibratoRateAttach; // Attachment to link the vibrato frequency slider to the parameter tree.

    juce::Slider vibratoGainParam; // Slider for controlling the vibrato gain.
    SliderAttatchmentPtr vibratoGainAttach; // Attachment to link the vibrato gain slider to the parameter tree.

    juce::Slider vibratoMixParam; // Slider for controlling the vibrato mix.
    SliderAttatchmentPtr vibratoMixAttach; // Attachment to link the vibrato mix slider to the parameter tree.

    // Stylus parameters
    juce::Slider stylusPressureParam; // Slider for controlling the pressure of the stylus on the record.
    SliderAttatchmentPtr stylusPressureAttach; // Attachment to link the stylus pressure slider to the parameter tree.

    juce::Slider vinylFilterFreqParam; // Slider for controlling the vinyl filter frequency.
    SliderAttatchmentPtr vinylFilterFreqAttach; // Attachment to link the vinyl filter frequency slider to the parameter tree.

    // Global parameters
    juce::Slider pitchShiftParam; // Slider for controlling the pitch shift.
    SliderAttatchmentPtr pitchShiftAttach; // Attachment to link the pitch shift slider to the parameter tree.

private:

    void sliderValueChanged(juce::Slider* slider) override; // Callback for when a slider's value changes.
	void setupSections(); // Sets up the layout and sections of the GUI.

    void stylusUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);
    void soundboxUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);
    void hornUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);

    
    // Rectangles defining sections of the GUI layout.

	// Rectangles for the interface horn sections.
	juce::Rectangle<int> hornStiffnessSection; // Rectangle for the horn stiffness section of the GUI.
	juce::Rectangle<int> hornStiffnessTextSection; // Rectangle for the text label of the horn stiffness section.

	juce::Rectangle<int> hornDiameterSection; // Rectangle for the horn diameter section of the GUI.
	juce::Rectangle<int> hornDiameterTextSection; // Rectangle for the text label of the horn diameter section.

	juce::Rectangle<int> hornLengthSection; // Rectangle for the horn length section of the GUI.
	juce::Rectangle<int> hornLengthTextSection; // Rectangle for the text label of the horn length section.

	// Rectangles for the interface soundbox sections.
	juce::Rectangle<int> soundboxPressureSection; // Rectangle for the soundbox pressure section of the GUI.
	juce::Rectangle<int> soundboxPressureTextSection; // Rectangle for the text label of the soundbox pressure section.

	juce::Rectangle<int> noiseGainSection; // Rectangle for the noise gain section of the GUI.
	juce::Rectangle<int> noiseGainTextSection; // Rectangle for the text label of the noise gain section.

	juce::Rectangle<int> vibratoDepthSection; // Rectangle for the vibrato depth section of the GUI.
	juce::Rectangle<int> vibratoDepthTextSection; // Rectangle for the text label of the vibrato depth section.

	juce::Rectangle<int> vibratoRateSection; // Rectangle for the vibrato frequency section of the GUI.
	juce::Rectangle<int> vibratoRateTextSection; // Rectangle for the text label of the vibrato frequency section.

	juce::Rectangle<int> vibratoGainSection; // Rectangle for the vibrato gain section of the GUI.
	juce::Rectangle<int> vibratoGainTextSection; // Rectangle for the text label of the vibrato gain section.

	juce::Rectangle<int> vibratoMixSection; // Rectangle for the vibrato mix section of the GUI.
	juce::Rectangle<int> vibratoMixTextSection; // Rectangle for the text label of the vibrato mix section.

	// Rectangles for the interface stylus sections.
	juce::Rectangle<int> stylusPressureSection; // Rectangle for the stylus pressure section of the GUI.
	juce::Rectangle<int> stylusPressureTextSection; // Rectangle for the text label of the stylus pressure section.

	juce::Rectangle<int> vinylFilterFreqSection; // Rectangle for the vinyl filter frequency section of the GUI.
	juce::Rectangle<int> vinylFilterFreqTextSection; // Rectangle for the text label of the vinyl filter frequency section.

	juce::Rectangle<int> pitchShiftSection; // Rectangle for the pitch shift section of the GUI.
	juce::Rectangle<int> pitchShiftTextSection; // Rectangle for the text label of the pitch shift section.

    StylusEmulation gramoStylus;
	HornEmulation gramoHorn;
    SoundboxEmulation gramoSoundbox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoMain)
};