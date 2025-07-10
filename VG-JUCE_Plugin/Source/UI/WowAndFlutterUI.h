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

class WowAndFlutterUI : public juce::Component, public juce::Slider::Listener
{
public:
    WowAndFlutterUI(WowAndFlutter& wowAndFlutterData)
        : wowAndFlutter(wowAndFlutterData)
    {
        setSize(100, 300);

        fWowControl.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        fWowControl.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
        fWowControl.setRange(0.0f, 1.0f);
        fWowControl.setValue(0.5f);
        fWowControl.addListener(this);
        addAndMakeVisible(&fWowControl);
    }

    ~WowAndFlutterUI() override
    {
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.drawText("Wow and Flutter", getLocalBounds(), juce::Justification::centred, true);
    }
    
    void sliderValueChanged(juce::Slider* slider) override
    {
        if (slider == &fWowControl)
            wowAndFlutter.fWowControl = slider->getValue();
    }

private:
    WowAndFlutter& wowAndFlutter;
    juce::Slider fWowControl;
};