/*
  ==============================================================================

    KAPInterfaceDefines.h
    Created: 17 Jan 2023 9:08:15pm
    Author:  crber

  ==============================================================================
*/

#pragma once
//helpers are being used to change global values app-wide

#define MAIN_PANEL_WIDTH    700
#define MAIN_PANEL_HEIGHT   300

#define TOP_PANEL_WIDTH     MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT    45

#define GAIN_PANEL_WIDTH    100
#define GAIN_PANEL_HEIGHT   MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT

#define CENTER_PANEL_WIDTH  MAIN_PANEL_WIDTH - (GAIN_PANEL_WIDTH * 2)
#define CENTER_PANEL_HEIGHT GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH     CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT    35

#define EFFECTS_PANEL_WIDTH     CENTER_PANEL_WIDTH
#define EFFECTS_PANEL_HEIGHT    CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT

