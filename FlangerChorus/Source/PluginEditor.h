/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KadenzeChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KadenzeChorusAudioProcessorEditor (KadenzeChorusAudioProcessor&);
    ~KadenzeChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KadenzeChorusAudioProcessor& audioProcessor;

    Slider mDryWetSlider;
    Slider mDepthSlider;
    Slider mRateSlider;
    Slider mPhaseOffsetSlider;
    Slider mFeedbackSlider;

    ComboBox mType;

    //slider mLFORate

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KadenzeChorusAudioProcessorEditor)
};
