#include "InfoButton.h"

InfoButton::InfoButton (juce::Colour colour)
{
    button.setButtonText ("i");
    button.addListener (this);

    infoText.setColour (juce::Label::backgroundColourId, colour);
    infoText.setColour (juce::Label::outlineColourId, juce::Colours::white);
    infoText.setColour (juce::Label::textColourId, juce::Colours::blue);
    infoText.setJustificationType (juce::Justification::centredLeft);
    infoText.setBorderSize (juce::BorderSize<int> (20, 70, 20, 70));

    std::string sInfoString = "";
    sInfoString += ProjectInfo::companyName + std::string (" ") + ProjectInfo::projectName + std::string (" version ") + ProjectInfo::versionString + std::string ("\n\n");

    infoText.setText (sInfoString, juce::dontSendNotification);
}

InfoButton::~InfoButton() {}

void InfoButton::addToEditor (juce::AudioProcessorEditor* editor)
{
    editor->addAndMakeVisible (infoText);
    infoText.setVisible (false);
    editor->addAndMakeVisible (button);
}

void InfoButton::buttonStateChanged (juce::Button* b)
{
    if (b == &button)
    {
        if (button.isOver())
        {
            infoText.setVisible (true);
        }
        else
        {
            infoText.setVisible (false);
        }
    }
}

void InfoButton::buttonClicked (juce::Button* button)
{
}
