//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


//=====================================================[ INCLUDES ]=====================================================

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>

//#include <iostream>
//using std::string;
//using std::cout;
//using std::endl;

//#include <vector>
//using std::vector;


//--[ X-PLANE SDK LIBRARY INCLUDES ]------------------------------------------------------------------------------------
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

//--[ IMGUI XP INTEGRATION HEADERS ]------------------------------------------------------------------------------------
#include "imgui_xp_integ.h"


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================

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

