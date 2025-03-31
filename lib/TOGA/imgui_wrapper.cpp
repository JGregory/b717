//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
//#include <string>
//#include <iostream>
//#include <vector>
//#include<cstdio>
//#include <cassert>

//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;
//using std::printf;


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
// #include "XPLMCamera.h"
// #include "XPLMDataAccess.h"
// #include "XPLMDefs.h"
// #include "XPLMDisplay.h"
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
#include "backends/imgui_impl_opengl2.h"


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------
#include "imgui_xp_impl.h"


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


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

