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
        // Single control for vinyl artefacts (combines crackle, dust and dust intensity)
        fVinylArtifactsControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        fVinylArtifactsControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
        fVinylArtifactsControl.addListener(this);
        addAndMakeVisible(fVinylArtifactsControl);

        vinylArtifactsControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.apvts, "VINYL_ARTIFACTS", fVinylArtifactsControl);
    }

    ~VinylCrackleUI() override
    {
    }

    void paint(juce::Graphics& g) override
    {
        // Background with slight color tint
        g.fillAll(juce::Colours::lightgrey.withAlpha(0.1f));

        // Draw labels
        g.setFont(16.0f);
        g.setColour(juce::Colours::darkred);
        g.drawFittedText("VINYL ARTIFACTS", 10, 10, 100, 30, juce::Justification::left, 1);
    }

    void resized() override
    {
        setupSections();
        fVinylArtifactsControl.setBounds(vinylSection);
    }

    void setupSections()
    {
        juce::Rectangle<int> r = getLocalBounds();
        
        // Calculate a scale factor based on the actual height of the component
        float fHeightScaleFactor = juce::jmin(1.0f, (float)getHeight() / 275.0f);
        
        // Adjust control heights based on available space
        int iControlHeight = juce::jmax(40, (int)(100 * fHeightScaleFactor));
        
        // Reserve space for visualization
        pictureSection = r.removeFromLeft(r.getWidth() - 250);
        
        // Right side for controls
        constexpr int iTextSectionWidth = 80;
        
        // Vinyl artifacts control
        vinylSection = r.removeFromTop(iControlHeight);
        vinylTextSection = vinylSection.removeFromLeft(iTextSectionWidth);
        vinylTextSection = vinylTextSection.withY(vinylTextSection.getY() + 40)
                                   .withHeight(vinylTextSection.getHeight() - 40);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
        if (slider == &fVinylArtifactsControl) {
            float vinylValue = fVinylArtifactsControl.getValue();
            
            // Define scaling factors for different parameters
            constexpr float CRACKLE_SCALE = 1.0f;         // 100% of vinyl value
            constexpr float DUST_SCALE = 0.8f;            // 80% of vinyl value
            constexpr float DUST_INTENSITY_SCALE = 0.85f; // 85% of vinyl value
            
            // Map of parameters to update with their scaling factors
            const std::pair<const char*, float> paramMappings[] = {
                {"CRACKLE", CRACKLE_SCALE},
                {"DUST", DUST_SCALE},
                {"DUST_INTENSITY", DUST_INTENSITY_SCALE}
            };
            
            // Update all parameters based on vinyl value with appropriate scaling
            for (const auto& [paramID, scaleFactor] : paramMappings) {
                auto* param = audioProcessor.apvts.getParameter(paramID);
                if (param) {
                    // Apply scaling factor to the vinyl artefacts value
                    float scaledValue = vinylValue * scaleFactor;
                    param->setValueNotifyingHost(param->convertTo0to1(scaledValue));
                }
            }
        }
        
        repaint();
    }

    float sliderToAlphaValue(juce::Slider& slider)
    {
        double range = (slider.getMaximum() - slider.getMinimum());
        return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
    }

    juce::Slider fVinylArtifactsControl;
    
    // Keep old controls as public members to maintain compatibility with existing code
    // These will be removed or hidden from the UI
    juce::Slider fCrackleControl; 
    juce::Slider fDustControl;

private:
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    SliderAttachmentPtr vinylArtifactsControlAttach;

    juce::Rectangle<int> pictureSection;
    juce::Rectangle<int> vinylSection;
    juce::Rectangle<int> vinylTextSection;

    const int TEXT_BOX_SIZE = 25;

    VirtualGramoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VinylCrackleUI)
};
