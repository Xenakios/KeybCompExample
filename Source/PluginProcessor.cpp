/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KeyboardComponentExampleAudioProcessor::KeyboardComponentExampleAudioProcessor()
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
{
}

KeyboardComponentExampleAudioProcessor::~KeyboardComponentExampleAudioProcessor()
{
}

//==============================================================================
const juce::String KeyboardComponentExampleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KeyboardComponentExampleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KeyboardComponentExampleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KeyboardComponentExampleAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KeyboardComponentExampleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KeyboardComponentExampleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KeyboardComponentExampleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KeyboardComponentExampleAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KeyboardComponentExampleAudioProcessor::getProgramName (int index)
{
    return {};
}

void KeyboardComponentExampleAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KeyboardComponentExampleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

void KeyboardComponentExampleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KeyboardComponentExampleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void KeyboardComponentExampleAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // note that in order to be able to play the synth with the GUI keyboard,
    // this call needs to be done first!
    mKeyState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    // then, you can do your
    // mSynth.renderNextBlock stuff
}

//==============================================================================
bool KeyboardComponentExampleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KeyboardComponentExampleAudioProcessor::createEditor()
{
    return new KeyboardComponentExampleAudioProcessorEditor (*this);
}

//==============================================================================
void KeyboardComponentExampleAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KeyboardComponentExampleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KeyboardComponentExampleAudioProcessor();
}
