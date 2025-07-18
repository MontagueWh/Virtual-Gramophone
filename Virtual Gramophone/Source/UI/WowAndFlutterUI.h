/*
  ==============================================================================

    WowAndFlutterUI.h
    Created: 10 Jul 2025 11:00:21am
    Author:  monty

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Data/WowAndFlutterData.h"
#include "../PluginProcessor.h"

class WowAndFlutterUI : public juce::Component,
                        public juce::Slider::Listener
{
public:
    WowAndFlutterUI(VirtualGramoAudioProcessor& p) : audioProcessor(p)
    {
        fWowControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fWowControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fWowControl.addListener(this);
        addAndMakeVisible(fWowControl);

        wowControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "WOW", fWowControl);

        fFlutterControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fFlutterControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fFlutterControl.addListener(this);
        addAndMakeVisible(fFlutterControl);

        flutterControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "FLUTTER", fFlutterControl);
    }

    ~WowAndFlutterUI() override
    {
    }

    void paint(juce::Graphics& g) override
    {
        // Empty implementation - drawing handled by parent component
    }

    void resized() override
    {
        setupSections();
        fWowControl.setBounds(wowSection);
        fFlutterControl.setBounds(flutterSection);
    }

    void setupSections()
    {
        juce::Rectangle<int> r = getLocalBounds();
        
        // Reserve space for gramophone visualization
        picture_section_ = r.removeFromLeft(r.getWidth() - 250);
        
        // Right side for controls
        constexpr int controlHeight = 80;
        constexpr int iTextSectionWidth = 80;
        constexpr int labelVerticalOffset = 40;
        
        // Wow control
        wowSection = r.removeFromTop(controlHeight);
        wowTextSection = wowSection.removeFromLeft(iTextSectionWidth);
        wowTextSection = wowTextSection.withY(wowTextSection.getY() + labelVerticalOffset)
                                      .withHeight(wowTextSection.getHeight() - labelVerticalOffset);
        
        // Flutter control
        flutterSection = r.removeFromTop(controlHeight);
        flutterTextSection = flutterSection.removeFromLeft(iTextSectionWidth);
        flutterTextSection = flutterTextSection.withY(flutterTextSection.getY() + labelVerticalOffset)
                                              .withHeight(flutterTextSection.getHeight() - labelVerticalOffset);
    }

    void drawWowFlutterLabels(juce::Graphics& g)
    {
        // Draw labels
        setupSections();
        g.setFont(16.0f);
        
        // Draw labels slightly lower to align with controls
        g.drawFittedText("WOW", wowTextSection, juce::Justification::centredLeft, 1);
        g.drawFittedText("FLUTTER", flutterTextSection, juce::Justification::centredLeft, 1);
    }

    void sliderValueChanged(juce::Slider* /*slider*/) override
    {
        // Repaint the component when sliders change
        repaint();
    }

    float sliderToAplhaValue(juce::Slider& slider)
    {
        double range = (slider.getMaximum() - slider.getMinimum());
        return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
    }

    juce::Slider fWowControl;
    juce::Slider fFlutterControl;

private:
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    SliderAttachmentPtr wowControlAttach;
    SliderAttachmentPtr flutterControlAttach;

    juce::Rectangle<int> picture_section_;
    juce::Rectangle<int> wowSection;
    juce::Rectangle<int> flutterSection;
    juce::Rectangle<int> wowTextSection;
    juce::Rectangle<int> flutterTextSection;

    const int TEXT_BOX_SIZE = 25;

    VirtualGramoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WowAndFlutterUI)
};

