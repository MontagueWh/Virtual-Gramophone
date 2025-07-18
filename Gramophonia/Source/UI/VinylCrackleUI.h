/*
  ==============================================================================

    VinylCrackleUI.h
    Created: 18 Jul 2025 7:03:46pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Data/VinylCrackleData.h"
#include "../PluginProcessor.h"

class VinylCrackleUI : public juce::Component,
                      public juce::Slider::Listener
{
public:
    VinylCrackleUI(VirtualGramoAudioProcessor& p) : audioProcessor(p)
    {
        // Main crackle control
        fCrackleControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fCrackleControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fCrackleControl.addListener(this);
        addAndMakeVisible(fCrackleControl);

        crackleControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "CRACKLE", fCrackleControl);

        // Dust control - affected by crackle intensity but can be adjusted separately
        fDustControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fDustControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fDustControl.setRange(0.0f, 1.0f);  // Normalized range 0-1
        fDustControl.setValue(0.0f);        // Start at 0
        fDustControl.addListener(this);
        addAndMakeVisible(fDustControl);

        // We'll manually update dust intensity when crackle control changes
        dustControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "DUST", fDustControl);
    }

    ~VinylCrackleUI() override
    {
    }

    void paint(juce::Graphics& g) override
    {
        // Background with slight color tint
        g.fillAll(juce::Colours::lightgrey.withAlpha(0.1f));

        // Draw labels directly in the component's paint method
        drawVinylCrackleLabels(g);
    }

    void resized() override
    {
        setupSections();
        fCrackleControl.setBounds(crackleSection);
        fDustControl.setBounds(dustSection);
    }

    void setupSections()
    {
        juce::Rectangle<int> r = getLocalBounds();
        
        // Calculate a scale factor based on the actual height of the component
        float heightScaleFactor = juce::jmin(1.0f, (float)getHeight() / 275.0f);
        
        // Adjust control heights based on available space
        int controlHeight = juce::jmax(40, (int)(80 * heightScaleFactor));
        int labelVerticalOffset = juce::jmax(20, (int)(40 * heightScaleFactor));
        
        // Reserve space for visualization
        picture_section_ = r.removeFromLeft(r.getWidth() - 250);
        
        // Right side for controls
        constexpr int iTextSectionWidth = 80;
        
        // Crackle control
        crackleSection = r.removeFromTop(controlHeight);
        crackleTextSection = crackleSection.removeFromLeft(iTextSectionWidth);
        crackleTextSection = crackleTextSection.withY(crackleTextSection.getY() + labelVerticalOffset)
                                         .withHeight(crackleTextSection.getHeight() - labelVerticalOffset);
        
        // Dust control - only show if there's enough space
        if (getHeight() > 150) {
            dustSection = r.removeFromTop(controlHeight);
            dustTextSection = dustSection.removeFromLeft(iTextSectionWidth);
            dustTextSection = dustTextSection.withY(dustTextSection.getY() + labelVerticalOffset)
                                       .withHeight(dustTextSection.getHeight() - labelVerticalOffset);
        }
    }

    void drawVinylCrackleLabels(juce::Graphics& g)
    {
        if (!isVisible())
            return;
        
        juce::Graphics::ScopedSaveState saveState(g);
        
        g.setFont(16.0f);
        g.setColour(juce::Colours::darkred);
        
        auto bounds = getLocalBounds();
        int margin = 10;
        
        g.drawFittedText("CRACKLE", margin, margin, 80, 30, juce::Justification::left, 1);
        
        if (getHeight() > 150)
            g.drawFittedText("DUST", margin, 80, 80, 30, juce::Justification::left, 1);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
        // Repaint the component when sliders change
        if (slider == &fCrackleControl) {
            // Map the crackle control (0-1) to dust intensity
            float crackleValue = fCrackleControl.getValue();
            
            // Update dust parameters based on crackle value
            auto* dustParam = audioProcessor.apvts.getRawParameterValue("DUST_INTENSITY");
            
            if (dustParam) {
                // Map the crackle value to dust intensity - make dust slightly less intense than crackle
                float newDustIntensity = crackleValue * 0.7f;
                
                // Set parameter value without using attachments
                audioProcessor.apvts.getParameter("DUST_INTENSITY")->setValueNotifyingHost(
                    audioProcessor.apvts.getParameter("DUST_INTENSITY")->convertTo0to1(newDustIntensity));
            }
        }
        
        repaint();
    }

    float sliderToAlphaValue(juce::Slider& slider)
    {
        double range = (slider.getMaximum() - slider.getMinimum());
        return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
    }

    juce::Slider fCrackleControl;
    juce::Slider fDustControl;

private:
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    SliderAttachmentPtr crackleControlAttach;
    SliderAttachmentPtr dustControlAttach;

    juce::Rectangle<int> picture_section_;
    juce::Rectangle<int> crackleSection;
    juce::Rectangle<int> dustSection;
    juce::Rectangle<int> crackleTextSection;
    juce::Rectangle<int> dustTextSection;

    const int TEXT_BOX_SIZE = 25;

    VirtualGramoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VinylCrackleUI)
};
