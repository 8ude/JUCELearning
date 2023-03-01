/*
  ==============================================================================

    KAPPresetManager.h
    Created: 1 Mar 2023 11:06:01pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include  "JuceHeader.h"

class KAPPresetManager
{
    //using generic JUCE audio processor instead of our custom plugin processor
    //we want all our processor interaction to handled on the generic level
    KAPPresetManager(AudioProcessor* inProcessor);
};