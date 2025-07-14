/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

constexpr float LINE_THICKNESS = 4.0f;
constexpr int TEXT_BOX_SIZE = 25;

//==============================================================================
VirtualGramoUIEditor::VirtualGramoUIEditor (VirtualGramoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), infoButtonUI (juce::Colours::darkgrey), stylusUI (p)
{

    fToneControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fToneControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    fToneControl.addListener(this);
    addAndMakeVisible(fToneControl);

    toneControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TONE", fToneControl);

    fMixControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fMixControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    fMixControl.addListener(this);
    addAndMakeVisible(fMixControl);

    mixControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", fMixControl);

    addAndMakeVisible(stylusUI);
    infoButtonUI.addToEditor(this);

    // Make the editor resizable with a resizable corner in the bottom-right
    setResizable(true, true);
    setResizeLimits(500, 300, 1200, 800); // Min size 500x300, max size 1200x800

    setSize(500, 300);
}

StylusUI::StylusUI(VirtualGramoAudioProcessor& p)
    : audioProcessor(p)
{

    fCompressControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fCompressControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    fCompressControl.addListener(this);
    addAndMakeVisible(fCompressControl);

    compressControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "COMPRESS", fCompressControl);

    fVibratoDepthControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fVibratoDepthControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    fVibratoDepthControl.addListener(this);
    addAndMakeVisible(fVibratoDepthControl);

    vibratoDepthControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "VIBRATO_DEPTH", fVibratoDepthControl);

    fVibratoRateControl.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fVibratoRateControl.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    fVibratoRateControl.addListener(this);
    addAndMakeVisible(fVibratoRateControl);

    vibratoRateControlAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "VIBRATO_RATE", fVibratoRateControl);
}

StylusUI::~StylusUI()
{

}

VirtualGramoUIEditor::~VirtualGramoUIEditor()
{
}

void VirtualGramoUIEditor::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::darkgoldenrod);

    // Draw title
    g.setColour(juce::Colour(0xff123456));
    g.setFont(40.0f);
    g.drawFittedText("GRAMOPHONY", getLocalBounds(), juce::Justification::centredTop, 1);

    // Let the StylusUI component draw the gramophone with our tone and mix values
    stylusUI.drawGramophone(g, sliderToAplhaValue(fToneControl), sliderToAplhaValue(fMixControl));

    // Draw labels for tone and mix
    SetupSections();
    g.setFont(18.0f);
    g.drawFittedText("TONE", toneTextSection, juce::Justification::left, 1);
    g.drawFittedText("DRY", mixTextSection, juce::Justification::left, 1);
}

void StylusUI::paint(juce::Graphics& g)
{
    
}

void StylusUI::drawGramophone(juce::Graphics& g, float toneValue, float mixValue)
{
    // Gramophone
    juce::Path funnel;
    funnel.startNewSubPath(8.0f, 102.0f);
    funnel.lineTo(43.0f, 48.0f);
    funnel.lineTo(113.0f, 38.0f);
    funnel.lineTo(194.0f, 55.0);
    funnel.lineTo(258.0f, 109.0f);
    funnel.lineTo(279.0f, 171.0f);
    funnel.lineTo(252.0f, 225.0f);
    funnel.lineTo(174.0f, 245.0f);
    funnel.lineTo(92.0f, 229.0f);
    funnel.lineTo(25.0f, 166.0f);
    funnel.closeSubPath();

    juce::Path base;
    base.startNewSubPath(74.0f, 210.0f);
    base.lineTo(54.0f, 254.0f);
    base.lineTo(53.0f, 275.0f);
    base.lineTo(0.0F, 300.0f);
    base.lineTo(32.0F, 300.0f);
    base.lineTo(73.0f, 285.0f);
    base.lineTo(79.0f, 260.0f);
    base.lineTo(104.0F, 230.0f);
    base.closeSubPath();

    g.setColour(juce::Colour(0xff123456));
    g.fillPath(base);

    // Same as background to hide parts of base when funnel is painted with alpha
    g.setColour(juce::Colours::beige);
    g.fillPath(funnel);

    // Apply the tone value from outside
    g.setColour(juce::Colours::orange.withAlpha(0.2f + toneValue / 2.0f));
    g.fillPath(funnel);

    // Apply compression effect
    g.setColour(juce::Colours::yellow.withAlpha(sliderToAplhaValue(fCompressControl) / 2.0f));
    g.fillPath(funnel);

    // Apply vibrato effects
    g.setColour(juce::Colours::blueviolet.withAlpha(sliderToAplhaValue(fVibratoDepthControl) / 4.0f));
    g.fillPath(funnel);

    g.setColour(juce::Colours::rebeccapurple.withAlpha(sliderToAplhaValue(fVibratoRateControl) / 3.0f));
    g.fillPath(funnel);

    // Apply mix effect from outside
    g.setColour(juce::Colours::orangered.withAlpha(mixValue / 3.0f));
    g.fillPath(funnel);

    // Draw contours
    g.setColour(juce::Colour(0xff123456));
    drawThreePointLine(g, 73.0f, 179.0f, 62.0f, 144.0f, 8.0f, 102.0f);
    drawThreePointLine(g, 85.0f, 189.0f, 83.0f, 133.0f, 43.0f, 48.0f);
    drawThreePointLine(g, 92.0f, 193.0f, 105.0f, 129.0f, 113.0f, 38.0f);
    drawThreePointLine(g, 101.0f, 201.0f, 144.0f, 126.0f, 194.0f, 55.0f);
    drawThreePointLine(g, 108.0f, 203.0f, 176.0f, 145.0f, 258.0f, 109.0f);
    drawThreePointLine(g, 122.0f, 209.0f, 188.0f, 179.0f, 279.0f, 171.0f);
    drawThreePointLine(g, 136.0f, 211.0f, 174.0f, 202.0f, 252.0f, 225.0f);
    drawThreePointLine(g, 108.0f, 203.0f, 144.0f, 215.0f, 174.0f, 245.0f);
    drawThreePointLine(g, 108.0f, 203.0f, 73.0f, 179.0f, 25.0f, 166.0f);
    g.drawLine(juce::Line<float>(108.0f, 203.0f, 92.0f, 229.0f), LINE_THICKNESS);

    // Draw labels
    setupSections();
    g.setFont(18.0f);
    g.drawFittedText("COMP", compressTextSection, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibratoTextSection, juce::Justification::left, 1);
}


void StylusUI::drawThreePointLine(juce::Graphics& g,
    float x1, float y1,
    float x2, float y2,
    float x3, float y3)
{
    g.drawLine(juce::Line<float>(x1, y1, x2, y2), LINE_THICKNESS);
    g.drawLine(juce::Line<float>(x2, y2, x3, y3), LINE_THICKNESS);
}

float VirtualGramoUIEditor::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

float StylusUI::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

void VirtualGramoUIEditor::resized()
{
    infoButtonUI.button.setBounds(getWidth() - 35, 10, 20, 20);
    infoButtonUI.infoText.setBounds(30, 50, getWidth() - 60, getHeight() - 100);

    SetupSections();

    // Position the StylusUI component
    stylusUI.setBounds(0, 50, getWidth(), 200);

    fToneControl.setBounds(toneSection);
    fMixControl.setBounds(mixSection);
}


void StylusUI::resized()
{
    setupSections();
    fCompressControl.setBounds(compressSection);
    fVibratoDepthControl.setBounds(vibratoDepthSection);
    fVibratoRateControl.setBounds(vibratoRateSection);
}

void VirtualGramoUIEditor::SetupSections()
{
    juce::Rectangle<int> r = getLocalBounds();
    top_section_ = r.removeFromTop(50);

    // Skip the stylus section
    r.removeFromTop(200);

    // Bottom controls section
    juce::Rectangle<int> controlsSection = r;
    constexpr int iTextSectionWidth = 40;

    toneSection = controlsSection.removeFromLeft(controlsSection.getWidth() / 2);
    toneTextSection = toneSection.removeFromLeft(iTextSectionWidth);

    mixSection = controlsSection;
    mixTextSection = mixSection.removeFromLeft(iTextSectionWidth);
}

void StylusUI::setupSections()
{
    juce::Rectangle<int> r = getLocalBounds();
    picture_section_ = r.removeFromLeft(310);

    juce::Rectangle<int> interfaceSection = r;
    int iSectionHeight = interfaceSection.getHeight() / 2;
    constexpr int iTextSectionWidth = 40;

    compressSection = interfaceSection.removeFromTop(iSectionHeight);
    compressTextSection = compressSection.removeFromLeft(iTextSectionWidth);

    vibratoDepthSection = interfaceSection;
    vibratoTextSection = vibratoDepthSection.removeFromLeft(iTextSectionWidth);
    vibratoRateSection = vibratoDepthSection.removeFromRight(vibratoDepthSection.getWidth() / 2);
}

void VirtualGramoUIEditor::sliderValueChanged (juce::Slider* /*slider*/)
{
    repaint();
}

void StylusUI::sliderValueChanged(juce::Slider* /*slider*/)
{
    // Repaint the component when sliders change
    repaint();
}
