/*
  ==============================================================================

    KAPPanelBase.h
    Created: 31 Dec 2022 5:57:41pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "PluginProcessor.h"

#include "KAPInterfaceDefines.h"

class KAPPanelBase : public Component
{
public:

    KAPPanelBase(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPPanelBase();

    void paint(Graphics& g) override;

protected:

    KadenzeAdvancedAudioPluginAudioProcessor* mProcessor;

};
