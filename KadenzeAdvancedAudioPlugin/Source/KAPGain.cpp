/*
  ==============================================================================

    KAPGain.cpp
    Created: 21 Jan 2022 12:24:25pm
    Author:  crber

  ==============================================================================
*/

#include "KAPGain.h"
#include "JuceHeader.h"
KAPGain::KAPGain()
{

}

KAPGain::~KAPGain()
{

}

void KAPGain::process(float* inAudio,
    float inGain,
    float* outAudio,
    int inNumSamplesToRender)
{
    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);

        gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);

        outAudio[i] = inAudio[i] * gainMapped;
    }
}