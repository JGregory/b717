//
// Created by James Gregory on 3/22/25.
//


#include "imgui_wrapper.h"
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
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplXPlane_NewFrame();
    ImGui::NewFrame();

    // Example UI
    ImGui::Begin("X-Plane Plugin Window");
    ImGui::Text("Hello, X-Plane!");
    if (ImGui::Button("Click Me")) {
        XPLMDebugString("Button clicked!\n");
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

// Cleanup
void ImGuiWrapper::Shutdown() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplXPlane_Shutdown();
    ImGui::DestroyContext();
}
