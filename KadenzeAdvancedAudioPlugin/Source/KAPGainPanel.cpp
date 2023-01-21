/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 31 Dec 2022 5:58:56pm
    Author:  crber

  ==============================================================================
*/

#include "KAPGainPanel.h"

KAPGainPanel::KAPGainPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);

}