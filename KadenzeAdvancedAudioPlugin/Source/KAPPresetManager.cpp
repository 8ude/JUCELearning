/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 1 Mar 2023 11:06:01pm
    Author:  crber

  ==============================================================================
*/

#include "KAPPresetManager.h"
KAPPresetManager::KAPPresetManager(AudioProcessor* inProcessor)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcessor)
{
    const String pluginName = (String)mProcessor->getName();

    mPresetDirectory = (File::getSpecialLocation(File::userDesktopDirectory)).getFullPathName() + pluginName;

    if (!File(mPresetDirectory).exists())
    {
        File(mPresetDirectory).createDirectory();
    }
}
KAPPresetManager::~KAPPresetManager()
{

}

void KAPPresetManager::getXmlForPreset(XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        inElement->setAttribute(mProcessor->getParameterName(i), 
                                mProcessor->getParameter(i));
    }
}

void KAPPresetManager::loadPresetForXml(XmlElement* inElement)
{
    mCurrentPresetXml = inElement;

    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        const String name = mCurrentPresetXml->getAttributeName(i);

        const float value = mCurrentPresetXml->getDoubleAttribute(name);

        for (int j = 0; j < mProcessor->getNumParameters(); j++)
        {
            if (mProcessor->getParameterName(j) == name)
            {
                mProcessor->setParameterNotifyingHost(j, value);
            }
        }
    }
}

int KAPPresetManager::getNumberOfPresets()
{
    return 0;
}

String KAPPresetManager::getPresetName(int inPresetIndex)
{
    return "none";
}

void KAPPresetManager::createNewPreset()
{

}

void KAPPresetManager::savePreset()
{

}

void KAPPresetManager::saveAsPreset(String inPresetName)
{

}

void KAPPresetManager::loadPreset(int inPresetIndex)
{

}

bool KAPPresetManager::getIsCurrentPresetSaved()
{
    return 0;
}

String KAPPresetManager::getCurrentPresetName()
{
    return "none";
}

void KAPPresetManager::storeLocalPreset()
{

}