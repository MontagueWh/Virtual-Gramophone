/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h" // Includes the header file for the plugin editor.
#include "PluginProcessor.h" // Includes the header file for the plugin processor.


constexpr float LINE_THICKNESS = 4.0f; // Defines the thickness of lines drawn in the editor.

//==============================================================================
// Constructor for the plugin editor.
VirtualGramoAudioProcessorEditor::VirtualGramoAudioProcessorEditor(VirtualGramoAudioProcessor& p)
   : AudioProcessorEditor(&p), audioProcessor(p), gramoVoice(p.gramoVoice), info_button_(juce::Colours::darkgrey)
{
    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.

    additionalEffectsParamsSetup(TEXT_BOX_SIZE);
    wetDryParamSetup(TEXT_BOX_SIZE);
    gramoParamSetup();

    // Adds the info button to the editor.
    info_button_.addToEditor(this);

	//addAndMakeVisible(gramoModelLoader); // Adds the model loader to the editor.

    setSize(1500, 1500); // Sets the initial size of the editor window.
	setResizable(true, true);
}

void VirtualGramoAudioProcessorEditor::gramoParamSetup()
{
    gramoVoice.initaliseGramoVoice(); // Initialise the gramophone component.

    // Sets up the stylus parameters.
    gramoVoice.stylusPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "STYLUS_PRESSURE", gramoVoice.stylusPressureParam); // Attach the stylus pressure slider to the parameter tree.
    gramoVoice.vinylFilterFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VINYL_FILTER_FREQ", gramoVoice.vinylFilterFreqParam); // Attach the vinyl filter frequency slider to the parameter tree.
    gramoVoice.pitchShiftAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "PITCH_SHIFT", gramoVoice.pitchShiftParam); // Attach the pitch shift slider to the parameter tree.

    // Sets up the soundbox parameters.
    gramoVoice.soundboxPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SOUNDBOX_PRESSURE", gramoVoice.soundboxPressureParam); // Attach the soundbox pressure slider to the parameter tree.
    gramoVoice.noiseGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "NOISE_GAIN", gramoVoice.noiseGainParam); // Attach the noise gain slider to the parameter tree.
    gramoVoice.vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_DEPTH", gramoVoice.vibratoDepthParam); // Attach the vibrato depth slider to the parameter tree.
    gramoVoice.vibratoRateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_RATE", gramoVoice.vibratoRateParam); // Attach the vibrato frequency slider to the parameter tree.
    gramoVoice.vibratoGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_GAIN", gramoVoice.vibratoGainParam); // Attach the vibrato gain slider to the parameter tree.
    gramoVoice.vibratoMixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_MIX", gramoVoice.vibratoMixParam); // Attach the vibrato mix slider to the parameter tree.

    // Sets up the horn parameters.
    gramoVoice.hornStiffnessAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HORN_STIFFNESS", gramoVoice.hornStiffnessParam); // Attach the horn stiffness slider to the parameter tree.
    gramoVoice.hornDiameterAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HORN_DIAMETER", gramoVoice.hornDiameterParam); // Attach the horn diameter slider to the parameter tree.
    gramoVoice.hornLengthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HORN_LENGTH", gramoVoice.hornLengthParam); // Attach the horn length slider to the parameter tree.

	addAndMakeVisible(gramoVoice); // Makes the GramoVoice component visible in the editor.
}

// Destructor for the plugin editor.
VirtualGramoAudioProcessorEditor::~VirtualGramoAudioProcessorEditor()
{
}

//==============================================================================
// Paints the editor's GUI components.
void VirtualGramoAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::beige);

    g.setColour(juce::Colour(0xff123456));
    g.setFont(40.0f);
    g.drawFittedText("Virtual Gramophone", getLocalBounds(), juce::Justification::centredTop, 1);

    setupSections();

    g.setFont(18.0f);
    g.drawFittedText("TONE", toneTextSection, juce::Justification::left, 1);
    g.drawFittedText("VIBE", vibratoTextSection, juce::Justification::left, 1);
    g.drawFittedText("DRY", wetDryTextSection, juce::Justification::left, 1);

	gramoVoice.paint(g); // Calls the paint method of the GramoVoice instance to draw its components.
}

