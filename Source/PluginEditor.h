#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CustomGainSlider : public juce::Slider {
public:
    CustomGainSlider() : juce::Slider() {}
    juce::String getTextFromValue(double value) override {
        return juce::String(value, 2) + " dB";
    }
};

class CustomPanSlider : public juce::Slider {
public:
    CustomPanSlider() : juce::Slider() {}
    juce::String getTextFromValue(double value) override {
        if (static_cast<int>(value/2) == 0) {
            return "C";
        }
        else if (value < 0) {
            return juce::String(static_cast<int>(-value / 2)) + "L";
        }
        else {
            return juce::String(static_cast<int>(value / 2)) + "R";
        }
    }
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
    int width = 200;
    int height = 300;

    juce::Rectangle<int> OutputLabelArea{width / 2, 0, width / 2, height / 8};
    juce::Rectangle<int> GainArea{width / 2, height / 8, width / 2, height * 3 / 8};
    juce::Rectangle<int> PannerArea{width / 2, height / 2, width / 2, height * 3 / 8};
    juce::Rectangle<int> MuteButtonArea{width / 2, height * 7 / 8, width / 4, height / 8};
    juce::Rectangle<int> DCButtonArea{width / 4, height * 7 / 8, width / 4, height / 8};

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::AudioProcessorValueTreeState &valueTreeState;

    CustomGainSlider gainSlider;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;

    CustomPanSlider panSlider;
    std::unique_ptr<SliderAttachment> panSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityAudioProcessorEditor)
};
