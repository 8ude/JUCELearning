/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"

#include "KAPParameterSlider.h"

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

    void paint(Graphics& g) override;

    void setFxPanelStyle(KAPFxPanelStyle inStyle);

private:

    KAPFxPanelStyle mStyle;

    OwnedArray<KAPParameterSlider> mSliders;

};