/*
  ==============================================================================

    GramoVoice.cpp
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GramoVoice.h"
#include <../Source/Libs/stk/include/Brass.h>

//==============================================================================
Gramo::Gramo()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Gramo::~Gramo()
{
}

void Gramo::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Gramo", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Gramo::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
