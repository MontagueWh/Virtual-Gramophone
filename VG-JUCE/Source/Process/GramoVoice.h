/*
  ==============================================================================

    GramoVoice.h
    Created: 13 May 2025 11:10:55am
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <../Source/Libs/stk/include/Brass.h>

//==============================================================================
/*
*/
class GramoVoice : public juce::Component, public stk::Brass, public juce::AudioProcessor, juce::AudioSource
{
public:
    GramoVoice();
    ~GramoVoice() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override; // Prepares the processor for playback by initialising resources
    void releaseResources() override; // Releases resources when playback stops.
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override; // Processes audio and MIDI data for each block of samples

private:

    stk::Brass horn;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GramoVoice)
};
