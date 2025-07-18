/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

constexpr float LINE_THICKNESS = 4.0f;

//==============================================================================
VirtualGramoUIEditor::VirtualGramoUIEditor (VirtualGramoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), infoButtonUI (juce::Colours::darkgrey),
      stylusUI (p), wowFlutterUI(p), vinylCrackleUI(p)  // Add vinylCrackleUI initialization
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
    addAndMakeVisible(wowFlutterUI);  // Keep this line
    addAndMakeVisible(vinylCrackleUI);
    infoButtonUI.addToEditor(this);

    // Make the editor resizable with a resizable corner in the bottom-right
    setResizable(true, true);
    setResizeLimits(650, 400, 1200, 800); // Increased min width to 650

    setSize(1000, 600);
}

StylusUI::StylusUI(VirtualGramoAudioProcessor& p)
    : audioProcessor(p)
{

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
    g.fillAll(juce::Colours::silver);

    // Draw title with Century Gothic font
    g.setColour(juce::Colours::gold);
    juce::Font centuryGothic("Century Gothic", 40.0f, juce::Font::plain);
    g.setFont(centuryGothic);
    g.drawFittedText("Virtual Gramophone", getLocalBounds(), juce::Justification::centredTop, 1);

    // Let the StylusUI component draw the gramophone with our tone and mix values
    drawComponents(g, sliderToAplhaValue(fToneControl), sliderToAplhaValue(fMixControl));

    // Draw labels for tone and mix
    SetupSections();
    g.setFont(18.0f);
    g.setColour(juce::Colours::darkred);  // Make labels more visible
    g.drawFittedText("TONE", toneTextSection, juce::Justification::left, 1);
    g.drawFittedText("DRY", mixTextSection, juce::Justification::left, 1);
}

void StylusUI::paint(juce::Graphics& g)
{
    // This component is now empty
    g.fillAll(juce::Colours::transparentBlack);
}

void VirtualGramoUIEditor::drawComponents(juce::Graphics& g, float toneValue, float mixValue)
{
    // Get the current component bounds to determine where to draw the gramophone
    juce::Rectangle<int> visualArea = getLocalBounds().withWidth(getWidth() - 250).withHeight(getHeight() - 50);
    
    // Save the current state
    g.saveState();
    
    // Translate to center the gramophone in the visualization area
    g.addTransform(juce::AffineTransform::translation(
        visualArea.getWidth()/2 - 150, // Center horizontally
        visualArea.getHeight()/2 - 100  // Center vertically
    ));
    
    // Draw the gramophone with all its effects
    // Gramophone
    juce::Path funnel;
    juce::Path base;
    drawGramophoneModel(funnel, base);

    g.setColour(juce::Colour(0xff123456));
    g.fillPath(base);

    // Same as background to hide parts of base when funnel is painted with alpha
    g.setColour(juce::Colours::beige);
    g.fillPath(funnel);

    // Apply the tone value from outside
    g.setColour(juce::Colours::orange.withAlpha(0.2f + toneValue / 2.0f));
    g.fillPath(funnel);

    // Apply flutter effect (which controls both vibrato rate and depth)
    float flutterIntensity = sliderToAplhaValue(wowFlutterUI.fFlutterControl);
    g.setColour(juce::Colours::blueviolet.withAlpha(flutterIntensity / 4.0f));
    g.fillPath(funnel);
    
    g.setColour(juce::Colours::rebeccapurple.withAlpha(flutterIntensity / 3.0f));
    g.fillPath(funnel);

    // Apply wow effect
    g.setColour(juce::Colours::green.withAlpha(sliderToAplhaValue(wowFlutterUI.fWowControl) / 3.0f));
    g.fillPath(funnel);

    // Apply vinyl artifacts effects (combines crackle and dust)
    float vinylArtifactsIntensity = sliderToAplhaValue(vinylCrackleUI.fVinylArtifactsControl);
    if (vinylArtifactsIntensity > 0.0f) {
        // Vinyl crackle effect (reddish tint)
        g.setColour(juce::Colours::red.withAlpha(vinylArtifactsIntensity / 5.0f));
        g.fillPath(funnel);
        
        // Vinyl dust effect (brownish tint)
        g.setColour(juce::Colours::brown.withAlpha(vinylArtifactsIntensity / 6.0f));
        g.fillPath(funnel);
    }
    
    // Apply mix effect from outside (keep this after the other effects)
    g.setColour(juce::Colours::orangered.withAlpha(mixValue / 3.0f));
    g.fillPath(funnel);

    // Draw contours
    g.setColour(juce::Colour(0xff123456));
    drawGramophoneContours(g);
    
    // Restore the state
    g.restoreState();
}

