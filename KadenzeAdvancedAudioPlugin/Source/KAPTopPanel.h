/*
  ==============================================================================

    KAPTopPanel.h
    Created: 31 Dec 2022 5:59:36pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel
:   public KAPPanelBase,
    public Button::Listener,
    public ComboBox::Listener
{
public:

    KAPTopPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();

    void paint(Graphics& g) override;

    void buttonClicked(Button* b) override;

    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

    void displaySaveAsPopup();

    void updatePresetComboBox();

    ScopedPointer<ComboBox> mPresetDisplay;

    ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;

};