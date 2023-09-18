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
    KAPLookAndFeel()
    {
        //setting the default ComboBox Colours to our custom ones
        setColour(ComboBox::backgroundColourId, KAPColour_3);
        setColour(ComboBox::outlineColourId, KAPColour_2);
        setColour(ComboBox::arrowColourId, KAPColour_1);
        setColour(ComboBox::textColourId, KAPColour_1);

        //button text colours
        setColour(TextButton::buttonColourId, KAPColour_1);
        setColour(TextButton::textColourOnId, KAPColour_1);
        setColour(TextButton::textColourOffId, KAPColour_1);
    }
    ~KAPLookAndFeel();

    // BUTTONS //
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

    //COMBO BOXES//

    Font getLabelFont(Label& label) override
    {
        return font_1;
    }

    void drawPopupMenuItem(Graphics&, const Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const String& text, const String& shortcutKeyText,
        const Drawable* icon, const Colour* textColour) override
    {

    }

    //SLIDERS//

private:

};