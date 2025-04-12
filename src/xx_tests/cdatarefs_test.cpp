//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>
#include <string>
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


bool run_cdr_test = false;      // Change to true to run the test... output goes to terminal window


CDataref toga_cdr_test_int("toga/b717/misc/xxxx/tst/cdr_test_int", int_cdr_T, 1);
CDataref toga_cdr_test_float("toga/b717/misc/xxxx/tst/cdr_test_float", float_cdr_T, 1);
CDataref toga_cdr_test_dbl("toga/b717/misc/xxxx/tst/cdr_test_dbl", double_cdr_T, 1);
CDataref toga_cdr_test_intV("toga/b717/misc/xxxx/tst/cdr_test_intV", intv_cdr_T, 8, 1);
CDataref toga_cdr_test_floatV("toga/b717/misc/xxxx/tst/cdr_test_floatV", floatv_cdr_T, 5, true, 1);
CDataref toga_cdr_test_floatV2("toga/b717/misc/xxxx/tst/cdr_test_floatV2", floatv_cdr_T, 6, true, 1);
CDataref toga_cdr_test_byteV("toga/b717/misc/xxxx/tst/cdr_test_byteV", bytev_cdr_T, 30, "custom test byte Dataref", true, 1);
CDataref toga_cdr_test_byteStr("toga/b717/misc/xxxx/tst/cdr_test_byteStr", bytev_cdr_T, 40, "custom test byte Dataref (String)", true, 1);









float CustomDatarefTestFLCB(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    CustomDatarefTest();

    return -1;
}



bool do_convenience_getters = true;

void CustomDatarefTest()
{

    //-- Integer
    toga_cdr_test_int.setInt(7);

    //-- Float
    toga_cdr_test_float.setFloat(20.53689);

    //-- Double
    toga_cdr_test_dbl.setDouble(9.489768435468);


    //-- Integer Array (4 options) uncomment only one at a time for testing

    //-- Integer Array Full Write
    std::vector<int> values = {10, 20, 30, 40, 50, 60};
    toga_cdr_test_intV.setIntV(values);

    //-- Integer Array Partial Write Starting at Index 2
    //std::vector<int> values2 = {101, 102};
    //toga_cdr_test_intV.setIntV(2, 2, values2);  // Writes to index 2 and 3

    //-- Integer Array Inline (no temporary)
    //toga_cdr_test_intV.setIntV({1, 2, 3, 4, 5});

    //-- Integer Array Paritial Inline
    //toga_cdr_test_intV.setIntV(1, 3, {7, 8, 9});  // Start at index 1, write 3 values




    //-- Float Array (4 options) uncomment only one at a time for testing

    //-- Float Array Full Write
    std::vector<float> temps = {21.5f, 22.0f, 22.7f, 21.2, 20.3};
    toga_cdr_test_floatV.setFloatV(temps);

    //-- Float Array Partial Write Starting at Index 2
    //std::vector<float> updates = {99.1f, 100.2f};
    //toga_cdr_test_floatV.setFloatV(4, 2, updates);  // Writes to index 4 and 5

    //-- Float Array Inline (no temporary)
    //toga_cdr_test_floatV.setFloatV({3.14f, 2.71f, 1.41f});

    //-- Float Array Paritial Inline
    //toga_cdr_test_floatV.setFloatV(0, 2, {5.5f, 6.6f});

    //-- Float Array (dynamic)
    std::vector<float> animation_values(6);
    for (int i = 0; i < 6; ++i) {
        animation_values[i] = sin(XPLMGetElapsedTime()) * 10.0f + i;
    }
    toga_cdr_test_floatV2.setFloatV(animation_values);




    //-- Byte (char)
    char byte_test[] = "xxxxx";
    toga_cdr_test_byteV.setByte(strlen(byte_test), byte_test);

    //-- ByteStr (string)
    toga_cdr_test_byteStr.setByteStr("test byte string");




    //==[ USING CONVENIENCE GETTERS ]===================================================

    if (do_convenience_getters)
    {
        printf("\n");
        printf("do_convenience_getters......\n");

        // Integer
        printf("Test Integer Get: %d \n", toga_cdr_test_int.getInt());

        // Float
        printf("Test Float Get: %f \n", toga_cdr_test_float.getFloat());

        // Double
        printf("Test Double Get: %14.12lf \n", toga_cdr_test_dbl.getDouble());

        // Interger Array
        std::vector<int> readback = toga_cdr_test_intV.getIntV(0, 4);
        for (int i = 0; i < readback.size(); ++i)
            printf("int[%d] = %d\n", i, readback[i]);

        // Float Array
        std::vector<float> test_float_array = toga_cdr_test_floatV.getFloatV(0, 3);
        for (int i = 0; i < test_float_array.size(); ++i) {
            printf("Test Float Array Get: test_float_array[%d] = %f\n", i, test_float_array[i]);
        }

        // Float Array (Dynamic)
        std::vector<float> test_float_array_dyn = toga_cdr_test_floatV.getFloatV(0, 3);
        for (int i = 0; i < test_float_array_dyn.size(); ++i) {
            printf("Test Float Array (Dynamic) Get: test_float_array[%d] = %f\n", i, test_float_array_dyn[i]);
        }

        // String

        string test_string = toga_cdr_test_byteV.getByteStr();
        printf("Test String Get: %s\n", test_string.c_str());


        do_convenience_getters = false;     // Only run the getters once
    }

}



//----------------------------------------------------------------------------------------------------------------------
void RegisterCustDatarefTest(){
    if (run_cdr_test)
    {
        XPLMRegisterFlightLoopCallback(CustomDatarefTestFLCB, -1, nullptr);
    }
};
//----------------------------------------------------------------------------------------------------------------------
void UnregisterCustDatarefTest(){
    if (run_cdr_test)
    {
        XPLMUnregisterFlightLoopCallback(CustomDatarefTestFLCB,	nullptr);
    }
};
