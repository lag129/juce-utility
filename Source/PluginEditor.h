#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CustomGainSlider : public juce::Slider
{
public:
    CustomGainSlider() : juce::Slider() {}
    juce::String getTextFromValue(double value) override
    {
        return juce::String(value, 2) + " dB";
    }
};

class CustomPanSlider : public juce::Slider
{
public:
    CustomPanSlider() : juce::Slider() {}
    juce::String getTextFromValue(double value) override
    {
        panValue = value / 2;
        if (panValue > -1.0 && panValue < 1.0) {
            return "C";
        }
        else if (panValue <= -1.0) {
            return juce::String(static_cast<int>(-panValue)) + "L";
        }
        else if (panValue >= 1.0){
            return juce::String(static_cast<int>(panValue)) + "R";
        }
        return "";
    }
private:
    double panValue;
};

class UtilityAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    UtilityAudioProcessorEditor(UtilityAudioProcessor &,
                                juce::AudioProcessorValueTreeState &vts);

    ~UtilityAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    UtilityAudioProcessor &audioProcessor;
    int width = 220;
    int height = 260;

    juce::Rectangle<int> InputLabelArea{0, 0, width / 2, height / 8};
    juce::Rectangle<int> WidthArea{0, height * 5 / 16, width / 2, height * 3 / 8};
    juce::Rectangle<int> OutputLabelArea{width / 2, 0, width / 2, height / 8};
    juce::Rectangle<int> GainArea{width / 2, height / 8, width / 2, height * 3 / 8};
    juce::Rectangle<int> PannerArea{width / 2, height / 2, width / 2, height * 3 / 8};
    juce::Rectangle<int> MuteButtonArea{width / 2, height * 7 / 8, width / 4, height / 8};
    juce::Rectangle<int> DCButtonArea{width * 3 / 4, height * 7 / 8, width / 4, height / 8};

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::AudioProcessorValueTreeState &valueTreeState;

    juce::Slider widthSlider;

    CustomGainSlider gainSlider;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;

    CustomPanSlider panSlider;
    std::unique_ptr<SliderAttachment> panSliderAttachment;

    juce::TextButton muteButton;
    std::unique_ptr<ButtonAttachment> muteButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityAudioProcessorEditor)
};
