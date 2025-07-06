// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#ifndef XDR_H
#define XDR_H


//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <string>
#include <vector>


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
#include "XPLMDataAccess.h"



//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


class XDataref {
public:
    static std::vector<XDataref*> xp_datarefs;

    // Core info
    XPLMDataRef dr_handle = nullptr;
    std::string dr_name;
    int dr_type = 0;
    bool dr_is_writeable = false;
    bool get_per_flight_loop = false;

    // Value caches
    int i_value = 0;
    float f_value = 0.0f;
    double d_value = 0.0;
    std::vector<int> i_array_values;
    std::vector<float> f_array_values;
    std::vector<unsigned char> b_array_values;
    size_t i_array_size = 0;
    size_t f_array_size = 0;

    // Constructors
    XDataref(std::string name, int type, bool poll = false);

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
    std::vector<int> getIntV(int start, int count);
    float getFloatV(int start, int count, float* out);
    std::vector<float> getFloatV(int start, int count);
    int getByte(int start, int count, void* out);
    std::string getByteStr();

    // Array Setters
    void setIntV(const std::vector<int>& values);
    void setIntV(int start, int count, const std::vector<int>& values);
    void setIntV(int start, int count, std::initializer_list<int> values);
    void setFloatV(const std::vector<float>& values);
    void setFloatV(int start, int count, const std::vector<float>& values);
    void setFloatV(int start, int count, std::initializer_list<float> values);
    void setByte(int count, void* values);
    void setByteStr(const char* str);



    // Cached value access helpers (with type validation)
    int valuei() const;
    float valuef() const;
    double valued() const;
    const std::vector<int>& valuesi() const;
    const std::vector<float>& valuesf() const;
    const std::vector<unsigned char>& valuesb() const;
    std::string stringValue() const;
};





// Polling callback declarations
float XDRPollFLCB(float, float, int, void*);
void RegisterXDRFLCB();
void UnregisterXDRFLCB();


#endif // XDR_H

