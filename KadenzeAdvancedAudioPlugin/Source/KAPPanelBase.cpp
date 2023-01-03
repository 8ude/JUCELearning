/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 31 Dec 2022 5:57:41pm
    Author:  crber

  ==============================================================================
*/

#include "KAPPanelBase.h"
KAPPanelBase::KAPPanelBase(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor): mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::paint(Graphics& g)
{
    //set fill first, then draw a rectangle above it
    g.setColour(Colours::whitesmoke);
    g.fillAll();

    g.setColour(Colours::black);
    g.drawRect(1, 1, getWidth() - 1, getHeight() - 1, 2);

}