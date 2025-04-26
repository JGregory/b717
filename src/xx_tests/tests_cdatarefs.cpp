// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

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
    CDataref int_dr("test/custom/int_dr", int_cdr_T, 1);
    int_dr.setInt(42);
    printf("Custom Int (set/get): %d\n", int_dr.getInt());

    CDataref float_dr("test/custom/float_dr", float_cdr_T, 1);
    float_dr.setFloat(3.14f);
    printf("Custom Float (set/get): %.2f\n", float_dr.getFloat());

    CDataref double_dr("test/custom/double_dr", double_cdr_T, 1);
    double_dr.setDouble(12345.678);
    printf("Custom Double (set/get): %.3f\n", double_dr.getDouble());
}

void test_cdataref_arrays() {
    CDataref int_array("test/custom/int_array", intv_cdr_T, 3, 1);
    int_array.setIntV({1, 2, 3});
    auto ints = int_array.getIntV(0, 3);
    printf("Custom Int Array (set/get): %d %d %d\n", ints[0], ints[1], ints[2]);

    CDataref float_array("test/custom/float_array", floatv_cdr_T, 2, true, 1);
    float_array.setFloatV({4.4f, 5.5f});
    auto floats = float_array.getFloatV(0, 2);
    printf("Custom Float Array (set/get): %.1f %.1f\n", floats[0], floats[1]);
}

void test_cdataref_bytestring() {
    const char* test_str = "hello world";
    CDataref byte_dr("test/custom/byte_str", bytev_cdr_T, strlen(test_str) + 1, test_str, true, 1);
    printf("Custom Byte String (set/get): %s\n", byte_dr.getByteStr().c_str());
}









#ifdef ENABLE_TESTS
void run_cdr_tests() {
    try {
        printf("\n[CDataref]...\n");
        test_cdataref_scalars();
        test_cdataref_arrays();
        test_cdataref_bytestring();

        // Manually pull values to verify caching
        printf("\n[CDataref] Verifying fetchNow() behavior...\n");

        CDataref test_int2("test/custom/int2_dr", int_cdr_T, 1);
        CDataref test_float2("test/custom/float2_dr", float_cdr_T, 1);
        CDataref test_double2("test/custom/float2_dr", double_cdr_T, 1);
        CDataref test_int_array2("test/custom/int2_array", intv_cdr_T, 3, 1);
        CDataref test_float_array2("test/custom/float_array2", floatv_cdr_T, 2, true, 1);
        CDataref test_bytes2("test/custom/byte2_str", floatv_cdr_T, 32, "test byte array", true, 1);

        test_int2.setInt(123);
        test_float2.setFloat(9.81f);
        test_double2.setDouble(9.816543259f);
        test_int_array2.setIntV({4, 5, 6});
        test_float_array2.setFloatV({1.035, 2.055});
        //  test_bytes2.setByteStr("change byte array");

        test_int2.fetchNow();
        test_float2.fetchNow();
        test_double2.fetchNow();
        test_int_array2.fetchNow();
        test_float_array2.fetchNow();
        test_bytes2.fetchNow();

        printf("Fetched Custom Int2: %d\n", test_int2.getInt());
        printf("Fetched Custom Float2: %.2f\n", test_float2.getFloat());
        printf("Fetched Custom Double2: %.10f\n", test_double2.getDouble());
        auto a = test_int_array2.getIntV(0, 3);
        printf("Fetched Custom IntArray2: %d %d %d\n", a[0], a[1], a[2]);
        auto b = test_float_array2.getFloatV(0, 2);
        printf("Fetched Custom FloatArray2: %f %f\n", b[0], b[1]);
        printf("Fetched Custom Byte String2: %s\n", test_bytes2.getByteStr().c_str());

        printf("|=====> [CDataref] tests passed.\n");
        printf("\n");

    } catch (const std::exception& e) {
        printf("|=====> [CDataref] tests failed: %s\n", e.what());
        printf("\n");
    }
}
#endif

