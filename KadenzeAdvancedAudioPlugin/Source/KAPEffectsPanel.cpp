/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 31 Dec 2022 5:58:48pm
    Author:  crber

  ==============================================================================
*/

#include "KAPEffectsPanel.h"
#include "KAPParameters.h"

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
    mSliders.clear();

    const int slider_size = 56;
    int x = 130;
    int y = (getHeight() * 0.5) - (slider_size * 0.5);

    switch (mStyle)
    {
    case(kKAPFxPanelStyle_Delay): {

        //ADD TIME PARAMETER
        KAPParameterSlider* time = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayTime]);
        time->setBounds(x, y, slider_size, slider_size);

        addAndMakeVisible(time);

        mSliders.add(time);
        
        x = x + (slider_size * 2);

        //ADD FEEDBACK PARAMETER
        KAPParameterSlider* feedback = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayFeedback]);
        feedback->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(feedback);
        mSliders.add(feedback);

        x = x + (slider_size * 2);

        //ADD WET DRY PARAMETER
        KAPParameterSlider* wetdry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(wetdry);
        mSliders.add(wetdry);

    } break;
    case (kKAPFxPanelStyle_Chorus): {

    } break;
    case (kKAPFxPanelStyle_TotalNumStyles): {
        //THIS IS BAD

        jassertfalse;
    } break;
    }
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