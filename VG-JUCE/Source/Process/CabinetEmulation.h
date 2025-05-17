/*
  ==============================================================================

    CabinetEmulation.h
    Created: 17 May 2025 6:51:21pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CabinetEmulation  : public juce::Component
{
public:
    CabinetEmulation();
    ~CabinetEmulation() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabinetEmulation)
};
