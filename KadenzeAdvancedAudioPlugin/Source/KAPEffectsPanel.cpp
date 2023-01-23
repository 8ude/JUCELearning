/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#include "KAPEffectsPanel.h"

KAPEffectsPanel::KAPEffectsPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(EFFECTS_PANEL_WIDTH, EFFECTS_PANEL_HEIGHT);
}

KAPEffectsPanel::~KAPEffectsPanel()
{

}

void KAPEffectsPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
}