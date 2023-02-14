/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 31 Dec 2022 5:58:37pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterComboBox.h"

class KAPCenterPanelMenuBar : public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanelMenuBar();

private:

    ScopedPointer<KAPParameterComboBox> mEffectsTypeComboBox;
};
