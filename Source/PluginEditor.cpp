/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KeyboardComponentExampleAudioProcessorEditor::KeyboardComponentExampleAudioProcessorEditor (KeyboardComponentExampleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    mKeyComponent(p.getKeyboardState(),juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(mKeyComponent);
    setSize (400, 300);
}

KeyboardComponentExampleAudioProcessorEditor::~KeyboardComponentExampleAudioProcessorEditor()
{
}

//==============================================================================
void KeyboardComponentExampleAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KeyboardComponentExampleAudioProcessorEditor::resized()
{
    mKeyComponent.setBounds(0, getHeight()-50, getWidth(), 50);
}
