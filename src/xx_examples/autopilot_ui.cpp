//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//=====================================================[ INCLUDES ]=====================================================

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
//#include <string>
#include <iostream>
//#include <vector>
#include <cstdio>
//#include <cassert>

//using std::cout;
//using std::endl;
using std::string;
//using std::vector;
using std::printf;


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
// #include "XPLMCamera.h"
// #include "XPLMDataAccess.h"
// #include "XPLMDefs.h"
#include "XPLMDisplay.h"
// #include "XPLMGraphics.h"
// #include "XPLMInstance.h"
// #include "XPLMMap.h"
// #include "XPLMMenus.h"
// #include "XPLMNavigation.h"
// #include "XPLMPlanes.h"
// #include "XPLMPlugin.h"
// #include "XPLMProcessing.h"
// #include "XPLMScenery.h"
// #include "XPLMSound.h"
// #include "XPLMUtilities.h"
// #include "XPLMWeather.h"
// #include "XPStandardWidgets.h"
// #include "XPUIGraphics.h"
// #include "XPWidgetDefs.h"
// #include "XPWidgets.h"
// #include "XPWidgetUtils.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------
#include "imgui.h"


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "imgui_wrapper.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------
#include "autopilot_ui.h"


//=======================================================================================================




// Window visibility flag
static bool showAutopilotWindow = true;

//ImFont* font2 = nullptr;


// =========================
// INITIALIZATION FUNCTION
// =========================
void InitAutopilotUI() {

   //ImGuiIO& io = ImGui::GetIO();
   //io.Fonts->AddFontFromFileTTF("../../resources/fonts/JetBrainsMono-Regular.ttf", 14);

    int screenWidth, screenHeight;
    XPLMGetScreenSize(&screenWidth, &screenHeight);
    printf("[Autopilot UI] SW/SH: %d %d \n", screenWidth, screenHeight);

    int sl, st, sr, sb;
    XPLMGetScreenBoundsGlobal(&sl, &st, &sr, &sb);
    printf("[Autopilot UI] SL/ST/SR/SB: %d %d %d %d \n", sl, st, sr, sb);

    printf("[Autopilot UI] Initialized.\n");
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
            ImGuiWindowFlags_NoTitleBar);
           // ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::SeparatorText("Autopilot Settings");

        //ImGui::PushFont(font2);
        //ImGui::Text("Hello with another font");
        //ImGui::PopFont();
        //static float altitude = 10000.0f;
        //ImGui::SliderFloat("Altitude", &altitude, 0.0f, 40000.0f);

        //if (ImGui::Button("Set Altitude")) {
        //    std::string logMsg = "[DrawAutopilotUIWindow] Altitude set to: " + std::to_string((int)altitude);
        //    printf("%s\n", logMsg.c_str());
        //}

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
    printf("[Autopilot UI] Registered Draw Callback.\n");
}

void UnregisterAutopilotUI() {
    XPLMUnregisterDrawCallback(DrawAutopilotUIWindow, xplm_Phase_Window, 0, nullptr);
    printf("[Autopilot UI] Unregistered Draw Callback.\n");
}
