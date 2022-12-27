/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "KAPGain.h"
#include "KAPDelay.h"
#include "KAPLfo.h"

//==============================================================================
/**
*/
class KadenzeAdvancedAudioPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KadenzeAdvancedAudioPluginAudioProcessor();
    ~KadenzeAdvancedAudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
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
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    /** interanal **/
    
    void initializeDSP();

    //this doesn't seem to be working?
    //ScopedPointer<KAPGain> mGain[2]

    std::unique_ptr<KAPGain> mGain[2];
    std::unique_ptr<KAPDelay> mDelay[2];
    std::unique_ptr<KAPLfo> mLFO[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KadenzeAdvancedAudioPluginAudioProcessor)
};
