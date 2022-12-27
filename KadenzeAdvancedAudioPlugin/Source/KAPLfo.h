/*
  ==============================================================================

    KAPLfo.h
    Created: 21 Jan 2022 12:24:16pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

class KAPLfo
{
public:
    KAPLfo();
    ~KAPLfo();


    void reset();

    void setSampleRate(double inSampleRate);

    void process(float inRate, float inDepth, int inNumSamples);

    float* getBuffer();

private:

    double mSampleRate;

    float mPhase;

    float mBuffer[maxBufferSize];

};
