/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 4 Feb 2023 5:14:22pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterComboBox
    : public ComboBox
{
public:

    KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
    ~KAPParameterComboBox();

private:

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox);

};