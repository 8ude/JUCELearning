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

enum KAPEffectsPanelStyle
{
    kKAPFxPanelStyle_Delay,
    kKAPFxPanelStyle_Chorus,
    kKAPFxPanelStyle_TotalNumStyles
};

class KAPEffectsPanel : 
    public KAPPanelBase,
    public ComboBox::Listener
{
public:
    KAPEffectsPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPEffectsPanel();

    void paint(Graphics& g) override;

    void setFxPanelStyle(KAPEffectsPanelStyle inStyle);

    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

    KAPEffectsPanelStyle mStyle;

    OwnedArray<KAPParameterSlider> mSliders;

};