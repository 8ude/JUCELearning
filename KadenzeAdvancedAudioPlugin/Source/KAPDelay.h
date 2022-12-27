/*
  ==============================================================================

    KAPDelay.h
    Created: 21 Jan 2022 12:24:38pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include "KAPAudioHelpers.h"

class KAPDelay
{
public:
    KAPDelay();
    ~KAPDelay();

    void setSampleRate(double inSampleRate);

    void reset();
    void process(
        float* inAudio, 
        float inTime, 
        float inFeedback, 
        float inWetDry, 
        float* inModulationBuffer,
        float* outAudio, 
        int inNumSamplesToRender);

private:

    double getInterpolatedSample(float inDelayTimeInSamples);

    double mSampleRate;
    double mBuffer[maxBufferSize];
    double mFeedbackSample;
    
    float mTimeSmoothed;

    int mDelayIndex;

};
