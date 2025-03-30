//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>

//#include <iostream>
//using std::string;
//using std::cout;
//using std::endl;

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


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "debug_flag.h"
#include "version.h"
#include "imgui_wrapper.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------
#include "autopilot_ui.h"


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
    printf("\n");
    printf("[B717] XPluginStart: %s %s\n", PROJECT_NAME, PROJECT_VERSION);



    //------------------------ PLUGIN DATA -----------------------------
    char sName[256];
    strcpy(sName, "TOGA B717v");
    strcat(sName, PROJECT_VERSION);

    strcpy(outName, sName);
    strcpy(outDesc, "Plugin for Boeing 717 Systems");
    strcpy(outSig, "toga.b717");



    //--------------------------- DEBUG --------------------------------
    DEBUG = false;
    USER_DEBUG = false;

    if (DEBUG)
    {
        printf("[B717] ==============================================\n");
        printf("[B717] =====--->>    DEBUG MODE ENABLED    <<---=====\n");
        printf("[B717] ==============================================\n");
    }


    //----------------------INIT & REGISTRATION ------------------------
    ImGuiWrapper::Init();               // Initialize ImGui

    InitAutopilotUI();                  // Initialize Autopilot UI
    RegisterAutopilotUI();              // Register Autopilot UI Callback

    return 1;

}









PLUGIN_API void	XPluginStop(void)
{
    printf("[B717] XPluginStop: \n");




    ImGuiWrapper::Shutdown();           // Cleanup ImGui
    UnregisterAutopilotUI();          // Unregister Autopilot UI Callback


}










PLUGIN_API int XPluginEnable(void)
{
    printf("[B717] XPluginEnable: \n");

    return 1;
}










PLUGIN_API void XPluginDisable(void)
{
    printf("[B717] XPluginDisable: \n");

}










PLUGIN_API void XPluginReceiveMessage(XPLMPluginID sender,
                                      long inMessage,
                                      void * inParam)
{
    printf("[B717] XPluginReceiveMessage: %d, %ld, %p \n", sender, inMessage, inParam);

}



