//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef XDR_H
#define XDR_H


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


class XDataref {
public:
    static vector<XDataref*> xp_datarefs;

    // Core info
    XPLMDataRef dr_handle = nullptr;
    string dr_name;
    int dr_type = 0;
    bool dr_is_writeable = false;
    bool get_per_flight_loop = false;

    // Value caches
    int i_value = 0;
    float f_value = 0.0f;
    double d_value = 0.0;
    vector<int> i_array_values;
    vector<float> f_array_values;
    vector<unsigned char> b_array_values;
    size_t i_array_size = 0;
    size_t f_array_size = 0;

    // Constructors
    XDataref(string name, int type, bool poll = false);

    // One-Time Universal fetch All Values for a Dataref (uses existing array size as needed)
    void fetchNow();

    // Scalar Getters
    int getInt();
    float getFloat();
    double getDouble();

    // Scalar Setters
    void setInt(int val);
    void setFloat(float val);
    void setDouble(double val);

    // Array Getters
    int getIntV(int start, int count, int* out);
    vector<int> getIntV(int start, int count);
    float getFloatV(int start, int count, float* out);
    vector<float> getFloatV(int start, int count);
    int getByte(int start, int count, void* out);
    string getByteStr();

    // Array Setters
    void setIntV(const vector<int>& values);
    void setIntV(int start, int count, const vector<int>& values);
    void setIntV(int start, int count, std::initializer_list<int> values);
    void setFloatV(const vector<float>& values);
    void setFloatV(int start, int count, const vector<float>& values);
    void setFloatV(int start, int count, std::initializer_list<float> values);
    void setByte(int count, void* values);
    void setByteStr(const char* str);



    // Cached value access helpers (with type validation)
    int valuei() const;
    float valuef() const;
    double valued() const;
    const vector<int>& valuesi() const;
    const vector<float>& valuesf() const;
    const vector<unsigned char>& valuesb() const;
    string stringValue() const;
};





// Polling callback declarations
float XDRPollFLCB(float, float, int, void*);
void RegisterXDRFLCB();
void UnregisterXDRFLCB();


#endif // XDR_H

