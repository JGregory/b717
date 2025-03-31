//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef CDR_H
#define CDR_H


//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
#include <string>
//#include <iostream>
#include <vector>
//#include <cstdio>

//using std::cout;
//using std::endl;
using std::string;
using std::vector;
//using std::printf;


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


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


class CDataref {

public:
    static vector<CDataref *> custom_datarefs;
    XPLMDataRef dr_handle;
    string dr_name;
    int dr_type;        // See datatypes.h
    int dr_is_writeable;
    int i_value;
    float f_value;
    double d_value;
    vector<int> i_array_values;
    vector<float> f_array_values;
    vector<unsigned char> b_array_values;

    // Constructors
    CDataref(string p_dr_name, int p_dr_type, int p_dr_is_writeable);   // int/float/double
    CDataref(string p_dr_name, int p_dr_type, int p_dr_is_writeable, size_t p_i_array_size);    // int array
    CDataref(string p_dr_name, int p_dr_type, int p_dr_is_writeable, size_t p_f_array_size, bool p_is_float_array); // float array
    CDataref(string p_dr_name, int p_dr_type, int p_dr_is_writeable, size_t p_b_array_size, const char* initial_value, bool p_is_byte_array);  // byte array

    // Destructor
    ~CDataref() = default;

    // Convenience Data Accessor Getters
    int getInt();
    float getFloat();
    double getDouble();
    int getIntV(int start_index, int num_elements, int *in_values);
    float getFloatV(int start_index, int num_elements, float *values);
    int getByte(int start_index, int num_elements, void *values);

    // Data Accessor Setters
    void setInt(int in_value);
    void setFloat(float inValue);
    void setDouble(double inValue);
    void setIntV(int start_index, int num_elements, int *in_values);
    void setFloatV(int start_index, int num_elements, float *in_values);
    void setByte(int start_index, int num_elements, void *in_values);


private:
    int xp_dr_type;

    // X-Plane SDK Getters
    static int readInt(void *inReadRefcon);
    static float readFloat(void *inReadRefcon);
    static double readDouble(void *inReadRefcon);
    static int readIntV(void *inReadRefcon, int *p_outValues, int p_begin_index, int p_range);
    static int readFloatV(void *inReadRefcon, float *p_outValues, int p_begin_index, int p_range);
    static int readByte(void *inReadRefcon, void *outValue, int inOffset, int inMaxBytes);

    // X-Plane SDK Setters
    static void writeInt(void *inWriteRefcon, int p_inValue);
    static void writeFloat(void *inWriteRefcon, float p_inValue);
    static void writeDouble(void *inWriteRefcon, double p_inValue);
    static void writeIntV(void *inWriteRefcon, int *p_inValues, int p_begin_index, int p_range);
    static void writeFloatV(void *inWriteRefcon, float *p_inValues, int p_begin_index, int p_range);
    static void writeByte(void *inWriteRefcon, void *inValue, int p_begin_index, int p_range);
};



#endif //CDR_H
