/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KadenzeChorusAudioProcessor::KadenzeChorusAudioProcessor()
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

    /* Construct and Add Parameters */
    addParameter(mDryWetParameter = new AudioParameterFloat(
        "drywet",
        "Dry Wet",
        0.01,
        1.0,
        0.5));

    addParameter(mDepthParameter = new AudioParameterFloat(
        "depth",
        "Depth",
        0.0,
        1.0,
        0.5));
    

    //rate range is in Hz, and corresponds to the rate of the LFO modulating the delay line
    addParameter(mRateParameter = new AudioParameterFloat(
        "rate",
        "Rate",
        0.1f,
        20.f,
        10.f));

    addParameter(mPhaseOffsetParameter = new AudioParameterFloat(
        "phaseoffset",
        "Phase Offset",
        0.0f,
        1.0f,
        0.f));

    addParameter(mFeedbackParameter = new AudioParameterFloat(
        "feedback",
        "Feedback",
        0.0f,
        0.98f,
        0.5f));

    addParameter(mTypeParameter = new AudioParameterInt(
        "type",
        "Type",
        0,
        1,
        0));

    /* Init Data to Default Values */
    mFeedbackLeft = 0;
    mFeedbackRight = 0;

    mCircularBufferWriteHead = 0;
    mCircularBufferLength = 0;

    mCircularBufferLeft = nullptr;
    mCircularBufferRight = nullptr;

    mLFOPhase = 0;

}

KadenzeChorusAudioProcessor::~KadenzeChorusAudioProcessor()
{    
}

//==============================================================================
const juce::String KadenzeChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzeChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KadenzeChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzeChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzeChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzeChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KadenzeChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void KadenzeChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KadenzeChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..


    mLFOPhase = 0;
    
    mCircularBufferLength = MAX_DELAY_TIME * sampleRate;

    
    if (mCircularBufferLeft != nullptr)
    {
        delete[] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }

    if (mCircularBufferLeft == nullptr)
    {
        mCircularBufferLeft = new float[mCircularBufferLength];
    }

    zeromem(mCircularBufferLeft, mCircularBufferLength * sizeof(float));

    if (mCircularBufferRight != nullptr)
    {
        delete[] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }

    if (mCircularBufferRight == nullptr)
    {
        mCircularBufferRight = new float[mCircularBufferLength];
    }

    zeromem(mCircularBufferRight, mCircularBufferLength * sizeof(float));

    mCircularBufferWriteHead = 0;


}

void KadenzeChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzeChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void KadenzeChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
        buffer.clear(i, 0, buffer.getNumSamples());

    /* obtain left and right audio data pointers */
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    //flanger is going to be a small delay, between 1-20 ms 

    /* iterate through samples in buffer */
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        /* write into circular buffer */
        mCircularBufferLeft[mCircularBufferWriteHead] = leftChannel[i] + mFeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = rightChannel[i] + mFeedbackRight;

        /* generate left LFO Output */
        float lfoOutLeft = sin(2 * M_PI * mLFOPhase);

        /* calculate right LFO phase */
        float lfoPhaseRight = mLFOPhase + *mPhaseOffsetParameter;

        if (lfoPhaseRight > 1)
        {
            lfoPhaseRight -= 1;
        }

        /* generate right LFO output */
        float lfoOutRight = sin(2 * M_PI * lfoPhaseRight);

        mLFOPhase += *mRateParameter / getSampleRate();

        if (mLFOPhase > 1)
        {
            mLFOPhase -= 1;
        }

        /* control lfo depth */
        lfoOutLeft *= *mDepthParameter;
        lfoOutRight *= *mDepthParameter;

        float lfoOutMappedLeft = 0;
        float lfoOutMappedRight = 0;

        /* map lfo output to desired delay times */
        
        //chorus
        if (*mTypeParameter == 0)
        {
            lfoOutMappedLeft = jmap(lfoOutLeft, -1.0f, 1.0f, 0.005f, 0.03f);
            lfoOutMappedRight = jmap(lfoOutRight, -1.0f, 1.0f, 0.005f, 0.03f);
        }
        //flanger
        else
        {
            lfoOutMappedLeft = jmap(lfoOutLeft, -1.0f, 1.0f, 0.001f, 0.005f);
            lfoOutMappedRight = jmap(lfoOutRight, -1.0f, 1.0f, 0.001f, 0.005f);
        }

        /* calculate delay lengths in samples */
        float delayTimeSamplesLeft = getSampleRate() * lfoOutMappedLeft;
        float delayTimeSamplesRight = getSampleRate() * lfoOutMappedRight;

        
        /* calculate the left read head position */
        float delayReadHeadLeft = mCircularBufferWriteHead - delayTimeSamplesLeft;
        

        if (delayReadHeadLeft < 0)
        {
            delayReadHeadLeft += mCircularBufferLength;
        }

        /* calculate the right read head position */
        float delayReadHeadRight = mCircularBufferWriteHead - delayTimeSamplesRight;

        if (delayReadHeadRight < 0)
        {
            delayReadHeadRight += mCircularBufferLength;
        }

        //calculate linear interpolation points for left channel
        int readHeadLeft_x = (int)delayReadHeadLeft;
        
        int readHeadLeft_x1 = readHeadLeft_x + 1;
        float readHeadFloatLeft = delayReadHeadLeft - readHeadLeft_x;
        if (readHeadLeft_x1 >= mCircularBufferLength)
        {
            readHeadLeft_x1 -= mCircularBufferLength;
        }


        //calculate linear interpolation  points for right channel
        int readHeadRight_x = (int)delayReadHeadRight;
        int readHeadRight_x1 = readHeadRight_x + 1;
        float readHeadFloatRight = delayReadHeadRight - readHeadRight_x;
        if (readHeadRight_x1 >= mCircularBufferLength)
        {
            readHeadRight_x1 -= mCircularBufferLength;
        }
        
        /* generate left and right output samples */
        float delay_sample_Left = lin_interp(mCircularBufferLeft[readHeadLeft_x], mCircularBufferLeft[readHeadLeft_x1], readHeadFloatLeft);
        float delay_sample_Right = lin_interp(mCircularBufferRight[readHeadRight_x], mCircularBufferRight[readHeadRight_x1], readHeadFloatRight);

        /* store output samples for feedback*/
        mFeedbackLeft = delay_sample_Left * *mFeedbackParameter;
        mFeedbackRight = delay_sample_Right * *mFeedbackParameter;


        

        mCircularBufferWriteHead++;

        if (mCircularBufferWriteHead >= mCircularBufferLength)
        {
            mCircularBufferWriteHead = 0;
        }

        float dryAmount = 1 - *mDryWetParameter;
        float wetAmount = *mDryWetParameter;

        buffer.setSample(
            0,
            i,
            buffer.getSample(0, i) * dryAmount + delay_sample_Left * wetAmount);
        buffer.setSample(
            1,
            i,
            buffer.getSample(1, i) * dryAmount + delay_sample_Right * wetAmount);

    }
}

//==============================================================================
bool KadenzeChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KadenzeChorusAudioProcessor::createEditor()
{
    return new KadenzeChorusAudioProcessorEditor (*this);
}

//==============================================================================
void KadenzeChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(new XmlElement("FlangerChorus"));

    xml->setAttribute("DryWet", *mDryWetParameter);
    xml->setAttribute("Depth", *mDepthParameter);
    xml->setAttribute("Rate", *mRateParameter);
    xml->setAttribute("PhaseOffset", *mPhaseOffsetParameter);
    xml->setAttribute("Feedback", *mFeedbackParameter);
    xml->setAttribute("Type", *mTypeParameter);

    DBG("XML set, first attribute: ");
    DBG(xml->getAttributeName(0));

    copyXmlToBinary(*xml, destData);

    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KadenzeChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

    if (xml.get() != nullptr && xml->hasTagName("FlangerChorus"))
    {
        DBG("XML get");
        *mDryWetParameter = xml->getDoubleAttribute("DryWet");
        *mDepthParameter = xml->getDoubleAttribute("Depth");
        *mRateParameter = xml->getDoubleAttribute("Rate");
        *mPhaseOffsetParameter = xml->getDoubleAttribute("PhaseOffset");
        *mFeedbackParameter = xml->getDoubleAttribute("Feedback");

        *mTypeParameter = xml->getIntAttribute("Type");

        DBG("DryWet Retrieved: ");
        DBG(*mDryWetParameter);
    }
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

float KadenzeChorusAudioProcessor::lin_interp(float sample_x, float sample_x1, float inPhase)
{
    return ((1 - inPhase) * sample_x) + (inPhase * sample_x1);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeChorusAudioProcessor();
}
