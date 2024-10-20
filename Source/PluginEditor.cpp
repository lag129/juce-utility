/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
UtilityAudioProcessorEditor::UtilityAudioProcessorEditor(
    UtilityAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    gainSliderAttachment.reset(new SliderAttachment(valueTreeState, "gain", gainSlider));
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width * 2 / 3, PannerArea.getHeight() / 6);
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider);

    panSliderAttachment.reset(new SliderAttachment(valueTreeState, "pan", panSlider));
    panSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width * 2 / 3, PannerArea.getHeight() / 6);
    addAndMakeVisible(panSlider);

    setSize(width, height);
}

UtilityAudioProcessorEditor::~UtilityAudioProcessorEditor()
{
}

//==============================================================================
void UtilityAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colour::Colour(46, 52, 64));
    g.fillRect(GainArea.toFloat());
}

void UtilityAudioProcessorEditor::resized()
{
    gainSlider.setBounds(GainArea.reduced(5));
    panSlider.setBounds(PannerArea.reduced(5));
}