// Converts a slider's value to an alpha (transparency) value.
float VirtualGramoAudioProcessorEditor::sliderToAplhaValue(juce::Slider& slider)
{
    double range = (slider.getMaximum() - slider.getMinimum());
    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);
}

// Handles resizing and layout of GUI components.
void VirtualGramoAudioProcessorEditor::resized()
{
    info_button_.button.setBounds(getWidth() - 35, 10, 20, 20); // Positions the info button.
    info_button_.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100); // Positions the info text.
    setupSections(); // Updates the layout sections.
    compressThreshParam.setBounds(compressSection); // Positions the compression slider.
    toneParam.setBounds(toneSection); // Positions the tone slider.
    vibratoDepthParam.setBounds(vibratoDepthSection); // Positions the vibrato slider.
    vibratoRateParam.setBounds(vibratoRateSection); // Positions the vibrato rate slider.
    wetDryParam.setBounds(wetDrySection); // Positions the mix slider.

	gramoVoice.resized(); // Calls the resized method of the GramoVoice instance to update its layout.
}

// Sets up the layout sections for the GUI.
void VirtualGramoAudioProcessorEditor::setupSections()
{
    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.
    topSection = r.removeFromTop(50); // Allocates the top section.

    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.
    int sectionHeight = interfaceSection.getHeight() / 4; // Divides the interface into four sections.
    constexpr int textSectionWidth = 40; // Width for the text labels.

    // Allocates sections for sliders and their labels.
    compressSection = interfaceSection.removeFromTop(sectionHeight);
    compressTextSection = compressSection.removeFromLeft(textSectionWidth);

	toneSection = interfaceSection.removeFromTop(sectionHeight);
	toneTextSection = toneSection.removeFromLeft(textSectionWidth);

	vibratoDepthSection = interfaceSection.removeFromTop(sectionHeight);
    vibratoRateSection = interfaceSection.removeFromTop(sectionHeight);
	vibratoTextSection = vibratoDepthSection.removeFromLeft(textSectionWidth);

    wetDrySection = interfaceSection;
    wetDrySection = interfaceSection.removeFromTop(textSectionWidth);
}

void VirtualGramoAudioProcessorEditor::additionalEffectsParamsSetup(const int TEXT_BOX_SIZE)
{
    // Sets up the compression slider.
    compressThreshParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.
    compressThreshParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.
    compressThreshParam.addListener(this); // Adds this editor as a listener for slider changes.
    addAndMakeVisible(compressThreshParam); // Makes the slider visible in the editor.

    // Links the compression slider to the "COMPRESS" parameter in the processor's parameter tree.
    compressThreshAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "COMPRESS", compressThreshParam);

    // Sets up the tone slider.
    toneParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    toneParam.addListener(this);
    addAndMakeVisible(toneParam);
    toneAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TONE", toneParam);

    // Sets up the vibrato slider.
    vibratoDepthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibratoDepthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoDepthParam.addListener(this);
    addAndMakeVisible(vibratoDepthParam);
    vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_DEPTH", vibratoDepthParam);

    // Sets up the vibrato rate slider.
    vibratoRateParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vibratoRateParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    vibratoRateParam.addListener(this);
    addAndMakeVisible(vibratoRateParam);
    vibratoRateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VIBRATO_RATE", vibratoRateParam);
}
void VirtualGramoAudioProcessorEditor::wetDryParamSetup(const int TEXT_BOX_SIZE)
{
    // Sets up the mix slider.
    wetDryParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetDryParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);
    wetDryParam.addListener(this);
    addAndMakeVisible(wetDryParam);
    wetDryAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", wetDryParam);
}

// Callback for when a slider's value changes.
void VirtualGramoAudioProcessorEditor::sliderValueChanged(juce::Slider* /*slider*/)
{
    repaint(); // Repaints the editor to reflect the updated slider value.
}