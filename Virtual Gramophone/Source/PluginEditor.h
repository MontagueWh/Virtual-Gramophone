/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "UI/InfoButtonUI.h"
#include "UI/WowAndFlutterUI.h" // Make sure this include is present
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
    void setupSections();
    void drawStylusLabels(juce::Graphics& g);
    void sliderValueChanged(juce::Slider* slider) override;

    juce::Slider fCompressControl;
    juce::Slider fVibratoDepthControl;
    juce::Slider fVibratoRateControl;

private:
    float sliderToAplhaValue(juce::Slider& slider);

    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    SliderAttachmentPtr compressControlAttach;
    SliderAttachmentPtr vibratoDepthControlAttach;

    SliderAttachmentPtr vibratoRateControlAttach;

    juce::Rectangle<int> picture_section_;
    juce::Rectangle<int> compressSection;
    juce::Rectangle<int> vibratoDepthSection;
    juce::Rectangle<int> vibratoRateSection;
    juce::Rectangle<int> compressTextSection;
    juce::Rectangle<int> vibratoDepthTextSection;
    juce::Rectangle<int> vibratoRateTextSection;
    juce::Rectangle<int> vibratoTextSection;

    VirtualGramoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StylusUI)
};

// WowAndFlutterUI class removed as it's now in WowAndFlutterUI.h

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
    WowAndFlutterUI wowFlutterUI; // Keep this member variable

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualGramoUIEditor)
};
