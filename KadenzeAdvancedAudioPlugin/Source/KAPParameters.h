/*
  ==============================================================================

    KAPParameters.h
    Created: 28 Jan 2023 12:04:06am
    Author:  crber

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
    kParameter_InputGain = 0,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_DelayWetDry,
    kParameter_DelayType, //chorus or delay
    kParameter_OutputGain,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_TotalNumParameters
};

static String KAPParameterID[kParameter_TotalNumParameters] =
{
    "InputGain",
    "Time",
    "Feedback",
    "WetDry",
    "Type",
    "OutputGain",
    "ModulationRate",
    "ModulationDepth",
};
