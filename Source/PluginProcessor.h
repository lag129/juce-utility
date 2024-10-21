#pragma once
#include <JuceHeader.h>

class UtilityAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    UtilityAudioProcessor();
    ~UtilityAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
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
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

private:
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float> *gain = parameters.getRawParameterValue("gain");
    std::atomic<float> *pan = parameters.getRawParameterValue("pan");
    std::atomic<float> *mute = parameters.getRawParameterValue("mute");
    //std::atomic<float> *dc = parameters.getRawParameterValue("dc");

    juce::dsp::Gain<float> gainDSP;
    juce::dsp::Panner<float> pannerDSP;
    juce::dsp::Gain<float> muteDSP;
    juce::dsp::ProcessSpec spec;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UtilityAudioProcessor)
};
