//
// Created by James Gregory on 3/22/25.
//

#include "../lib/IMGUI/imgui.h"
#include "XPLMGraphics.h"
#include "imgui_impl_xplane.h"
#include "XPLMDisplay.h"
#include <OpenGL/gl.h>                // OpenGL headers  TODO:  This is MacOS only

static XPLMDrawWindow_f drawCallback;

void ImGui_ImplXPlane_Init() {
    // Initialize your ImGui-X-Plane window logic here
}

void ImGui_ImplXPlane_NewFrame() {
    // Handle the X-Plane draw logic

    // Ensure the viewport size is updated
    int windowWidth, windowHeight;
    XPLMGetScreenSize(&windowWidth, &windowHeight);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

}

void ImGui_ImplXPlane_Shutdown() {
    // Clean up resources if necessary
}
