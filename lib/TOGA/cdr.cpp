//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

//using std::cout;
//using std::endl;
using std::string;
using std::vector;
using std::printf;


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
    size_t p_i_array_size,
    int p_dr_is_writeable
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    i_array_capacity(p_i_array_size),
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
    size_t p_f_array_size,
    bool p_is_float_array,
    int p_dr_is_writeable
) :
    dr_name{p_dr_name},
    dr_type{p_dr_type},
    dr_is_writeable{p_dr_is_writeable},
    f_array_capacity(p_f_array_size),
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
    size_t p_b_array_size,
    const char* initial_value,
    bool p_is_byte_array,
    int p_dr_is_writeable
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

std::vector<int> CDataref::getIntV(int start_index, int num_elements) {
    std::vector<int> result(num_elements, 0);
    int read_count = XPLMGetDatavi(dr_handle, result.data(), start_index, num_elements);
    result.resize(read_count); // In case fewer values were actually read
    return result;
}

float CDataref::getFloatV(int start_index, int num_elements, float *values) {
    return XPLMGetDatavf(dr_handle, values, start_index, num_elements); // NOLINT(*-narrowing-conversions)
}

std::vector<float> CDataref::getFloatV(int start_index, int num_elements) {
    std::vector<float> result(num_elements, 0.0f);
    int read_count = XPLMGetDatavf(dr_handle, result.data(), start_index, num_elements);
    result.resize(read_count); // In case fewer values were actually read
    return result;
}


int CDataref::getByte(int start_index, int num_elements, void *values) {
    return XPLMGetDatab(dr_handle, values, start_index, num_elements);
}

std::string CDataref::getByteStr() {
    // Get current dataref array size
    int array_size = static_cast<int>(XPLMGetDatab(dr_handle, nullptr, 0, 0));
    if (array_size <= 0) {
        return "";
    }

    std::vector<unsigned char> buffer(array_size, '\0');

    // Read actual contents from the dataref
    XPLMGetDatab(dr_handle, buffer.data(), 0, array_size);

    // Ensure null-termination
    buffer[array_size - 1] = '\0';

    return std::string(reinterpret_cast<char*>(buffer.data()));
}




void CDataref::setInt(int inValue) {
    if (!dr_is_writeable) return;
    i_value = inValue;
    XPLMSetDatai(dr_handle, inValue);
}

void CDataref::setFloat(float inValue) {
    if (!dr_is_writeable) return;
    f_value = inValue;
    XPLMSetDataf(dr_handle, inValue);
}

void CDataref::setDouble(double inValue) {
    if (!dr_is_writeable) return;
    d_value = inValue;
    XPLMSetDatad(dr_handle, inValue);
}

void CDataref::setIntV(const std::vector<int>& values) {
    if (!dr_is_writeable) return;
    int write_count = std::min(static_cast<int>(values.size()), static_cast<int>(i_array_capacity));

    for (int i = 0; i < write_count; ++i) {
        i_array_values[i] = values[i];
    }

    XPLMSetDatavi(dr_handle, const_cast<int*>(values.data()), 0, write_count);
}

void CDataref::setIntV(int start_index, int num_elements, const std::vector<int>& values) {
    if (!dr_is_writeable) return;
    if (start_index < 0 || num_elements <= 0 || static_cast<size_t>(start_index) >= i_array_capacity) {
        return;
    }

    int write_count = std::min({
        num_elements,
        static_cast<int>(values.size()),
        static_cast<int>(i_array_capacity - start_index)
    });

    for (int i = 0; i < write_count; ++i) {
        i_array_values[start_index + i] = values[i];
    }

    assert(write_count <= static_cast<int>(values.size()));

    XPLMSetDatavi(dr_handle, const_cast<int*>(values.data()), start_index, write_count);
}

void CDataref::setIntV(int start_index, int num_elements, std::initializer_list<int> values) {
    if (!dr_is_writeable) return;
    if (start_index < 0 || num_elements <= 0 || static_cast<size_t>(start_index) >= i_array_capacity) {
        return;
    }

    int write_count = std::min({
        num_elements,
        static_cast<int>(values.size()),
        static_cast<int>(i_array_capacity - start_index)
    });

    auto it = values.begin();
    for (int i = 0; i < write_count; ++i, ++it) {
        i_array_values[start_index + i] = *it;
    }

    XPLMSetDatavi(dr_handle, const_cast<int*>(values.begin()), start_index, write_count);
}

void CDataref::setFloatV(const std::vector<float>& values) {
    if (!dr_is_writeable) return;
    int write_count = std::min(static_cast<int>(values.size()), static_cast<int>(f_array_capacity));

    for (int i = 0; i < write_count; ++i) {
        f_array_values[i] = values[i];
    }

    XPLMSetDatavf(dr_handle, const_cast<float*>(values.data()), 0, write_count);
}

void CDataref::setFloatV(int start_index, int num_elements, const std::vector<float>& values) {
    if (!dr_is_writeable) return;
    if (start_index < 0 || num_elements <= 0 || static_cast<size_t>(start_index) >= f_array_capacity) {
        return;
    }

    int write_count = std::min({
        num_elements,
        static_cast<int>(values.size()),
        static_cast<int>(f_array_capacity - start_index)
    });

    for (int i = 0; i < write_count; ++i) {
        f_array_values[start_index + i] = values[i];
    }

    assert(write_count <= static_cast<int>(values.size()));

    XPLMSetDatavf(dr_handle, const_cast<float*>(values.data()), start_index, write_count);
}

void CDataref::setFloatV(int start_index, int num_elements, std::initializer_list<float> values) {
    if (!dr_is_writeable) return;
    if (start_index < 0 || num_elements <= 0 || static_cast<size_t>(start_index) >= f_array_capacity) {
        return;
    }

    int write_count = std::min({
        num_elements,
        static_cast<int>(values.size()),
        static_cast<int>(f_array_capacity - start_index)
    });

    auto it = values.begin();
    for (int i = 0; i < write_count; ++i, ++it) {
        f_array_values[start_index + i] = *it;
    }

    XPLMSetDatavf(dr_handle, const_cast<float*>(values.begin()), start_index, write_count);
}

void CDataref::setByte(int num_elements, void *in_values) {
    if (!dr_is_writeable) return;
    int array_size = static_cast<int>(b_array_values.size());

    if (num_elements <= 0 || num_elements >= array_size) {
        return; // Prevent overflow and invalid inputs
    }

    auto byte_in = static_cast<unsigned char *>(in_values);

    // Clear entire buffer
    std::fill(b_array_values.begin(), b_array_values.end(), '\0');

    // Copy new bytes
    for (int i = 0; i < num_elements; ++i) {
        b_array_values[i] = byte_in[i];
    }

    // Null-terminate immediately after content
    b_array_values[num_elements] = '\0';

    // Push updated buffer to X-Plane
    XPLMSetDatab(dr_handle, b_array_values.data(), 0, num_elements + 1);
}

void CDataref::setByteStr(const char* str) {
    if (!dr_is_writeable || !str) return;
    if (!str) return;

    int len = static_cast<int>(strlen(str));
    setByte(len, (void*)str); // Use full-replacement version of setByte
}






// Examples
/*













*/
