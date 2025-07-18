/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "UI/InfoButtonUI.h"
#include "UI/WowAndFlutterUI.h"
#include "UI/VinylCrackleUI.h" // Add this include
#include <JuceHeader.h>

//==============================================================================
/**
*/

class StylusUI : public juce::Component,
    public juce::Slider::Listener
{
public:
    StylusUI(VirtualGramoAudioProcessor& p);
    ~StylusUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    float sliderToAplhaValue(juce::Slider& slider);

    VirtualGramoAudioProcessor& audioProcessor;

    static constexpr int TEXT_BOX_SIZE = 25;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StylusUI)
};

class VirtualGramoUIEditor : public juce::AudioProcessorEditor,
                                       public juce::Slider::Listener
{
public:
    explicit VirtualGramoUIEditor(VirtualGramoAudioProcessor&);
    ~VirtualGramoUIEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void drawComponents(juce::Graphics& g, float toneValue, float mixValue);

    void drawGramophoneContours(juce::Graphics& g);

    void drawGramophoneModel(juce::Path& funnel, juce::Path& base);

private:
    float sliderToAplhaValue(juce::Slider& slider);
    void SetupSections();
    void sliderValueChanged(juce::Slider* slider) override;
    void drawThreePointLine(juce::Graphics&, float x1, float y1, float x2, float y2, float x3, float y3);

    InfoButton infoButtonUI;
    StylusUI stylusUI;
    WowAndFlutterUI wowFlutterUI;
    VinylCrackleUI vinylCrackleUI; // Add VinylCrackleUI

    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;

    juce::Slider fToneControl;
    SliderAttatchmentPtr toneControlAttach;

    juce::Slider fMixControl;
    SliderAttatchmentPtr mixControlAttach;

    juce::Rectangle<int> top_section_;
    juce::Rectangle<int> toneSection;
    juce::Rectangle<int> mixSection;
    juce::Rectangle<int> toneTextSection;
    juce::Rectangle<int> mixTextSection;

    VirtualGramoAudioProcessor& audioProcessor;

    static constexpr int TEXT_BOX_SIZE = 25;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualGramoUIEditor)
};
