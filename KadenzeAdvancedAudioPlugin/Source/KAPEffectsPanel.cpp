/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#include "KAPEffectsPanel.h"

KAPEffectsPanel::KAPEffectsPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) :         
    KAPPanelBase(inProcessor),
    mStyle(kKAPFxPanelStyle_Delay)
{
    setSize(EFFECTS_PANEL_WIDTH, EFFECTS_PANEL_HEIGHT);
}

KAPEffectsPanel::~KAPEffectsPanel()
{

}

void KAPEffectsPanel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
    mStyle = inStyle;
}

void KAPEffectsPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);

    switch (mStyle)
    {
        case(kKAPFxPanelStyle_Delay): {
            g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
        } break;
        case (kKAPFxPanelStyle_Chorus): {
            g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
        } break;
        case (kKAPFxPanelStyle_TotalNumStyles): {
            //THIS IS BAD
            g.drawFittedText("OH NO OH NO", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
            jassertfalse;
        } break;
    }
}