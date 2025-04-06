//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>
//#include <string>
#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <cassert>
#include <cmath>

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
#include "XPLMProcessing.h"
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


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------
#include "cdatarefs.h"


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------
#include "cdatarefs_test.h"


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------




//======================================================================================================================

CDataref toga_cdr_test_int("toga/b717/misc/xxxx/tst/cdr_test_int", int_cdr_T, 1);
CDataref toga_cdr_test_float("toga/b717/misc/xxxx/tst/cdr_test_float", float_cdr_T, 1);
CDataref toga_cdr_test_dbl("toga/b717/misc/xxxx/tst/cdr_test_dbl", double_cdr_T, 1);
CDataref toga_cdr_test_intV("toga/b717/misc/xxxx/tst/cdr_test_intV", intv_cdr_T, 1, 8);
CDataref toga_cdr_test_floatV("toga/b717/misc/xxxx/tst/cdr_test_floatV", floatv_cdr_T, 1, 6, true);
CDataref toga_cdr_test_floatV2("toga/b717/misc/xxxx/tst/cdr_test_floatV2", floatv_cdr_T, 1, 6, true);
CDataref toga_cdr_test_byteV("toga/b717/misc/xxxx/tst/cdr_test_byteV", bytev_cdr_T, 1, 30, "custom test byte Dataref", true);
CDataref toga_cdr_test_byteStr("toga/b717/misc/xxxx/tst/cdr_test_byteStr", bytev_cdr_T, 1, 40, "custom test byte Dataref (String)", true);







float CustomDatarefTestFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    CustomDatarefTest();

    return -1;
}



bool do_convenience_getters = true;

void CustomDatarefTest()
{
    //==[ USING CONVENIENCE SETTERS ]===================================================

    // Integer
    toga_cdr_test_int.setInt(7);

    // Float
    toga_cdr_test_float.setFloat(20.53689);

    // Long
    toga_cdr_test_dbl.setDouble(9.489768435468);

    // Integer Array
    int int_values[8] = {5, 10, 15, 20, 25, 30, 35, 40};
    toga_cdr_test_intV.setIntV(0, 8, int_values);

    // Float Array (static)
    float float_values[6] = {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
    toga_cdr_test_floatV.setFloatV(0, 6, float_values);

    // Float Array (dynamic)
    static float animation_values[6];
    for (int i = 0; i < 6; ++i) {
        animation_values[i] = sin(XPLMGetElapsedTime()) * 10.0f + i;
    }
    toga_cdr_test_floatV2.setFloatV(0, 6, animation_values);

    // Byte (char)
    char byte_test[] = "xxxxx";
    toga_cdr_test_byteV.setByte(strlen(byte_test), byte_test);

    // ByteStr (string)
    toga_cdr_test_byteStr.setByteStr("test byte string");




    //==[ USING CONVENIENCE GETTERS ]===================================================

    if (do_convenience_getters)
    {
        printf("\n");
        printf("do_convenience_getters......\n");
        printf("Test Integer Get: %d \n", toga_cdr_test_int.getInt());
        printf("Test Float Get: %f \n", toga_cdr_test_float.getFloat());
        printf("Test Double Get: %14.12lf \n", toga_cdr_test_dbl.getDouble());

        int toga_int_array[8];
        toga_cdr_test_intV.getIntV(2, 1, toga_int_array);
        printf("Test Integer Array Get[0]: %d \n", toga_int_array[0]);


        do_convenience_getters = false;
    }

}



//----------------------------------------------------------------------------------------------------------------------
void RegisterCustDatarefTest(){
    XPLMRegisterFlightLoopCallback(CustomDatarefTestFLCB, -1, nullptr);
};
//----------------------------------------------------------------------------------------------------------------------
void UnregisterCustDatarefTest(){
    XPLMUnregisterFlightLoopCallback(CustomDatarefTestFLCB,	nullptr);
};
