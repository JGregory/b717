//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//=====================================================[ INCLUDES ]=====================================================

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>

#include <iostream>
using std::string;
using std::cout;
using std::endl;


//--[ X-PLANE SDK LIBRARY INCLUDES ]------------------------------------------------------------------------------------
// #include "XPLMCamera.h"
// #include "XPLMDataAccess.h"
// #include "XPLMDefs.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
// #include "XPLMInstance.h"
// #include "XPLMMap.h"
// #include "XPLMMenus.h"
// #include "XPLMNavigation.h"
// #include "XPLMPlanes.h"
// #include "XPLMPlugin.h"
// #include "XPLMProcessing.h"
// #include "XPLMScenery.h"
// #include "XPLMSound.h"
#include "XPLMUtilities.h"
// #include "XPLMWeather.h"
// #include "XPStandardWidgets.h"
// #include "XPUIGraphics.h"
// #include "XPWidgetDefs.h"
// #include "XPWidgets.h"
// #include "XPWidgetUtils.h"

//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------
#include "../lib/IMGUI/imgui.h"


//--[ IMGUI XP INTEGRATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "../lib/TOGA/imgui_wrapper.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------
#include "autopilot_ui.h"


//=======================================================================================================


// Window visibility flag
static bool showAutopilotWindow = true;


// =========================
// INITIALIZATION FUNCTION
// =========================
void InitAutopilotUI() {

    int screenWidth, screenHeight;
    XPLMGetScreenSize(&screenWidth, &screenHeight);
    cout << "[B717] " << screenWidth << " " << screenHeight << endl;

    int sl, st, sr, sb;
    XPLMGetScreenBoundsGlobal(&sl, &st, &sr, &sb);
    cout << "[B717] " << sl << " " << st << " " << sr << " " << sb << endl;

    XPLMDebugString("[Autopilot UI] Initialized.\n");
}


// =========================
// DRAWING CALLBACK FUNCTION
// =========================
int DrawAutopilotUIWindow(XPLMDrawingPhase inPhase, int inIsBefore, void* inRefcon) {
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
    XPLMRegisterDrawCallback(DrawAutopilotUIWindow, xplm_Phase_Window, 0, nullptr);
    XPLMDebugString("[Autopilot UI] Registered Draw Callback.\n");
}

void UnregisterAutopilotUI() {
    XPLMUnregisterDrawCallback(DrawAutopilotUIWindow, xplm_Phase_Window, 0, nullptr);
    XPLMDebugString("[Autopilot UI] Unregistered Draw Callback.\n");
}
