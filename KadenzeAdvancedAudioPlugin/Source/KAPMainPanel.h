/*
  ==============================================================================

    KAPMainPanel.h
    Created: 31 Dec 2022 5:57:54pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPTopPanel.h"

#include "KAPGainPanel.h"

#include "KAPCenterPanelMenuBar.h"

#include "KAPCenterPanel.h"

class KAPMainPanel : public KAPPanelBase
{
public:
    KAPMainPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPMainPanel();
private:

    ScopedPointer<KAPTopPanel> mTopPanel;
    ScopedPointer<KAPGainPanel> mOutputGainPanel;
    ScopedPointer<KAPGainPanel> mInputGainPanel;
    ScopedPointer<KAPCenterPanelMenuBar> mCenterPanelMenuBar;
    ScopedPointer<KAPCenterPanel> mCenterPanel;
};