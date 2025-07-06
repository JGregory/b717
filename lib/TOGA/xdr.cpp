// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMUtilities.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "xdr.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================


std::vector<XDataref*> XDataref::xp_datarefs;


XDataref::XDataref(std::string name, int type, bool poll)
    :
    dr_name(std::move(name)),
    dr_type(type),
    get_per_flight_loop(poll)
{
    dr_handle = XPLMFindDataRef(dr_name.c_str());
    if (!dr_handle) {
        XPLMDebugString(("[xdr] DataRef not found: " + dr_name + "\n").c_str());
        return;
    }
    dr_is_writeable = XPLMCanWriteDataRef(dr_handle);

    // Dynamically infer array size if needed
    if (dr_type == xplmType_IntArray) {
        i_array_size = XPLMGetDatavi(dr_handle, nullptr, 0, 0);
        i_array_values.resize(i_array_size);
    } else if (dr_type == xplmType_FloatArray) {
        f_array_size = XPLMGetDatavf(dr_handle, nullptr, 0, 0);
        f_array_values.resize(f_array_size);
    } else if (dr_type == xplmType_Data) {
        size_t data_size = XPLMGetDatab(dr_handle, nullptr, 0, 0);
        b_array_values.resize(data_size);
    }

    if (poll) xp_datarefs.push_back(this);
}




void XDataref::fetchNow() {
    if (!dr_handle) return;

    switch (dr_type) {
    case xplmType_Int:
        i_value = XPLMGetDatai(dr_handle);
        break;
    case xplmType_Float:
        f_value = XPLMGetDataf(dr_handle);
        break;
    case xplmType_Double:
        d_value = XPLMGetDatad(dr_handle);
        break;
    case xplmType_IntArray:
        XPLMGetDatavi(dr_handle, i_array_values.data(), 0, static_cast<int>(i_array_size));
        break;
    case xplmType_FloatArray:
        XPLMGetDatavf(dr_handle, f_array_values.data(), 0, static_cast<int>(f_array_size));
        break;
    case xplmType_Data:
        XPLMGetDatab(dr_handle, b_array_values.data(), 0, static_cast<int>(b_array_values.size()));
        break;
    default:
        break;
    }
}




int XDataref::getInt() { return XPLMGetDatai(dr_handle); }
float XDataref::getFloat() { return XPLMGetDataf(dr_handle); }
double XDataref::getDouble() { return XPLMGetDatad(dr_handle); }

int XDataref::getIntV(int start, int count, int* out) {
    return XPLMGetDatavi(dr_handle, out, start, count);
}

std::vector<int> XDataref::getIntV(int start, int count) {
    std::vector<int> result(count, 0);
    int read = XPLMGetDatavi(dr_handle, result.data(), start, count);
    result.resize(read);
    return result;
}

float XDataref::getFloatV(int start, int count, float* out) {
    return XPLMGetDatavf(dr_handle, out, start, count);
}

std::vector<float> XDataref::getFloatV(int start, int count) {
    std::vector<float> result(count, 0.0f);
    int read = XPLMGetDatavf(dr_handle, result.data(), start, count);
    result.resize(read);
    return result;
}

int XDataref::getByte(int start, int count, void* out) {
    return XPLMGetDatab(dr_handle, out, start, count);
}

std::string XDataref::getByteStr() {
    int size = XPLMGetDatab(dr_handle, nullptr, 0, 0);
    if (size <= 0) return "";
    std::vector<unsigned char> buf(size, '\0');
    XPLMGetDatab(dr_handle, buf.data(), 0, size);
    buf[size - 1] = '\0';
    return std::string(reinterpret_cast<char*>(buf.data()));
}



void XDataref::setInt(int val) {
    if (!dr_is_writeable) return;
    i_value = val;
    XPLMSetDatai(dr_handle, val);
}

void XDataref::setFloat(float val) {
    if (!dr_is_writeable) return;
    f_value = val;
    XPLMSetDataf(dr_handle, val);
}

void XDataref::setDouble(double val) {
    if (!dr_is_writeable) return;
    d_value = val;
    XPLMSetDatad(dr_handle, val);
}

void XDataref::setIntV(const std::vector<int>& values) {
    if (!dr_is_writeable) return;
    int count = std::min(static_cast<int>(values.size()), static_cast<int>(i_array_size));
    for (int i = 0; i < count; ++i) i_array_values[i] = values[i];
    XPLMSetDatavi(dr_handle, const_cast<int*>(values.data()), 0, count);
}

void XDataref::setIntV(int start, int count, const std::vector<int>& values) {
    if (!dr_is_writeable || start < 0 || count <= 0 || static_cast<size_t>(start) >= i_array_size) return;
    int write_count = std::min({ count, static_cast<int>(values.size()), static_cast<int>(i_array_size - start) });
    for (int i = 0; i < write_count; ++i) i_array_values[start + i] = values[i];
    XPLMSetDatavi(dr_handle, const_cast<int*>(values.data()), start, write_count);
}

void XDataref::setIntV(int start, int count, std::initializer_list<int> values) {
    if (!dr_is_writeable || start < 0 || count <= 0 || static_cast<size_t>(start) >= i_array_size) return;
    int write_count = std::min({ count, static_cast<int>(values.size()), static_cast<int>(i_array_size - start) });
    auto it = values.begin();
    for (int i = 0; i < write_count; ++i, ++it) i_array_values[start + i] = *it;
    XPLMSetDatavi(dr_handle, const_cast<int*>(values.begin()), start, write_count);
}

