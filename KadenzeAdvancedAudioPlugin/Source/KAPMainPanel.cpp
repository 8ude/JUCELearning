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
    
    mTopPanel = new KAPTopPanel(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel);

    mInputGainPanel = new KAPGainPanel(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mInputGainPanel);

    mOutputGainPanel = new KAPGainPanel(inProcessor);
    mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mOutputGainPanel);

    mCenterPanelMenuBar = new KAPCenterPanelMenuBar(inProcessor);
    mCenterPanelMenuBar->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanelMenuBar);


    mCenterPanel = new KAPCenterPanel(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel);
}
KAPMainPanel::~KAPMainPanel()
{

}
