/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"

enum KAPFxPanelStyle
{
    kKAPFxPanelStyle_Delay,
    kKAPFxPanelStyle_Chorus,
    kKAPFxPanelStyle_TotalNumStyles
};

class KAPEffectsPanel : public KAPPanelBase
{
public:
    KAPEffectsPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPEffectsPanel();

    void setFxPanelStyle(KAPFxPanelStyle inStyle);

private:

    KAPFxPanelStyle mStyle;

    void paint(Graphics& g) override;
};