//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
#include <string>
//#include <iostream>
//#include <vector>
#include <cstdio>
//#include <cassert>
//#include <cmath>

//using std::cout;
//using std::endl;
using std::string;
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

/*
bool run_xdr_test = true;      // Change to true to run the test... output goes to terminal window


XDataref xdr_currentDay("sim/cockpit2/clock_timer/current_day", int_xdr_T, true, 0);
XDataref xdr_framePeriod("sim/time/framerate_period", float_xdr_T, true, 0);
XDataref xdr_totalFlightTime("sim/time/total_flight_time_sec", double_T, true);




float XDatarefTestFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    XDatarefTest();
    return -1;
}



bool do_xdr_convenience_getters = true;

void XDatarefTest()
{
    //==[ USING CONVENIENCE SETTERS ]===================================================

    // Integer


    // Float


    // Double


    // Interger Array


    // Float Array


    // String (Byte Array)



    //==[ USING CONVENIENCE GETTERS ]===================================================
    if (do_xdr_convenience_getters)
    {
        // Integer
        printf("Test Int Value xdr_currentDay: %d \n", xdr_currentDay.valuei());

        // Float
        printf("Test Float Value xdr_framePeriod: %f \n", xdr_framePeriod.valuef());

        // Double
        printf("Test Double Value xdr_totalFlightTime: %lf \n", xdr_totalFlightTime.valued());

        // Interger Array


        // Float Array


        // String (Byte Array)


        do_xdr_convenience_getters = false;     // Only run the getters once
    }
}






//----------------------------------------------------------------------------------------------------------------------
void RegisterXDatarefTest(){
    if (run_xdr_test)
    {
        XPLMRegisterFlightLoopCallback(XDatarefTestFLCB, -1, nullptr);
    }
};
//----------------------------------------------------------------------------------------------------------------------
void UnregisterXDatarefTest(){
    if (run_xdr_test)
    {
        XPLMUnregisterFlightLoopCallback(XDatarefTestFLCB,	nullptr);
    }
};


*/



void test_xdataref_scalars() {
    XDataref gear_handle("sim/cockpit/switches/gear_handle_status", int_T, false);
    printf("Gear Handle (int): %d\n", gear_handle.valuei());

    XDataref altitude("sim/flightmodel/position/elevation", float_T, false);
    printf("Altitude (float): %.2f\n", altitude.valuef());

    XDataref sim_time("sim/time/total_flight_time_sec", double_T, false);
    printf("Sim Time (double): %.2f\n", sim_time.valued());
}

void test_xdataref_arrays() {
    XDataref batteries("sim/cockpit2/electrical/battery_on", intv_T, 2, true);
    printf("Battery 0: %d\n", batteries.valuesi()[0]);
    printf("Battery 1: %d\n", batteries.valuesi()[1]);

    XDataref engines("sim/flightmodel/engine/ENGN_thro", floatv_T, 2, true);
    printf("Throttle 0: %.2f\n", engines.valuesf()[0]);
    printf("Throttle 1: %.2f\n", engines.valuesf()[1]);
}

void test_xdataref_string() {
    XDataref aircraft_name("sim/aircraft/view/acf_descrip", bytev_cdr_T, 128, nullptr, false);
    printf("Aircraft: %s\n", aircraft_name.stringValue().c_str());
}

#ifdef ENABLE_TESTS
void run_xdr_tests() {
    try {
        test_xdataref_scalars();
        test_xdataref_arrays();
        test_xdataref_string();
        printf("XDataref tests passed.\n");
    } catch (const std::exception& e) {
        printf("XDataref tests failed: %s\n", e.what());
    }
}
#endif
