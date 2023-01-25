/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 31 Dec 2022 5:58:02pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

//both menu bar and Fx panel are going to be essentially children of the Center Panel
#include "KAPCenterPanelMenuBar.h"
#include "KAPEffectsPanel.h"

class KAPCenterPanel : public KAPPanelBase
{
public:
    KAPCenterPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanel();

private:
    ScopedPointer<KAPCenterPanelMenuBar> mMenuBar;
    ScopedPointer<KAPEffectsPanel> mEffectsPanel;
    void paint(Graphics& g) override;
};
