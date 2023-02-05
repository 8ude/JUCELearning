/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 4 Feb 2023 5:14:04pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterSlider
    : public Slider
{
public:
    KAPParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
    ~KAPParameterSlider();

private:

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterSlider);
    //typically, C++ allows you to copy one constructor into another one. But this will flag the class so this isn't possible (I think... see session 2.7 min 3:30) I don't exactly know why this is an issue though?

};
