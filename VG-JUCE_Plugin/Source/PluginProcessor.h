/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Data/WowAndFlutterData.h"

//==============================================================================
/**
*/
class VGJUCE_PluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    VGJUCE_PluginAudioProcessor();
    ~VGJUCE_PluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    class StylusComponent
    {
    public:
        const float BP_FREQ = 2950.0f;

        WowAndFlutter wowAndFlutter; // Instance of the Wow and Flutter effect

        void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
        {
            juce::dsp::ProcessSpec spec = { sampleRate, static_cast<juce::uint32>(samplesPerBlock),
                                static_cast<juce::uint32>(numChannels) };

            chorus_.prepare(spec);

            mix_.prepare(spec);

            float frequency = apvts.getRawParameterValue("TONE")->load();
            filter_ch1_.prepare(spec);
            filter_ch1_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency, 6.0f);

            filter_ch2_.prepare(spec);
            filter_ch2_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency, 6.0f);
        }

        void process(juce::AudioBuffer<float>& input, float sample, double sampleRate, juce::AudioBuffer<float>& output)
        {
            for (int channel = 0; channel < input.getNumChannels(); ++channel)
            {

                // TODO: make this value tweakable.
                float treshold = apvts.getRawParameterValue("COMPRESS")->load();
                float frequency = apvts.getRawParameterValue("TONE")->load();

                wowAndFlutter.applyModulation(&input, input.getNumSamples(), &output, output.getNumSamples(), wowAndFlutter.fWowControl, wowAndFlutter.fFlutterControl, sampleRate);

                if (*input.getReadPointer(channel, sample) >= treshold)
                {
                    *input.getWritePointer(channel, sample) = (*input.getReadPointer(channel, sample) / 4) + (3 * treshold / 4);
                }
                else if (*input.getReadPointer(channel, sample) <= -treshold)
                {
                    *input.getWritePointer(channel, sample) = (*input.getReadPointer(channel, sample) / 4) - (3 * treshold / 4);
                }
                // Partly calculated partly by ear set makeup gain.
                *input.getWritePointer(channel, sample) *= 5.0f - (11.0f * treshold * treshold);

                if (channel == 0)
                {
                    filter_ch1_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency + 10.0f, 2.7f);
                    *input.getWritePointer(channel, sample) = filter_ch1_.processSample(*input.getReadPointer(channel, sample));
                }
                else if (channel == 1)
                {
                    filter_ch2_.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency - 10.0f, 2.73f);
                    *input.getWritePointer(channel, sample) = filter_ch2_.processSample(*input.getReadPointer(channel, sample));
                }
            }

            auto block = juce::dsp::AudioBlock<float>(input);
            auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);

            chorus_.setRate(apvts.getRawParameterValue("VIBRATO_RATE")->load());
            chorus_.setDepth(apvts.getRawParameterValue("VIBRATO")->load());
            chorus_.setCentreDelay(1.0f);
            chorus_.setFeedback(0.0f);
            chorus_.setMix(1.0f);

            chorus_.process(contextToUse);

            mix_.setWetMixProportion(1.0f - apvts.getRawParameterValue("MIX")->load());
            mix_.mixWetSamples(block);
        }

    private:

        juce::dsp::Chorus<float> chorus_;
        juce::dsp::IIR::Filter<float> filter_ch1_;
        juce::dsp::IIR::Filter<float> filter_ch2_;
        juce::dsp::DryWetMixer<float> mix_;
    };

    juce::AudioProcessorValueTreeState apvts;

private:
    //==============================================================================

    StylusComponent stylusComponent;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VGJUCE_PluginAudioProcessor)
};
