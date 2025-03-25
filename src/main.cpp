//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>

#include <iostream>
using std::string;
using std::cout;
using std::endl;

#include<cstdio>
using std::printf;


//--[ X-PLANE SDK LIBRARY INCLUDES ]------------------------------------------------------------------------------------
//  #include "XPLMCamera.h"
//  #include "XPLMDataAccess.h"
#include "XPLMDefs.h"
#include "XPLMDisplay.h"
//  #include "XPLMGraphics.h"
//  #include "XPLMInstance.h"
//  #include "XPLMMap.h"
//  #include "XPLMMenus.h"
//  #include "XPLMNavigation.h"
//  #include "XPLMPlanes.h"
//  #include "XPLMPlugin.h"
//  #include "XPLMProcessing.h"
//  #include "XPLMScenery.h"
//  #include "XPLMSound.h"
//  #include "XPLMUtilities.h"
//  #include "XPLMWeather.h"
//  #include "XPStandardWidgets.h"
//  #include "XPUIGraphics.h"
//  #include "XPWidgetDefs.h"
//  #include "XPWidgets.h"
//  #include "XPWidgetUtils.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP INTEGRATION HEADERS ]------------------------------------------------------------------------------------
#include "../lib/TOGA/debug_flag.h"


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "../lib/TOGA/version.h"
#include "../lib/TOGA/imgui_wrapper.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------
#include "xx_examples/autopilot_ui.h"


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


// Forward declarations
int DrawCallback(
    XPLMDrawingPhase inPhase,    // Drawing phase
    int inIsBefore,              // Before or after the phase
    void* inRefcon               // User-defined data
);


PLUGIN_API int XPluginStart(char * outName,
                            char * outSig,
                            char * outDesc)
{
    cout << "" << endl;
    cout << "[B717] XPluginStart: " << PROJECT_NAME << "v" << PROJECT_VERSION << endl;



    //------------------------ PLUGIN DATA -----------------------------
    char sName[256];
    strcpy(sName, "TOGA B717v");
    strcat(sName, PROJECT_VERSION);

    strcpy(outName, sName);
    strcpy(outDesc, "Plugin for Boeing 717 Systems");
    strcpy(outSig, "toga.b717");



    //--------------------------- DEBUG --------------------------------
    DEBUG = true;
    USER_DEBUG = false;

    if (DEBUG)
    {
        cout << "[B717] ==============================================" << endl;
        cout << "[B717] =====--->>    DEBUG MODE ENABLED    <<---=====" << endl;
        cout << "[B717] ==============================================" << endl;
    }


    printf("TESTING");
    ImGuiWrapper::Init();               // Initialize ImGui

    InitAutopilotUI();                  // Initialize Autopilot UI
    RegisterAutopilotUI();              // Register Autopilot UI Callback

    return 1;

}









PLUGIN_API void	XPluginStop(void)
{
    cout << "[B717] XPluginStop: " << endl;




    ImGuiWrapper::Shutdown();           // Cleanup ImGui
    UnregisterAutopilotUI();          // Unregister Autopilot UI Callback


}










PLUGIN_API int XPluginEnable(void)
{
    cout << "[B717] XPluginEnable: " << endl;


    return 1;
}










PLUGIN_API void XPluginDisable(void)
{
    cout << "[B717] XPluginDisable: " << endl;


}










PLUGIN_API void XPluginReceiveMessage(XPLMPluginID sender,
                                      long inMessage,
                                      void * inParam)
{
    cout << "[B717] XPluginReceiveMessage: " << sender << inMessage << inParam << endl;


}



