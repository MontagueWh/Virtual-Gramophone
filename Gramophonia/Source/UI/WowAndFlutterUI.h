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

        // Flutter control now affects both rate and depth
        fFlutterControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fFlutterControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fFlutterControl.setRange(0.0f, 1.0f);  // Normalized range 0-1
        fFlutterControl.setValue(0.0f);        // Start at 0
        fFlutterControl.addListener(this);
        addAndMakeVisible(fFlutterControl);

        // We'll manually update vibrato rate and depth when flutter control changes
        // Remove the standard attachment since we're controlling multiple parameters
        flutterControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "FLUTTER", fFlutterControl);
    }

    ~WowAndFlutterUI() override
    {
    }

    void paint(juce::Graphics& g)
    {
        // Debug background color (can be removed later)
        g.fillAll(juce::Colours::lightgreen.withAlpha(0.1f));

        // Draw labels directly in the component's paint method
        drawWowFlutterLabels(g);
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
        
        // Calculate a scale factor based on the actual height of the component
        float heightScaleFactor = juce::jmin(1.0f, (float)getHeight() / 275.0f);
        
        // Adjust control heights based on available space
        int controlHeight = juce::jmax(40, (int)(80 * heightScaleFactor));
        int labelVerticalOffset = juce::jmax(20, (int)(40 * heightScaleFactor));
        
        // Reserve space for gramophone visualization
        picture_section_ = r.removeFromLeft(r.getWidth() - 250);
        
        // Right side for controls
        constexpr int iTextSectionWidth = 80;
        
        // Wow control
        wowSection = r.removeFromTop(controlHeight);
        wowTextSection = wowSection.removeFromLeft(iTextSectionWidth);
        wowTextSection = wowTextSection.withY(wowTextSection.getY() + labelVerticalOffset)
                                      .withHeight(wowTextSection.getHeight() - labelVerticalOffset);
        
        // Flutter control - only show if there's enough space
        if (getHeight() > 150) {
            flutterSection = r.removeFromTop(controlHeight);
            flutterTextSection = flutterSection.removeFromLeft(iTextSectionWidth);
            flutterTextSection = flutterTextSection.withY(flutterTextSection.getY() + labelVerticalOffset)
                                                  .withHeight(flutterTextSection.getHeight() - labelVerticalOffset);
        }
    }

    void drawWowFlutterLabels(juce::Graphics& g)
    {
        if (!isVisible())
            return;
        
        juce::Graphics::ScopedSaveState saveState(g);
        
        g.setFont(16.0f);
        g.setColour(juce::Colours::darkred);
        
        auto bounds = getLocalBounds();
        int margin = 10;
        
        g.drawFittedText("WOW", margin, margin, 80, 30, juce::Justification::left, 1);
        
        if (getHeight() > 150)
            g.drawFittedText("FLUTTER", margin, 80, 80, 30, juce::Justification::left, 1);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
        // Repaint the component when sliders change
        if (slider == &fFlutterControl) {
            // Map the flutter control (0-1) to appropriate ranges for rate and depth
            float flutterValue = fFlutterControl.getValue();
            
            // Update vibrato rate and depth parameters based on flutter value
            auto* rateParam = audioProcessor.apvts.getRawParameterValue("VIBRATO_RATE");
            auto* depthParam = audioProcessor.apvts.getRawParameterValue("VIBRATO_DEPTH");
            
            if (rateParam && depthParam) {
                // Map the flutter control value to appropriate parameter ranges
                // These mapping formulas can be adjusted to taste
                float newRate = 0.5f + (flutterValue * 3.5f);  // 0.5 to 4.0
                float newDepth = flutterValue * 0.33f;         // 0.0 to 0.33
                
                // Set parameter values without using attachments
                audioProcessor.apvts.getParameter("VIBRATO_RATE")->setValueNotifyingHost(
                    audioProcessor.apvts.getParameter("VIBRATO_RATE")->convertTo0to1(newRate));
                
                audioProcessor.apvts.getParameter("VIBRATO_DEPTH")->setValueNotifyingHost(
                    audioProcessor.apvts.getParameter("VIBRATO_DEPTH")->convertTo0to1(newDepth));
            }
        }
        
        repaint();
    }

    float sliderToAplhaValue(juce::Slider& slider)
    {
        double range = (slider.getMaximum() - slider.getMinimum());
        return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
    }

    juce::Slider fWowControl;
    juce::Slider fFlutterControl;  // Now controls both rate and depth

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

