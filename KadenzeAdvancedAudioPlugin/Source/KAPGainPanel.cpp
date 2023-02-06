/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 31 Dec 2022 5:58:56pm
    Author:  crber

  ==============================================================================
*/

#include "KAPGainPanel.h"

#include "KAPParameters.h"

KAPGainPanel::KAPGainPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) : KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::setParameterID(int inParameterID)
{
    mSlider = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[inParameterID]);

    const int slider_size = 54;

    mSlider->setBounds(
        getWidth() * 0.5 - (slider_size * 0.5),
        getHeight() * 0.5 - (slider_size * 0.5),
        slider_size,
        slider_size);

    addAndMakeVisible(mSlider);
}


void KAPGainPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);

}