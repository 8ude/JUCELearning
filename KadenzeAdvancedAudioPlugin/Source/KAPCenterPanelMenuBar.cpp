/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 31 Dec 2022 5:58:37pm
    Author:  crber

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"



KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

void KAPCenterPanelMenuBar::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
}