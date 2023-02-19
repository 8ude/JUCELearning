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
#include "KAPEffectsPanel.h"

class KAPCenterPanelMenuBar : public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanelMenuBar();

    void addEffectsTypeComboBoxListener(KAPEffectsPanel* inListener);
    void removeEffectsTypeComboBoxListener(KAPEffectsPanel* inListener);

private:

    ScopedPointer<KAPParameterComboBox> mEffectsTypeComboBox;
};
