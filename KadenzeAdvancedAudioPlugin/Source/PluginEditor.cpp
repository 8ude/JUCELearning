/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "KAPLookAndFeel.h"

//==============================================================================
KadenzeAdvancedAudioPluginAudioProcessorEditor::KadenzeAdvancedAudioPluginAudioProcessorEditor (KadenzeAdvancedAudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

    mMainPanel = new KAPMainPanel(&audioProcessor);
    addAndMakeVisible(mMainPanel);
}

KadenzeAdvancedAudioPluginAudioProcessorEditor::~KadenzeAdvancedAudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void KadenzeAdvancedAudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KadenzeAdvancedAudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
