/*
  ==============================================================================

    GramoVoice.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StylusEmulation.h"
#include "HornEmulation.h"
#include "SoundboxEmulation.h"

//==============================================================================
/*
*/
class GramoVoice : public juce::Component, juce::AudioSource, juce::Slider::Listener
{
public:
    GramoVoice();
    ~GramoVoice() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

	void paint(juce::Graphics& g) override; // Paints the editor's GUI components.
    void resized() override; // Handles resizing and layout of GUI components.

    void gramophoneParametersSetup(const int TEXT_BOX_SIZE); // Sets up the parameters for the gramophone.

private:

    void sliderValueChanged(juce::Slider* slider) override; // Callback for when a slider's value changes.
	void setupSections(); // Sets up the layout and sections of the GUI.

    // Type alias for a unique pointer to a SliderAttachment.
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;

    SliderAttatchmentPtr hornStiffnessAttach; // Attachment to link the horn stiffness slider to the parameter tree.
    SliderAttatchmentPtr hornDiameterAttach; // Attachment to link the horn diameter slider to the parameter tree.
    SliderAttatchmentPtr hornLengthAttach; // Attachment to link the horn length slider to the parameter tree.

    juce::Rectangle<int> hornStiffnessSection; // Rectangle for the horn stiffness text label section.
    juce::Rectangle<int> hornDiameterSection; // Rectangle for the horn diameter text label section.
    juce::Rectangle<int> hornLengthSection; // Rectangle for the horn length text label section.
    juce::Rectangle<int> hornFreqSection; // Rectangle for the horn frequency text label section.

    juce::Rectangle<int> hornStiffnessTextSection; // Rectangle for the horn stiffness text label section.
    juce::Rectangle<int> hornDiameterTextSection; // Rectangle for the horn diameter text label section.
    juce::Rectangle<int> hornLengthTextSection; // Rectangle for the horn length text label section.

    juce::Slider hornStiffnessParam; // Slider for changing the stiffness of the gramophone's brass horn
    juce::Slider hornDiameterParam; // Slider for changing the diameter of the gramophone's brass horn
    juce::Slider hornLengthParam; // Slider for changing the length of the gramophone's brass horn
    juce::Slider frequencyParam;
    juce::Slider pressureParam;
    juce::Slider inputGainParam;
    juce::Slider mixParam;
    juce::Slider vibratoFreqParam;
    juce::Slider vibratoGainParam;
    juce::Slider pitchShiftParam;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pressureAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vibratoFreqAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vibratoGainAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchShiftAttach;

    StylusEmulation gramoStylus;
	HornEmulation gramoHorn;
    SoundboxEmulation gramoSoundbox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoVoice)
};