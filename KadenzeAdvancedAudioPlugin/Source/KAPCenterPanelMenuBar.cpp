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
    //need to make sure to distinguish between the Item ID and the Item index
    mEffectsTypeComboBox->addItem("DELAY", 1);
    mEffectsTypeComboBox->addItem("CHORUS", 2);
    mEffectsTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType), dontSendNotification);
    addAndMakeVisible(mEffectsTypeComboBox);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

void KAPCenterPanelMenuBar::addEffectsTypeComboBoxListener(KAPEffectsPanel* inListener)
{
    mEffectsTypeComboBox->addListener(inListener);
}
void KAPCenterPanelMenuBar::removeEffectsTypeComboBoxListener(KAPEffectsPanel* inListener)
{
    mEffectsTypeComboBox->removeListener(inListener);
}

