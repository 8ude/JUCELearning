/*
  ==============================================================================

    KAPDelay.cpp
    Created: 21 Jan 2022 12:24:38pm
    Author:  crber

  ==============================================================================
*/

#include "KAPDelay.h"

#include "JuceHeader.h"

#include "KAPAudioHelpers.h"

KAPDelay::KAPDelay() 
    : mSampleRate(-1),
    //this initializes the constructor with a sample rate of -1 (which will crash the plugin if it's not overridden before processing audio)
//the colon after the constructor allows you to initialize member variables in-line
    mBuffer{},
    mFeedbackSample(0.0),
    mTimeSmoothed(0),
    mDelayIndex(0)

{

}

KAPDelay::~KAPDelay()
{

}

void KAPDelay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPDelay::reset()
{
    mTimeSmoothed = 0.0f;
    zeromem(mBuffer, sizeof(double) * maxBufferSize);
}

void KAPDelay::process(float* inAudio, 
                       float inTime,                //delay time, in seconds 
                       float inFeedback, 
                       float inWetDry, 
                       float inType,
                       float* inModulationBuffer,   //buffer from the LFO module 
                       float* outAudio, 
                       int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - inWetDry;
    const float feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);

    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        if ((int)inType == kKAPDelayType_Delay)
        {
            //adjust the delay time gradually when it's changed by the user
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
        }
        else
        {
            //for now our modulation is a +/- sine wave LFO
            //the lfo is acting to modulate the delay time - give it a bit of warble. Both 0.003 and 0.002 are magic numbers 
            const double delayTimeModulation = (0.003 + (0.002 * inModulationBuffer[i]));
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
        }

        const double delayTimeInSamples = mSampleRate * mTimeSmoothed;

        const double sample = getInterpolatedSample(delayTimeInSamples);

        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);

        mFeedbackSample = sample;

        outAudio[i] = (inAudio[i] * dry + sample * wet);

        mDelayIndex = mDelayIndex + 1;

        if (mDelayIndex >= maxBufferSize)
        {
            mDelayIndex = mDelayIndex - maxBufferSize;
        }
    }

}

double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;

    if (readPosition < 0.0f)
    {
        readPosition = readPosition + maxBufferSize;
    }

    int index_y0 = (int)readPosition - 1;
    if (index_y0 < 0)
    {
        index_y0 = index_y0 + maxBufferSize;
    }
    int index_y1 = (int)readPosition; 

    if (index_y1 >= maxBufferSize)
    {
        index_y1 = index_y1 - maxBufferSize;
    }

    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;

    double outSample = kap_linear_interp(sample_y0, sample_y1, t);

    return outSample;

}
