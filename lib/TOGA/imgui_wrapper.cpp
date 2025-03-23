//
// Created by James Gregory on 3/22/25.
//

#include <iostream>

using std::string;

#include "../lib/IMGUI/imgui.h"
#include "../lib/TOGA/imgui_wrapper.h"
#include "../lib/IMGUI/backends/imgui_impl_opengl2.h"  // ImGui's OpenGL 2 backend
#include "../src/imgui_impl_xplane.h"   // We'll create this custom backend
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include <OpenGL/gl.h>                // OpenGL headers  TODO:  This is MacOS only

// Initialization
void ImGuiWrapper::Init() {
    ImGui::CreateContext();
    ImGui_ImplOpenGL2_Init();  // Initialize ImGui with OpenGL2
    ImGui_ImplXPlane_Init();   // Custom X-Plane integration
}

// Rendering
void ImGuiWrapper::Render() {
    // Ensure OpenGL state is correctly set for ImGui
    XPLMSetGraphicsState(0, 0, 0, 0, 1, 0, 0);

    // ImGui Frame Start
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplXPlane_NewFrame();
    ImGui::NewFrame();

    // =========================
    // *** WINDOW CONTENT HERE ***
    // =========================
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f);  // Ensure it's fully visible

    ImGui::Begin("X-Plane Plugin Window", nullptr,
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoMove);

    ImGui::Text("Hello, X-Plane!");
    if (ImGui::Button("Test Button")) {
        XPLMDebugString("[ImGui] Button clicked!\n");
    }

    ImGui::End();  // End ImGui Window
    // =========================

    // ImGui Frame End
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


// Cleanup
void ImGuiWrapper::Shutdown() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplXPlane_Shutdown();
    ImGui::DestroyContext();
}
