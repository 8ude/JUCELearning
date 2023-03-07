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
}

void KAPPresetManager::loadXmlForPreset(XmlElement* inElement)
{

}