void XDataref::setFloatV(const std::vector<float>& values) {
    if (!dr_is_writeable) return;
    int count = std::min(static_cast<int>(values.size()), static_cast<int>(f_array_size));
    for (int i = 0; i < count; ++i) f_array_values[i] = values[i];
    XPLMSetDatavf(dr_handle, const_cast<float*>(values.data()), 0, count);
}

void XDataref::setFloatV(int start, int count, const std::vector<float>& values) {
    if (!dr_is_writeable || start < 0 || count <= 0 || static_cast<size_t>(start) >= f_array_size) return;
    int write_count = std::min({ count, static_cast<int>(values.size()), static_cast<int>(f_array_size - start) });
    for (int i = 0; i < write_count; ++i) f_array_values[start + i] = values[i];
    XPLMSetDatavf(dr_handle, const_cast<float*>(values.data()), start, write_count);
}

void XDataref::setFloatV(int start, int count, std::initializer_list<float> values) {
    if (!dr_is_writeable || start < 0 || count <= 0 || static_cast<size_t>(start) >= f_array_size) return;
    int write_count = std::min({ count, static_cast<int>(values.size()), static_cast<int>(f_array_size - start) });
    auto it = values.begin();
    for (int i = 0; i < write_count; ++i, ++it) f_array_values[start + i] = *it;
    XPLMSetDatavf(dr_handle, const_cast<float*>(values.begin()), start, write_count);
}

void XDataref::setByte(int count, void* values) {
    if (!dr_is_writeable || count <= 0 || count >= static_cast<int>(b_array_values.size())) return;
    auto in = static_cast<unsigned char*>(values);
    std::fill(b_array_values.begin(), b_array_values.end(), '\0');
    for (int i = 0; i < count; ++i) b_array_values[i] = in[i];
    b_array_values[count] = '\0';
    XPLMSetDatab(dr_handle, b_array_values.data(), 0, count + 1);
}

void XDataref::setByteStr(const char* str) {
    if (!dr_is_writeable || !str) return;
    int len = static_cast<int>(strlen(str));
    setByte(len, (void*)str);
}



// Value access helpers
int XDataref::valuei() const {
    if (dr_type != xplmType_Int)
        //std::printf("dr_name: %s", this->dr_name.c_str());
        throw std::runtime_error("XDataref::valuei() called on non-int type");
    return i_value;
}
float XDataref::valuef() const {
    if (dr_type != xplmType_Float)
        throw std::runtime_error("XDataref::valuef() called on non-float type");
    return f_value;
}
double XDataref::valued() const {
    if (dr_type != xplmType_Double)
        throw std::runtime_error("XDataref::valued() called on non-double type");
    return d_value;
}

const std::vector<int>& XDataref::valuesi() const {
    if (dr_type != xplmType_IntArray)
        throw std::runtime_error("XDataref::valuesi() called on non-int array type");
    return i_array_values;
}
const std::vector<float>& XDataref::valuesf() const {
    if (dr_type != xplmType_FloatArray)
        throw std::runtime_error("XDataref::valuesf() called on non-float array type");
    return f_array_values;
}
const std::vector<unsigned char>& XDataref::valuesb() const {
    if (dr_type != xplmType_Data)
        throw std::runtime_error("XDataref::valuesb() called on non-byte dataref type");
    return b_array_values;
}

std::string XDataref::stringValue() const {
    if (dr_type != xplmType_Data)
        throw std::runtime_error("XDataref::stringValue() called on non-data type");
    return std::string(reinterpret_cast<const char*>(b_array_values.data()));
}



// Flight loop callback to poll values into XDataref objects
float XDRPollFLCB(float, float, int, void*) {
    for (XDataref* xdr : XDataref::xp_datarefs) {
        if (!xdr || !xdr->dr_handle || !xdr->get_per_flight_loop) continue;

        switch (xdr->dr_type) {
            case xplmType_Int:
                xdr->i_value = XPLMGetDatai(xdr->dr_handle);
                break;
            case xplmType_Float:
                xdr->f_value = XPLMGetDataf(xdr->dr_handle);
                break;
            case xplmType_Double:
                xdr->d_value = XPLMGetDatad(xdr->dr_handle);
                break;
            case xplmType_IntArray:
                XPLMGetDatavi(xdr->dr_handle, xdr->i_array_values.data(), 0, static_cast<int>(xdr->i_array_size));
                break;
            case xplmType_FloatArray:
                XPLMGetDatavf(xdr->dr_handle, xdr->f_array_values.data(), 0, static_cast<int>(xdr->f_array_size));
                break;
            case xplmType_Data:
                XPLMGetDatab(xdr->dr_handle, xdr->b_array_values.data(), 0, static_cast<int>(xdr->b_array_values.size()));
                break;
            default:
                break;
        }
    }
    return -1.0f; // run every frame
}







void RegisterXDRFLCB(void){

    XPLMDebugString("TK:  Registering XDR module FLCB\n");
    XPLMRegisterFlightLoopCallback(XDRPollFLCB,    -1,     NULL);
}

void UnregisterXDRFLCB(void){

    XPLMDebugString("TK:  Unregistering XDR module FLCB\n");
    XPLMUnregisterFlightLoopCallback(XDRPollFLCB,	NULL);
}





