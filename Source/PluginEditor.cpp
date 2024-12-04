#include "PluginProcessor.h"
#include "PluginEditor.h"

UtilityAudioProcessorEditor::UtilityAudioProcessorEditor(
    UtilityAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    leftButtonAttachment.reset(new ButtonAttachment(valueTreeState, "L", leftButton));
    leftButton.setButtonText("∅L");
    leftButton.setClickingTogglesState(true);
    addAndMakeVisible(leftButton);

    rightButtonAttachment.reset(new ButtonAttachment(valueTreeState, "R", rightButton));
    rightButton.setButtonText("∅R");
    rightButton.setClickingTogglesState(true);
    addAndMakeVisible(rightButton);

    //gainSliderAttachment.reset(new SliderAttachment(valueTreeState, "gain", gainSlider));
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width * 2 / 3, GainArea.getHeight() / 6);
    addAndMakeVisible(widthSlider);

    gainSliderAttachment.reset(new SliderAttachment(valueTreeState, "gain", gainSlider));
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width * 2 / 3, GainArea.getHeight() / 6);
    addAndMakeVisible(gainSlider);

    panSliderAttachment.reset(new SliderAttachment(valueTreeState, "pan", panSlider));
    panSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width * 2 / 3, PannerArea.getHeight() / 6);
    addAndMakeVisible(panSlider);

    muteButtonAttachment.reset(new ButtonAttachment(valueTreeState, "mute", muteButton));
    muteButton.setButtonText("Mute");
    muteButton.setClickingTogglesState(true);
    addAndMakeVisible(muteButton);

    dcButtonAttachment.reset(new ButtonAttachment(valueTreeState, "dc", dcButton));
    dcButton.setButtonText("DC");
    dcButton.setClickingTogglesState(true);
    addAndMakeVisible(dcButton);

    setSize(width, height);
}

UtilityAudioProcessorEditor::~UtilityAudioProcessorEditor()
{
}

void UtilityAudioProcessorEditor::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colour::Colour(46, 52, 64));
    g.fillRect(WidthArea.toFloat());
    g.fillRect(GainArea.toFloat());
    g.fillRect(MuteButtonArea.toFloat());
}

void UtilityAudioProcessorEditor::resized()
{
    leftButton.setBounds(LeftButtonArea.reduced(5));
    rightButton.setBounds(RightButtonArea.reduced(5));
    widthSlider.setBounds(WidthArea.reduced(5));
    gainSlider.setBounds(GainArea.reduced(5));
    panSlider.setBounds(PannerArea.reduced(5));
    muteButton.setBounds(MuteButtonArea.reduced(5));
    dcButton.setBounds(DCButtonArea.reduced(5));
}
