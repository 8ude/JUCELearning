/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 4 Feb 2023 5:14:04pm
    Author:  crber

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(AudioProcessorValueTreeState& stateToControl, const String& parameterID)
    : juce::Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);

    setRange(0.0f, 1.0f, 0.001f);
    mAttachment = new AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);

}

KAPParameterSlider::~KAPParameterSlider()
{

}
