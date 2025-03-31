//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
#include <string>
#include <iostream>
#include <vector>
//#include <cstdio>
#include <cassert>

//using std::cout;
//using std::endl;
using std::string;
//using std::vector;
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
#include "cdr.h"
#include "datatypes.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


vector<CDataref *> CDataref::custom_datarefs;


// Integer/Float/Double Type Constructor
CDataref::CDataref(
    string p_dr_name,
    int p_dr_type,
    int p_dr_is_writeable
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    i_value{0},
    f_value{0},
    d_value{0}
{
    switch(p_dr_type) {
        case (int_cdr_T):
            xp_dr_type = xplmType_Int;
            break;
        case (float_cdr_T):
            xp_dr_type = xplmType_Float;
            break;
        case (double_cdr_T):
            xp_dr_type = xplmType_Double;
            break;
        default:
            assert(false && "[B717] p_dr_type is invalid");
    }
    this->dr_handle = XPLMRegisterDataAccessor(
        dr_name.data(),
        xp_dr_type, dr_is_writeable,
        readInt, writeInt,
        readFloat, writeFloat,
        readDouble, writeDouble,
        readIntV, writeIntV,
        readFloatV, writeFloatV,
        nullptr, nullptr,
        this,
        this
    );

    custom_datarefs.push_back(this);

}



// Integer Array Type Constructor
CDataref::CDataref(
    string p_dr_name,
    int p_dr_type,
    int p_dr_is_writeable,
    size_t p_i_array_size
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    i_array_values(p_i_array_size),
    xp_dr_type(xplmType_IntArray)
{

    this->dr_handle = XPLMRegisterDataAccessor(
        dr_name.data(),
        xp_dr_type, p_dr_is_writeable,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        readIntV, writeIntV,
        nullptr, nullptr,
        nullptr, nullptr,
        this,
        this
    );

    custom_datarefs.push_back(this);

}



// Float Array Type Constructor
CDataref::CDataref(
    string p_dr_name,
    int p_dr_type,
    int p_dr_is_writeable,
    size_t p_f_array_size,
    bool p_is_float_array
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    f_array_values(p_f_array_size),
    xp_dr_type(xplmType_FloatArray)
{

    this->dr_handle = XPLMRegisterDataAccessor(
        dr_name.data(),
        xp_dr_type, p_dr_is_writeable,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        readFloatV, writeFloatV,
        nullptr, nullptr,
        this,
        this
    );

    custom_datarefs.push_back(this);

}



// Byte Array Constructor
CDataref::CDataref(
    string p_dr_name,
    int p_dr_type,
    int p_dr_is_writeable,
    size_t p_b_array_size,
    const char* initial_value,
    bool p_is_byte_array
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    b_array_values(p_b_array_size, '\0'),  // Initialize with null characters
    xp_dr_type(xplmType_Data)
{

    if (initial_value) {
        strncpy(reinterpret_cast<char*>(b_array_values.data()), initial_value, p_b_array_size - 1);
        b_array_values[p_b_array_size - 1] = '\0';  // Ensure null termination
    }

    // Register the dataref with X-Plane
    this->dr_handle = XPLMRegisterDataAccessor(
        dr_name.data(),
        xp_dr_type, p_dr_is_writeable,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr,
        readByte, writeByte,  // Byte array (string) handlers
        this,
        this
    );

    // Write the initial string value to X-Plane
    XPLMSetDatab(this->dr_handle, b_array_values.data(), 0,
                 static_cast<int>(strlen(reinterpret_cast<const char*>(b_array_values.data())) + 1));

    custom_datarefs.push_back(this);

}




// XP Data Accessor Getters/Setters
int CDataref::readInt(void *inReadRefcon) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);
    return this_instance->i_value;
}

float CDataref::readFloat(void *inReadRefcon) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);
    return this_instance->f_value;
}

double CDataref::readDouble(void *inReadRefcon) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);
    return this_instance->d_value;
}

int CDataref::readIntV(void *inReadRefcon, int *p_outValues, int p_begin_index, int p_range) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);

    // If X-Plane is querying the array size, return its length
    if (p_outValues == nullptr) {
        return static_cast<int>(this_instance->i_array_values.size());
    }

    // Ensure range is within bounds
    int array_size = static_cast<int>(this_instance->i_array_values.size());
    if (p_begin_index >= array_size || p_range <= 0) {
        return 0;
    }

    int copied_elements = 0;
    for (int i = 0; i < p_range && (p_begin_index + i) < array_size; ++i) {
        p_outValues[i] = this_instance->i_array_values[p_begin_index + i];
        copied_elements++;
    }

    return copied_elements;
}

int CDataref::readFloatV(void *inReadRefcon, float *p_outValues, int p_begin_index, int p_range) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);

    // Return array size when p_outValues is nullptr
    if (p_outValues == nullptr) {
        return static_cast<int>(this_instance->f_array_values.size());
    }

    // Ensure range is within bounds
    int array_size = static_cast<int>(this_instance->f_array_values.size());
    if (p_begin_index >= array_size || p_range <= 0) {
        return 0;
    }

    int copied_elements = 0;
    for (int i = 0; i < p_range && (p_begin_index + i) < array_size; ++i) {
        p_outValues[i] = this_instance->f_array_values[p_begin_index + i];
        copied_elements++;
    }

    return copied_elements;
}

