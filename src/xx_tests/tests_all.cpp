// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
//#include <string>
//#include <iostream>
//#include <vector>
#include <cstdio>
//#include <cassert>
//#include <cmath>

//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;
using std::printf;


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
#include "XPLMUtilities.h"
// #include "XPLMWeather.h"
// #include "XPStandardWidgets.h"
// #include "XPUIGraphics.h"
// #include "XPWidgetDefs.h"
// #include "XPWidgets.h"
// #include "XPWidgetUtils.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "cdr.h"
#include "xdr.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------
#include "tests_cdatarefs.h"
#include "tests_xdatarefs.h"
#include "tests_all.h"


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================



#ifdef ENABLE_TESTS

static XPLMCommandRef gRunAllTestsCmd = nullptr;

void runAllTests() {
    printf("\n");
    printf("[=================================================]\n");
    printf("All registered tests in progress...\n");
    run_cdr_tests();
    run_xdr_tests();

    printf("\nAll registered tests completed.\n");
    printf("[=================================================]\n");
    printf("\n");
}

int run_all_tests_cb(XPLMCommandRef, XPLMCommandPhase phase, void*) {
    if (phase == xplm_CommandBegin) {
        runAllTests();
    }
    return 1;
}

void registerTestCommand() {
    gRunAllTestsCmd = XPLMCreateCommand("toga/gnrl/xxxx/cmd/run_all_tests", "Run all tests");
    XPLMRegisterCommandHandler(gRunAllTestsCmd, run_all_tests_cb, 1, nullptr);
}

void unregisterTestCommand() {
    if (gRunAllTestsCmd) {
        XPLMUnregisterCommandHandler(gRunAllTestsCmd, run_all_tests_cb, 1, nullptr);
        gRunAllTestsCmd = nullptr;
    }
}

#endif
