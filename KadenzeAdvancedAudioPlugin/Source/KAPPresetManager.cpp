/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 1 Mar 2023 11:06:01pm
    Author:  crber

  ==============================================================================
*/

#include "KAPPresetManager.h"
KAPPresetManager::KAPPresetManager(AudioProcessor* inProcessor)
    : mProcessor(inProcessor)
{

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

void KAPPresetManager::loadXmlForPreset(XmlElement* inElement)
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