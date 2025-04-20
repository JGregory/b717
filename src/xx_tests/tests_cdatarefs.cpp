//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>
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


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------
#include "cdr.h"


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


void test_cdataref_scalars() {
    CDataref int_dr("test/custom/int_dr", int_cdr_T, true);
    int_dr.setInt(42);
    printf("Custom Int: %d\n", int_dr.getInt());

    CDataref float_dr("test/custom/float_dr", float_cdr_T, true);
    float_dr.setFloat(3.14f);
    printf("Custom Float: %.2f\n", float_dr.getFloat());

    CDataref double_dr("test/custom/double_dr", double_cdr_T, true);
    double_dr.setDouble(12345.678);
    printf("Custom Double: %.3f\n", double_dr.getDouble());
}

void test_cdataref_arrays() {
    CDataref int_array("test/custom/int_array", intv_cdr_T, 3, true);
    int_array.setIntV({1, 2, 3});
    auto ints = int_array.getIntV(0, 3);
    printf("Custom Int Array: %d %d %d\n", ints[0], ints[1], ints[2]);

    CDataref float_array("test/custom/float_array", floatv_cdr_T, 2, true);
    float_array.setFloatV({4.4f, 5.5f});
    auto floats = float_array.getFloatV(0, 2);
    printf("Custom Float Array: %.1f %.1f\n", floats[0], floats[1]);
}

void test_cdataref_bytestring() {
    const char* test_str = "hello world";
    CDataref byte_dr("test/custom/byte_str", bytev_cdr_T, strlen(test_str) + 1, test_str, true);
    printf("Custom Byte String: %s\n", byte_dr.getByteStr().c_str());
}









#ifdef ENABLE_TESTS
void run_cdr_tests() {
    try {
        test_cdataref_scalars();
        test_cdataref_arrays();
        test_cdataref_bytestring();

        // Manually pull values to verify caching
        printf("\n[CDataref] Verifying fetchNow() behavior...\n");

        CDataref test_int2("test/custom/int2_dr", int_cdr_T, true);
        CDataref test_float2("test/custom/float2_dr", float_cdr_T, true);
        CDataref test_array2("test/custom/int2_array", intv_cdr_T, 3, true);
        CDataref test_bytes2("test/custom/byte2_str", floatv_cdr_T, 32, "fetch_test", true);

        test_int2.setInt(123);
        test_float2.setFloat(9.81f);
        test_array2.setIntV({4, 5, 6});
        test_bytes2.setByteStr("check123");

        test_int2.fetchNow();
        test_float2.fetchNow();
        test_array2.fetchNow();
        test_bytes2.fetchNow();

        printf("Fetched Int: %d\n", test_int2.getInt());
        printf("Fetched Float: %.2f\n", test_float2.getFloat());
        auto a = test_array2.getIntV(0, 3);
        printf("Fetched IntArray: %d %d %d\n", a[0], a[1], a[2]);
        printf("Fetched Byte String: %s\n", test_bytes2.getByteStr().c_str());

        printf("|=====> CDataref tests passed.\n");
    } catch (const std::exception& e) {
        printf("|=====> CDataref tests failed: %s\n", e.what());
    }
}
#endif

