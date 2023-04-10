/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 1 Mar 2023 11:06:01pm
    Author:  crber

  ==============================================================================
*/

#include "KAPPresetManager.h"

#if JUCE_WINDOWS
    static const String directorySeparator = "\\";
#elif JUCE_MAC
    static const String directorySeparator = "/";
#endif

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

    storeLocalPreset();
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
    return mLocalPresets.size();
}

String KAPPresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void KAPPresetManager::createNewPreset()
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }

    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

//does this work if user accidentally clicks "Save" instead of "Save As"?
void KAPPresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    mCurrentlyLoadedPreset.deleteFile();

    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                       destinationData.getSize());

    mCurrentPresetIsSaved = true;
}

void KAPPresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + directorySeparator + inPresetName + PRESET_FILE_EXTENTION);

    if (!presetFile.exists())
    {
        presetFile.create();
    }
    else
    {
        presetFile.deleteFile();
    }

    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    presetFile.appendData(destinationData.getData(),
        destinationData.getSize());

    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;

    storeLocalPreset();
}

void KAPPresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];

    MemoryBlock presetBinary;

    if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary))
    {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(), 
                                        presetBinary.getSize());
    }
}

bool KAPPresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

String KAPPresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void KAPPresetManager::storeLocalPreset()
{
    mLocalPresets.clear();

    for (DirectoryIterator di(File(mPresetDirectory),
        false,
        '*' + (String)PRESET_FILE_EXTENTION,
        File::TypesOfFileToFind::findFiles); di.next();)
    {
        File preset = di.getFile();
        mLocalPresets.add(preset);
    }
}