int CDataref::readByte(void *inReadRefcon, void *outValue, int inOffset, int inMaxBytes) {
    auto *this_instance = static_cast<CDataref*>(inReadRefcon);

    // Return size if X-Plane requests array length
    if (outValue == nullptr) {
        return static_cast<int>(this_instance->b_array_values.size());
    }

    // Ensure range is within bounds
    int array_size = static_cast<int>(this_instance->b_array_values.size());
    if (inOffset >= array_size || inMaxBytes <= 0) {
        return 0;
    }

    int copied_elements = 0;
    //unsigned char *byte_out = static_cast<unsigned char *>(outValue);
    auto byte_out = static_cast<unsigned char *>(outValue);
    for (int i = 0; i < inMaxBytes && (inOffset + i) < array_size; ++i) {
        byte_out[i] = this_instance->b_array_values[inOffset + i];
        copied_elements++;
    }

    return copied_elements;
}







// CUSTOM DATAREF READ/WRITE CALLBACKS
void CDataref::writeInt(void *inWriteRefcon, int p_inValue) {
    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);
    this_instance->i_value = p_inValue;
}

void CDataref::writeFloat(void *inWriteRefcon, float p_inValue) {
    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);
    this_instance->f_value = p_inValue;
}

void CDataref::writeDouble(void *inWriteRefcon, double p_inValue) {
    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);
    this_instance->d_value = p_inValue;
}

void CDataref::writeIntV(void *inWriteRefcon, int *p_inValues, int p_begin_index, int p_range) {

    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);

    if (p_begin_index + p_range < this_instance->i_array_values.size()) {
        for (int i = p_begin_index; i < p_range; ++i) {
            this_instance->i_array_values[i] = p_inValues[i];
        }
    }

}

void CDataref::writeFloatV(void *inWriteRefcon, float *p_inValues, int p_begin_index, int p_range) {

    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);

    if (p_begin_index + p_range < this_instance->f_array_values.size()) {
        for (int i = p_begin_index; i < p_range; ++i) {
            this_instance->f_array_values[i] = p_inValues[i];
        }
    }

}

void CDataref::writeByte(void *inWriteRefcon, void *inValue, int p_begin_index, int p_range) {
    auto *this_instance = static_cast<CDataref*>(inWriteRefcon);

    // Ensure range is within bounds
    int array_size = static_cast<int>(this_instance->b_array_values.size());
    if (p_begin_index >= array_size || p_range <= 0) {
        return;
    }

    //unsigned char *byte_in = static_cast<unsigned char *>(inValue);
    auto byte_in = static_cast<unsigned char *>(inValue);
    for (int i = 0; i < p_range && (p_begin_index + i) < array_size; ++i) {
        this_instance->b_array_values[p_begin_index + i] = byte_in[i];
    }

    // Ensure null termination
    this_instance->b_array_values[p_begin_index + p_range - 1] = '\0';
}









// CONVENIENCE DATA ACCESSOR GETTERS/SETTERS
int	CDataref::getInt() {
    return XPLMGetDatai(dr_handle);
}

float CDataref::getFloat() {
    return XPLMGetDataf(dr_handle);
}

double CDataref::getDouble() {
    return XPLMGetDatad(dr_handle);
}

int CDataref::getIntV(int start_index, int num_elements, int *values) {
    return XPLMGetDatavi(dr_handle, values, start_index, num_elements);
}

float CDataref::getFloatV(int start_index, int num_elements, float *values) {
    return XPLMGetDatavf(dr_handle, values, start_index, num_elements); // NOLINT(*-narrowing-conversions)
}

int CDataref::getByte(int start_index, int num_elements, void *values) {
    return XPLMGetDatab(dr_handle, values, start_index, num_elements);
}




void CDataref::setInt(int inValue){
    XPLMSetDatai(dr_handle, inValue);
}

void CDataref::setFloat(float in_value) {
    XPLMSetDataf(dr_handle, in_value);
}

void CDataref::setDouble(double in_value) {
    XPLMSetDatad(dr_handle, in_value);
}

void CDataref::setIntV(int start_index, int num_elements, int *in_values) {
    // Update internal array first
    if (start_index + num_elements <= i_array_values.size()) {
        for (int i = 0; i < num_elements; ++i) {
            i_array_values[start_index + i] = in_values[i];
        }
    }

    // Push updated values to X-Plane
    XPLMSetDatavi(dr_handle, i_array_values.data(), 0, static_cast<int>(i_array_values.size()));
}


void CDataref::setFloatV(int start_index, int num_elements, float *in_values) {
    // Update internal array first
    if (start_index + num_elements <= f_array_values.size()) {
        for (int i = 0; i < num_elements; ++i) {
            f_array_values[start_index + i] = in_values[i];
        }
    }

    // Push updated values to X-Plane
    XPLMSetDatavf(dr_handle, f_array_values.data(), 0, static_cast<int>(f_array_values.size()));
}


void CDataref::setByte(int start_index, int num_elements, void *in_values) {
    XPLMSetDatab(dr_handle, in_values, start_index, num_elements);
}

