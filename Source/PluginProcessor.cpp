/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
UtilityAudioProcessor::UtilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , parameters(*this, nullptr, juce::Identifier("UtilityAudioProcessor"), {
        std::make_unique<juce::AudioParameterFloat>(
            "gain",
            "Gain",
            juce::NormalisableRange<float>(-100.0f, 30.0f),
            0.0f),
        std::make_unique<juce::AudioParameterFloat>(
            "pan", 
            "Pan", 
            juce::NormalisableRange<float>(-100.0f, 100.0f),
            0.0f),
        std::make_unique<juce::AudioParameterBool>(
           "mute",
           "Mute",
           false),
    })
{
    gain = parameters.getRawParameterValue("gain");
    pan = parameters.getRawParameterValue("pan");
    })
{
}

UtilityAudioProcessor::~UtilityAudioProcessor()
{
}

//==============================================================================
const juce::String UtilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool UtilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool UtilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool UtilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double UtilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int UtilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int UtilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void UtilityAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String UtilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void UtilityAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void UtilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    spec.sampleRate = sampleRate;

    gainDSP.prepare(spec);
    pannerDSP.prepare(spec);
    muteDSP.prepare(spec);
}

void UtilityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool UtilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void UtilityAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    gainDSP.setGainDecibels(*gain);
    pannerDSP.setPan(*pan / 100);
    
    if (*mute == 0) {
        muteDSP.setGainLinear(1.0f);
    }
    else {
        muteDSP.setGainLinear(0.0f);
    }
    

    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    gainDSP.process(context);
    pannerDSP.process(context);
    muteDSP.process(context);
}

//==============================================================================
bool UtilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* UtilityAudioProcessor::createEditor()
{
    return new UtilityAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void UtilityAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void UtilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UtilityAudioProcessor();
}
