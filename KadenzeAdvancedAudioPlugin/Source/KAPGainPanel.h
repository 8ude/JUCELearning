/*
  ==============================================================================

    KAPGainPanel.h
    Created: 31 Dec 2022 5:58:56pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"

class KAPGainPanel : public KAPPanelBase
{
public:
    KAPGainPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPGainPanel();

    void setParameterID(int inParameterID);

private:
    void paint(Graphics& g) override;

    ScopedPointer <KAPParameterSlider> mSlider;

};
