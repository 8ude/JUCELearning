/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KadenzeDelayAudioProcessor::KadenzeDelayAudioProcessor()
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
    addParameter(mDryWetParameter = new AudioParameterFloat(
        "drywet", 
        "Dry Wet", 
        0.01, 
        1.0, 
        0.5));

    addParameter(mFeedbackParameter = new AudioParameterFloat(
        "feedback",
        "Feedback",
        0,
        0.98,
        0.5));

    addParameter(mTimeParameter = new AudioParameterFloat(
        "delaytime",
        "Delay Time",
        0.01,
        MAX_DELAY_TIME,
        0.5));

    mTimeSmoothed = 0;

    mFeedbackLeft = 0;
    mFeedbackRight = 0;

    mDelayReadHead = 0;
    mDelayTimeInSamples = 0;

    mCircularBufferWriteHead = 0;
    mCircularBufferLength = 0;

    mCircularBufferLeft = nullptr;
    mCircularBufferRight = nullptr;
}

KadenzeDelayAudioProcessor::~KadenzeDelayAudioProcessor()
{
    if (mCircularBufferLeft != nullptr)
    {
        delete[] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }
    if (mCircularBufferRight != nullptr)
    {
        delete[] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }
}

//==============================================================================
const juce::String KadenzeDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzeDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KadenzeDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzeDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzeDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzeDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KadenzeDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void KadenzeDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KadenzeDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    mDelayTimeInSamples = sampleRate * *mTimeParameter;

    mTimeSmoothed = *mTimeParameter;

    mCircularBufferWriteHead = 0;
    mCircularBufferLength = MAX_DELAY_TIME * sampleRate;

    

    if (mCircularBufferLeft != nullptr)
    {
        delete[] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }

    if (mCircularBufferRight != nullptr)
    {
        delete[] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }

    if (mCircularBufferLeft == nullptr)
    {
        mCircularBufferLeft = new float[mCircularBufferLength];
    }

    zeromem(mCircularBufferLeft, mCircularBufferLength * sizeof(float));

    if (mCircularBufferRight == nullptr)
    {
        mCircularBufferRight = new float[mCircularBufferLength];
    }

    zeromem(mCircularBufferRight, mCircularBufferLength * sizeof(float));

    for (int i = 0; i < mCircularBufferLength; i++)
    {
        mCircularBufferLeft[i] = 0;
        mCircularBufferRight[i] = 0;
    }

}

void KadenzeDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzeDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void KadenzeDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); i++)
    {

        mTimeSmoothed = mTimeSmoothed - 0.0001 * (mTimeSmoothed - *mTimeParameter);

        mDelayTimeInSamples = getSampleRate() * mTimeSmoothed;

        mCircularBufferLeft[mCircularBufferWriteHead] = leftChannel[i] + mFeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = rightChannel[i] + mFeedbackRight;

        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;

        if (mDelayReadHead < 0)
        {
            mDelayReadHead += mCircularBufferLength;
        }

        int readHead_x = (int)mDelayReadHead;
        int readHead_x1 = readHead_x + 1;
        if (readHead_x1 >= mCircularBufferLength)
        {
            readHead_x1 -= mCircularBufferLength;
        }

        float readHeadFloat = mDelayReadHead - readHead_x;

        float delay_sample_Left = lin_interp( mCircularBufferLeft[readHead_x], mCircularBufferLeft[readHead_x1], readHeadFloat);
        float delay_sample_Right = lin_interp(mCircularBufferRight[readHead_x], mCircularBufferRight[readHead_x1], readHeadFloat);

        mFeedbackLeft = delay_sample_Left * *mFeedbackParameter;
        mFeedbackRight = delay_sample_Right * *mFeedbackParameter;


        buffer.setSample(
            0, 
            i, 
            buffer.getSample(0, i) * (1 - *mDryWetParameter) + delay_sample_Left * *mDryWetParameter);
        buffer.setSample(
            1, 
            i, 
            buffer.getSample(1, i) * (1 - *mDryWetParameter) + delay_sample_Right * *mDryWetParameter);

        mCircularBufferWriteHead++;

        if (mCircularBufferWriteHead >= mCircularBufferLength)
        {
            mCircularBufferWriteHead = 0;
        }

    }
    
}

//==============================================================================
bool KadenzeDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KadenzeDelayAudioProcessor::createEditor()
{
    return new KadenzeDelayAudioProcessorEditor (*this);
}

//==============================================================================
void KadenzeDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KadenzeDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

float KadenzeDelayAudioProcessor::lin_interp(float inSampleX, float inSampleY, float inPhase)
{
    return (1 - inPhase) * inSampleX + inPhase * inSampleY;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeDelayAudioProcessor();
}
