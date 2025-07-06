// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
#include "XPLMDataAccess.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
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
    std::printf("Gear Handle (int): %d\n", gear_handle.valuei());

    XDataref altitude("sim/flightmodel/position/elevation", xplmType_Float, false);
    altitude.fetchNow();
    std::printf("Altitude (float): %.2f\n", altitude.valuef());

    XDataref sim_alt("sim/flightmodel2/position/pressure_altitude", xplmType_Double, false);
    sim_alt.fetchNow();
    std::printf("Sim Press Alt (double): %.12f\n", sim_alt.valued());
}

void test_xdataref_arrays() {
    XDataref batteries("sim/cockpit2/electrical/battery_on", xplmType_IntArray, false);
    batteries.fetchNow();
    std::printf("Battery 0 (int array): %d\n", batteries.valuesi()[0]);
    std::printf("Battery 1 (int array): %d\n", batteries.valuesi()[1]);

    XDataref engines("sim/flightmodel/engine/ENGN_thro", xplmType_FloatArray, false);
    engines.fetchNow();
    std::printf("Throttle 0 (float array): %.2f\n", engines.valuesf()[0]);
    std::printf("Throttle 1 (float array): %.2f\n", engines.valuesf()[1]);
}

void test_xdataref_string() {
    XDataref aircraft_name("sim/aircraft/view/acf_descrip", xplmType_Data, false);
    aircraft_name.fetchNow();
    std::printf("Aircraft (byte array): %s\n", aircraft_name.stringValue().c_str());
}






#ifdef ENABLE_TESTS


void run_xdr_tests() {
    try {
        std::printf("\n[XDataref]...\n");
        test_xdataref_scalars();
        test_xdataref_arrays();
        test_xdataref_string();
        std::printf("|=====> [XDataref] tests passed.\n");
    } catch (const std::exception& e) {
        std::printf("|=====> [XDataref] tests failed: %s\n", e.what());
    }
}


#endif
