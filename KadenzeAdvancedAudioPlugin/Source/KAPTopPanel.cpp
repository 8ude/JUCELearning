/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 31 Dec 2022 5:59:36pm
    Author:  crber

  ==============================================================================
*/

#include "KAPTopPanel.h"


KAPTopPanel::KAPTopPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) 
    :   KAPPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);

}
KAPTopPanel::~KAPTopPanel()
{

}

void KAPTopPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    g.drawFittedText("KADENZE AUDIO PLUGIN", 0, 0, getWidth()-10, getHeight(), Justification::centredRight, 1);
}