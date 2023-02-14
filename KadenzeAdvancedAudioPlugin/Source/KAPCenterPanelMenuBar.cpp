/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 31 Dec 2022 5:58:37pm
    Author:  crber

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"



KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

    const int width = 85;

    mEffectsTypeComboBox = new KAPParameterComboBox(mProcessor->parameters, KAPParameterID[kParameter_DelayType]);

    mEffectsTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    
    addAndMakeVisible(mEffectsTypeComboBox);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

