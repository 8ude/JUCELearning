/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 31 Dec 2022 5:58:02pm
    Author:  crber

  ==============================================================================
*/

#include "KAPCenterPanel.h"

KAPCenterPanel::KAPCenterPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);

    mMenuBar = new KAPCenterPanelMenuBar(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar);

    mEffectsPanel = new KAPEffectsPanel(inProcessor);
    mEffectsPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mEffectsPanel);
}

KAPCenterPanel::~KAPCenterPanel()
{

}

void KAPCenterPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
}