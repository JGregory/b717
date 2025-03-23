//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef IMGUI_WRAPPER_H
#define IMGUI_WRAPPER_H



#include "../lib/IMGUI/imgui.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"



class ImGuiWrapper {
public:
    static void Init();
    static void Render();
    static void Shutdown();
};


#endif //IMGUI_WRAPPER_H