void VirtualGramoUIEditor::drawGramophoneContours(juce::Graphics& g)
{
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
}

void VirtualGramoUIEditor::drawGramophoneModel(juce::Path& funnel, juce::Path& base)
{
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

    base.startNewSubPath(74.0f, 210.0f);
    base.lineTo(54.0f, 254.0f);
    base.lineTo(53.0f, 275.0f);
    base.lineTo(0.0F, 300.0f);
    base.lineTo(32.0F, 300.0f);
    base.lineTo(73.0f, 285.0f);
    base.lineTo(79.0f, 260.0f);
    base.lineTo(104.0F, 230.0f);
    base.closeSubPath();
}

void VirtualGramoUIEditor::drawThreePointLine(juce::Graphics& g,
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
    // Header area with title
    auto bounds = getLocalBounds();
    auto headerArea = bounds.removeFromTop(50);
    infoButtonUI.button.setBounds(headerArea.getRight() - 35, 10, 20, 20);
    
    // Right control panel
    auto rightPanel = bounds.removeFromRight(250);
    
    // Main area with gramophone visualization
    auto mainArea = bounds;
    
    // Position control components in the right panel
    int controlHeight = 100;
    
    // Tone control
    auto toneArea = rightPanel.removeFromTop(controlHeight);
    fToneControl.setBounds(toneArea.withTrimmedLeft(60));  // Make room for label
    
    // Mix control
    auto mixArea = rightPanel.removeFromTop(controlHeight);
    fMixControl.setBounds(mixArea.withTrimmedLeft(60));  // Make room for label
    
    // Since StylusUI is now empty, give all remaining space to other controls
    stylusUI.setBounds(0, 0, 0, 0);  // Hide StylusUI completely
    
    // Split remaining space between WowAndFlutterUI and VinylCrackleUI
    int remainingHeight = rightPanel.getHeight();
    int wowHeight = remainingHeight / 2;
    
    wowFlutterUI.setBounds(rightPanel.removeFromTop(wowHeight));
    vinylCrackleUI.setBounds(rightPanel);  // Give remaining space to VinylCrackleUI
    
    // Info text area
    infoButtonUI.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100);
}


void StylusUI::resized()
{

}

void VirtualGramoUIEditor::SetupSections()
{
    juce::Rectangle<int> r = getLocalBounds();
    top_section_ = r.removeFromTop(50);

    // Reserve right side for controls (250px width)
    juce::Rectangle<int> rightSide = r.removeFromRight(250);

    // Divide the right side into sections for controls
    constexpr int controlHeight = 100;  // Reduced from 200 to prevent overlap
    constexpr int iTextSectionWidth = 60;

    // Tone control (top)
    toneSection = rightSide.removeFromTop(controlHeight);
    toneTextSection = toneSection.removeFromLeft(iTextSectionWidth);

    // Mix control (below tone)
    mixSection = rightSide.removeFromTop(controlHeight);
    mixTextSection = mixSection.removeFromLeft(iTextSectionWidth);
}

void VirtualGramoUIEditor::sliderValueChanged (juce::Slider* /*slider*/)
{
    repaint();
}

void StylusUI::sliderValueChanged(juce::Slider* /*slider*/)
{

}
