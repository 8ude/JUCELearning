/*
  ==============================================================================

    KAPLfo.cpp
    Created: 21 Jan 2022 12:24:16pm
    Author:  crber

  ==============================================================================
*/

#include "KAPLfo.h"
#include "JuceHeader.h"

KAPLfo::KAPLfo()
{
    reset();
}

KAPLfo::~KAPLfo()
{

}

void KAPLfo::reset()
{
    mPhase = 0.0f; 
    zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void KAPLfo::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPLfo::process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
    
    for (int i = 0; i < inNumSamples; i++)
    {
        mPhase = mPhase + (rate / mSampleRate);

        if (mPhase > 1.0f)
        {
            mPhase = mPhase - 1.0f;
        }

        const float lfoPosition = sin(mPhase * k2PI) * inDepth;

        mBuffer[i] = lfoPosition;

    }

    
}

float* KAPLfo::getBuffer()
{
    return mBuffer;
}
