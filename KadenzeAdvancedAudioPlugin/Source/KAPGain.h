/*
  ==============================================================================

    KAPGain.h
    Created: 21 Jan 2022 12:24:25pm
    Author:  crber

  ==============================================================================
*/

#pragma once
class KAPGain
{
public:
    KAPGain();
    ~KAPGain();

    void process(float* inAudio,
                float inGain,
                float* outAudio,
                int inNumSamplesToRender);

private:

};