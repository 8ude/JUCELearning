/*
  ==============================================================================

    KAPMainPanel.cpp
    Created: 31 Dec 2022 5:57:54pm
    Author:  crber

  ==============================================================================
*/

#include "KAPMainPanel.h"

KAPMainPanel::KAPMainPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor): KAPPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
}
KAPMainPanel::~KAPMainPanel()
{

}
