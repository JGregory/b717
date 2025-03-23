//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#include "../lib/TOGA/imgui_wrapper.h"
#include "XPLMDisplay.h"
#include "XPLMUtilities.h"
#include "autopilot_ui.h"
#include <string>

// Window visibility flag
static bool showAutopilotWindow = true;

// =========================
// INITIALIZATION FUNCTION
// =========================
void InitAutopilotUI() {
    XPLMDebugString("[Autopilot UI] Initialized.\n");
}

// =========================
// DRAWING CALLBACK FUNCTION
// =========================
int DrawCallback(XPLMDrawingPhase inPhase, int inIsBefore, void* inRefcon) {
    if (inPhase != xplm_Phase_Window || inIsBefore) {
        return 1;  // Continue drawing in the next frame
    }

    ImGuiWrapper::BeginFrame();  // Start ImGui frame

    if (showAutopilotWindow) {
        ImGui::SetNextWindowPos(ImVec2(200, 150), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Once);

        ImGui::Begin("Autopilot Control", &showAutopilotWindow,
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Autopilot Settings");
        static float altitude = 10000.0f;
        ImGui::SliderFloat("Altitude", &altitude, 0.0f, 40000.0f);

        if (ImGui::Button("Set Altitude")) {
            std::string logMsg = "[Autopilot UI] Altitude set to " + std::to_string((int)altitude) + "\n";
            XPLMDebugString(logMsg.c_str());
        }

        ImGui::End();
    }

    ImGuiWrapper::EndFrame();  // End ImGui frame

    return 1;  // Continue drawing in the next frame
}

// =========================
// REGISTRATION FUNCTIONS
// =========================
void RegisterAutopilotUI() {
    XPLMRegisterDrawCallback(DrawCallback, xplm_Phase_Window, 0, nullptr);
    XPLMDebugString("[Autopilot UI] Registered Draw Callback.\n");
}

void UnregisterAutopilotUI() {
    XPLMUnregisterDrawCallback(DrawCallback, xplm_Phase_Window, 0, nullptr);
    XPLMDebugString("[Autopilot UI] Unregistered Draw Callback.\n");
}
