/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 31 Dec 2022 5:59:36pm
    Author:  crber

  ==============================================================================
*/

#include "KAPTopPanel.h"
#define JUCE_MODAL_LOOPS_PERMITTED = 1


KAPTopPanel::KAPTopPanel(KadenzeAdvancedAudioPluginAudioProcessor* inProcessor) 
    :   KAPPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);

    int button_x = 15;
    int button_y = 10;
    int button_w = 55;
    int button_h = 25;


    //init preset UI
    mNewPreset = new TextButton();
    mNewPreset->setButtonText("NEW");
    mNewPreset->setBounds(button_x, button_y, button_w, button_h);
    mNewPreset->addListener(this);
    addAndMakeVisible(mNewPreset);
    button_x = button_x + button_w;
    
    mSavePreset = new TextButton();
    mSavePreset->setButtonText("SAVE");
    mSavePreset->setBounds(button_x, button_y, button_w, button_h);
    mSavePreset->addListener(this);
    addAndMakeVisible(mSavePreset);
    button_x = button_x + button_w;

    mSaveAsPreset = new TextButton();
    mSaveAsPreset->setButtonText("SAVE AS");
    mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
    mSaveAsPreset->addListener(this);
    addAndMakeVisible(mSaveAsPreset);
    button_x = button_x + button_w;

    const int comboBox_w = 200;
    const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;

    mPresetDisplay = new ComboBox();
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(mPresetDisplay);

    updatePresetComboBox();
}
KAPTopPanel::~KAPTopPanel()
{

}

//inhereted from juce Button::Listener
void KAPTopPanel::buttonClicked(Button* b)
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();

    if (b == mNewPreset)
    {
        presetManager->createNewPreset();
    }
    else if (b == mSavePreset)
    {
        presetManager->savePreset();
    }

    else if (b == mSaveAsPreset)
    {
        displaySaveAsPopup();
    }
}

//inhereted from ComboBox::Listener
void KAPTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == mPresetDisplay)
    {
        KAPPresetManager* presetManager = mProcessor->getPresetManager();

        const int index = mPresetDisplay->getSelectedItemIndex();
        presetManager->loadPreset(index);
    }
}

void KAPTopPanel::displaySaveAsPopup()
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();

    String currentPresetName = presetManager->getCurrentPresetName();

    AlertWindow window("Save As", "Please enter a name for your Preset", AlertWindow::NoIcon);
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("presetName", currentPresetName, "preset name: ");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);

    //deprecated function - unsure why exactly.
    //I guess it keeps the window open until it returns a 1 or 0
    if (window.runModalLoop())
    {
        String presetName = window.getTextEditor("presetName")->getText();
        presetManager->saveAsPreset(presetName);

        updatePresetComboBox();
    }

}

void KAPTopPanel::updatePresetComboBox()
{
    KAPPresetManager* presetManager = mProcessor->getPresetManager();
    String presetName = presetManager->getCurrentPresetName();

    mPresetDisplay->clear(dontSendNotification);

    const int numPresets = presetManager->getNumberOfPresets();

    for (int i = 0; i < numPresets; i++)
    {
        mPresetDisplay->addItem(presetManager->getPresetName(i), i + 1); //combo box id's cannot be 0
    }

    mPresetDisplay->setText(presetManager->getCurrentPresetName());
}

void KAPTopPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    g.drawFittedText("KADENZE AUDIO PLUGIN", 0, 0, getWidth()-10, getHeight(), Justification::centredRight, 1);
}