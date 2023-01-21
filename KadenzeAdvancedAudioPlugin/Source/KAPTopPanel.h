/*
  ==============================================================================

    KAPTopPanel.h
    Created: 31 Dec 2022 5:59:36pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel: public KAPPanelBase
{
public:

    KAPTopPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();

    void paint(Graphics& g) override;

private:

};