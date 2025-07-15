/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VirtualGramophoneAudioProcessorEditor::VirtualGramophoneAudioProcessorEditor (VirtualGramophoneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), infoButtonUI(juce::Colours::darkgrey)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    infoButtonUI.addToEditor(this);

    setSize (800, 600);
}

VirtualGramophoneAudioProcessorEditor::~VirtualGramophoneAudioProcessorEditor()
{
}

//==============================================================================
void VirtualGramophoneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::gold);

    // Draw title
    g.setColour(juce::Colour(0xff123456));
    g.setFont(juce::Font("Didot", 40.0f, juce::Font::italic));
    g.drawFittedText("Virtual Gramophone", getLocalBounds(), juce::Justification::centredTop, 1);
}

void VirtualGramophoneAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	setResizable(true, true);
}
