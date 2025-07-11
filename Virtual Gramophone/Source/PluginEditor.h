/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "UI/InfoButton.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/

class StylusUI : public juce::Component,
    public juce::Slider::Listener
{
public:
    StylusUI(GramophonyAudioProcessor& p);
    ~StylusUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void setupSections();
    void drawGramophone(juce::Graphics& g, float toneValue, float mixValue);
    void sliderValueChanged(juce::Slider* slider) override;

private:
    void drawThreePointLine(juce::Graphics&, float x1, float y1, float x2, float y2, float x3, float y3);
    float sliderToAplhaValue(juce::Slider& slider);

    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    juce::Slider fCompressControl;
    SliderAttachmentPtr compress_slider_attachment_;

    juce::Slider fVibratoDepthControl;
    SliderAttachmentPtr vibrato_slider_attachment_;

    juce::Slider vibrato_rate_slider_;
    SliderAttachmentPtr vibrato_rate_slider_attachment_;

    juce::Rectangle<int> picture_section_;
    juce::Rectangle<int> compressSection;
    juce::Rectangle<int> vibratoDepthSection;
    juce::Rectangle<int> vibratoRateSection;
    juce::Rectangle<int> compressTextSection;
    juce::Rectangle<int> vibrato_text_section_;

    GramophonyAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StylusUI)
};

class GramophonyAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       public juce::Slider::Listener
{
public:
    explicit GramophonyAudioProcessorEditor(GramophonyAudioProcessor&);
    ~GramophonyAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    float sliderToAplhaValue(juce::Slider& slider);
    void SetupSections();
    void sliderValueChanged(juce::Slider* slider) override;

    InfoButton info_button_;
    StylusUI stylus_ui_;

    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;

    juce::Slider fToneControl;
    SliderAttatchmentPtr tone_slider_attachment_;

    juce::Slider fMixControl;
    SliderAttatchmentPtr mix_slider_attachment_;

    juce::Rectangle<int> top_section_;
    juce::Rectangle<int> toneSection;
    juce::Rectangle<int> mixSection;
    juce::Rectangle<int> toneTextSection;
    juce::Rectangle<int> mixTextSection;

    GramophonyAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GramophonyAudioProcessorEditor)
};
