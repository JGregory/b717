//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
// #include <cstring>

// #include <iostream>
// using std::string;
// using std::cout;
// using std::endl;

//#include <vector>
//using std::vector;


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


//--[ IMGUI XP INTEGRATION HEADERS ]------------------------------------------------------------------------------------
#include "imgui_xp_integ.h"


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "imgui_wrapper.h"


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

