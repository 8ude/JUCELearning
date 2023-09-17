/*
  ==============================================================================

    KAPLookAndFeel.h
    Created: 17 Apr 2023 11:03:34pm
    Author:  crber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "KAPInterfaceDefines.h"

class KAPLookAndFeel :
    LookAndFeel_V4
{
public:
    KAPLookAndFeel();
    ~KAPLookAndFeel();

    Font getTextButtonFont(TextButton&, int buttonHeight) override
    {
        return font_1;
    }
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        Colour fillColour;
        if (shouldDrawButtonAsDown) 
        {
            fillColour = KAPColour_5;
        }
        else if (shouldDrawButtonAsHighlighted)
        {
            fillColour = KAPColour_3;
        }

        const float cornerSize = 6.0f;

        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);

    }

private:

};