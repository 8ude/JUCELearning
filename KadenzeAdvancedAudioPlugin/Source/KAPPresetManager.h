/*
  ==============================================================================

    KAPPresetManager.h
    Created: 1 Mar 2023 11:06:01pm
    Author:  crber

  ==============================================================================
*/

#pragma once
#include  "JuceHeader.h"

#define PRESET_FILE_EXTENTION ".kpf"

class KAPPresetManager
{
public:
    //using generic JUCE audio processor instead of our custom plugin processor
    //we want all our processor interaction to handled on the generic level
    KAPPresetManager(AudioProcessor* inProcessor);
    ~KAPPresetManager();

    void getXmlForPreset(XmlElement* inElement);

    void loadPresetForXml(XmlElement* inElement);

    int getNumberOfPresets();

    String getPresetName(int inPresetIndex);

    void createNewPreset();

    void savePreset();

    void saveAsPreset(String inPresetName);

    void loadPreset(int inPresetIndex);

    bool getIsCurrentPresetSaved();

    String getCurrentPresetName();

private:

    void storeLocalPreset();

    bool mCurrentPresetIsSaved;

    File mCurrentlyLoadedPreset;

    Array<File> mLocalPresets;

    String mCurrentPresetName;

    String mPresetDirectory;

    XmlElement* mCurrentPresetXml;
    AudioProcessor* mProcessor;
    
};