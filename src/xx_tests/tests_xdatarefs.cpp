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
#include "XPLMDataAccess.h"
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


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "datatypes.h"
#include "xdr.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------
//#include "cdatarefs.h"


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------
//#include "tests_xdatarefs.h"


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


void test_xdataref_scalars() {
    XDataref gear_handle("sim/cockpit/switches/gear_handle_status", xplmType_Int, false);
    gear_handle.fetchNow();
    printf("Gear Handle (int): %d\n", gear_handle.valuei());

    XDataref altitude("sim/flightmodel/position/elevation", xplmType_Float, false);
    altitude.fetchNow();
    printf("Altitude (float): %.2f\n", altitude.valuef());

    XDataref sim_time("sim/time/total_flight_time_sec", xplmType_Double, false);
    sim_time.fetchNow();
    printf("Sim Time (double): %.2f\n", sim_time.valued());
}

void test_xdataref_arrays() {
    XDataref batteries("sim/cockpit2/electrical/battery_on", xplmType_IntArray, false);
    batteries.fetchNow();
    printf("Battery 0: %d\n", batteries.valuesi()[0]);
    printf("Battery 1: %d\n", batteries.valuesi()[1]);

    XDataref engines("sim/flightmodel/engine/ENGN_thro", xplmType_FloatArray, false);
    engines.fetchNow();
    printf("Throttle 0: %.2f\n", engines.valuesf()[0]);
    printf("Throttle 1: %.2f\n", engines.valuesf()[1]);
}

void test_xdataref_string() {
    XDataref aircraft_name("sim/aircraft/view/acf_descrip", xplmType_Data, false);
    aircraft_name.fetchNow();
    printf("Aircraft: %s\n", aircraft_name.stringValue().c_str());
}






#ifdef ENABLE_TESTS


void run_xdr_tests() {
    try {
        test_xdataref_scalars();
        test_xdataref_arrays();
        test_xdataref_string();
        printf("|=====> XDataref tests passed.\n");
    } catch (const std::exception& e) {
        printf("|=====> XDataref tests failed: %s\n", e.what());
    }
}


#endif
