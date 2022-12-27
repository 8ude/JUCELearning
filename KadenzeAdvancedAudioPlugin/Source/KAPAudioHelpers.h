/*
  ==============================================================================

    KAPAudioHelpers.h
    Created: 4 Jan 2022 11:17:11pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002

const static int maxBufferSize = 192000;
const static double kPI = 3.14159265359;
const static double k2PI = 6.28318530718;
/// <summary>
/// interpolates between two values
/// </summary>
/// <param name="v0">our start value</param>
/// <param name="v1">end value</param>
/// <param name="t">amount to interpolate (0.0- 1.0)</param>
/// <returns></returns>
inline float kap_linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}