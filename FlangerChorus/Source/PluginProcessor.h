/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define MAX_DELAY_TIME 2
#define M_PI MathConstants<float>::pi

//==============================================================================
/**
*/
class KadenzeChorusAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KadenzeChorusAudioProcessor();
    ~KadenzeChorusAudioProcessor() override;

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

    //========== Bespoke methods ===========================================
    float lin_interp(float sample_x, float sample_x1, float inPhase);

private:

    /* User Parameters */
    AudioParameterFloat* mDryWetParameter;
    AudioParameterFloat* mDepthParameter;
    AudioParameterFloat* mRateParameter;
    AudioParameterFloat* mPhaseOffsetParameter;
    AudioParameterFloat* mFeedbackParameter;

    AudioParameterInt* mTypeParameter;

    /* Circular Buffer Data */
    int mCircularBufferLength;
    int mCircularBufferWriteHead;

    float* mCircularBufferLeft;
    float* mCircularBufferRight;

    float mFeedbackLeft;
    float mFeedbackRight;

    /* LFO Data */
    float mLFOPhase;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KadenzeChorusAudioProcessor)
};
