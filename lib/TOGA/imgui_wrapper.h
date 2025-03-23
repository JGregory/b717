//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef IMGUI_WRAPPER_H
#define IMGUI_WRAPPER_H


#include "imgui.h"


namespace ImGuiWrapper {
    void Init();        // Initialize ImGui (once)
    void BeginFrame();  // Start a new ImGui frame
    void EndFrame();    // Complete ImGui rendering
    void Shutdown();    // Clean up ImGui context
}


#endif //IMGUI_WRAPPER_H
