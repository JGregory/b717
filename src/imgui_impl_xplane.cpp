//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#include "imgui_impl_xplane.h"
#include "imgui.h"
#include "XPLMGraphics.h"
#include "XPLMDisplay.h"

// =========================
// INITIALIZATION FUNCTION
// =========================
void ImGui_ImplXPlane_Init() {
    // No special initialization logic required for X-Plane at the moment
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard control for ImGui
}

// =========================
// SHUTDOWN FUNCTION
// =========================
void ImGui_ImplXPlane_Shutdown() {
    // No specific shutdown logic is required yet
    // Any cleanup logic specific to ImGui-X-Plane integration can go here
}

// =========================
// PER-FRAME LOGIC
// =========================
void ImGui_ImplXPlane_NewFrame() {
    int windowWidth, windowHeight;
    XPLMGetScreenSize(&windowWidth, &windowHeight);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);
}

