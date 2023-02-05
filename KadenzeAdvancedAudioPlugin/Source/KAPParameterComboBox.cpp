/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 4 Feb 2023 5:14:22pm
    Author:  crber

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID)
    : juce::ComboBox(parameterID)
{
    mAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);

}
KAPParameterComboBox::~KAPParameterComboBox()
{

}

