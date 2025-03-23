//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#include "imgui_wrapper.h"
#include "../IMGUI/backends/imgui_impl_opengl2.h"
#include "../../src/imgui_impl_xplane.h"
#include "../SDK/CHeaders/XPLM/XPLMGraphics.h"
//#include <GL/gl.h>

namespace ImGuiWrapper {

    void Init() {
        ImGui::CreateContext();
        ImGui_ImplOpenGL2_Init();
        ImGui_ImplXPlane_Init();
    }

    void BeginFrame() {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplXPlane_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    void Shutdown() {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplXPlane_Shutdown();
        ImGui::DestroyContext();
    }

} // namespace ImGuiWrapper

