//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef AUTOPILOT_UI_H
#define AUTOPILOT_UI_H


// Initialization and Drawing Functions
void InitAutopilotUI();      // Called once in `XPluginStart()` for any setup logic
void DrawAutopilotWindow();  // Draws the autopilot UI window

// Callback Registration/Unregistration Functions
void RegisterAutopilotUI();   // Registers the drawing callback
void UnregisterAutopilotUI(); // Unregisters the drawing callback


#endif //AUTOPILOT_UI_H
