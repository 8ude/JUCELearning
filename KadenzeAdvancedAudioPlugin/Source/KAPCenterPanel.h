/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 31 Dec 2022 5:58:02pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPCenterPanel : public KAPPanelBase
{
public:
    KAPCenterPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanel();

private:
    void paint(Graphics& g) override;
};
