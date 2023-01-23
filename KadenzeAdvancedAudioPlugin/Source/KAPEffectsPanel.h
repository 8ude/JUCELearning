/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"

class KAPEffectsPanel : public KAPPanelBase
{
public:
    KAPEffectsPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPEffectsPanel();
private:
    void paint(Graphics& g) override;
};