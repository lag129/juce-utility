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

    juce::Rectangle<int> GainArea{ width, height * 1 / 2 };
    juce::Rectangle<int> PannerArea{ 0, height * 1 / 2, width, height / 2 };

    int mapPanValue() {
        double panValue = panSlider.getValue();
        return (panValue + 100) / 4 - 50;
    }

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::AudioProcessorValueTreeState &valueTreeState;

    CustomGainSlider gainSlider;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;

    CustomPanSlider panSlider;
    std::unique_ptr<SliderAttachment> panSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityAudioProcessorEditor)
};
