//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

/*

************************ EXAMPLES ONLY - DO NOT UNCOMMENT - NOT MEANT FOR LIVE PRODUCTION USE **************************

CDataref toga_cdr_test_int("toga/b717/misc/xxxx/tst/cdr_test_int", int_cdr_T, 1);
CDataref toga_cdr_test_float("toga/b717/misc/xxxx/tst/cdr_test_float", float_cdr_T, 1);
CDataref toga_cdr_test_dbl("toga/b717/misc/xxxx/tst/cdr_test_dbl", double_cdr_T, 1);
CDataref toga_cdr_test_intV("toga/b717/misc/xxxx/tst/cdr_test_intV", intv_cdr_T, 8, 1);
CDataref toga_cdr_test_floatV("toga/b717/misc/xxxx/tst/cdr_test_floatV", floatv_cdr_T, 5, true, 1);
CDataref toga_cdr_test_floatV2("toga/b717/misc/xxxx/tst/cdr_test_floatV2", floatv_cdr_T, 6, true, 1);
CDataref toga_cdr_test_byteV("toga/b717/misc/xxxx/tst/cdr_test_byteV", bytev_cdr_T, 30, "custom test byte Dataref", true, 1);
CDataref toga_cdr_test_byteStr("toga/b717/misc/xxxx/tst/cdr_test_byteStr", bytev_cdr_T, 40, "custom test byte Dataref (String)", true, 1);


--[ Convenience Getters ]--

-- Integer
int x = toga_cdr_test_int.getInt()
int x = toga_cdr_test_int.valuei()

-- Float
float x = toga_cdr_test_float.getFloat()
float x = toga_cdr_test_float.valuef()

-- Double
long x = toga_cdr_test_dbl.getDouble()
long x = toga_cdr_test_dbl.valued()

-- Integer Array
std::vector<int> x = toga_cdr_test_intV.getIntV(0, 4)
int x = toga_cdr_test_intV.valuesi()[0]

-- Float Array
std::vector<float> x = toga_cdr_test_floatV.getFloatV(0, 3)
float x = toga_cdr_test_floatV.valuesf()[3]

-- Byte Array (String)
string x = toga_cdr_test_byteV.getByteStr() (test_string.c_str())
string x = toga_cdr_test_byteV.stringValue().c_str()



--[ Convenience Setters ]--

-- Integer
toga_cdr_test_int.setInt(7)

-- Float
toga_cdr_test_float.setFloat(20.53689)

-- Double
toga_cdr_test_dbl.setDouble(9.489768435468)

-- Integer Array
std::vector<int> values = {10, 20, 30, 40, 50, 60}
toga_cdr_test_intV.setIntV(values)

std::vector<int> values2 = {101, 102};
toga_cdr_test_intV.setIntV(2, 2, values2)

toga_cdr_test_intV.setIntV({1, 2, 3, 4, 5})

toga_cdr_test_intV.setIntV(1, 3, {7, 8, 9})

-- Float Array
std::vector<float> temps = {21.5f, 22.0f, 22.7f, 21.2, 20.3}
toga_cdr_test_floatV.setFloatV(temps)

std::vector<float> updates = {99.1f, 100.2f}
toga_cdr_test_floatV.setFloatV(4, 2, updates)

toga_cdr_test_floatV.setFloatV({3.14f, 2.71f, 1.41f})

toga_cdr_test_floatV.setFloatV(0, 2, {5.5f, 6.6f})

std::vector<float> animation_values(6)
for (int i = 0; i < 6; ++i) {
    animation_values[i] = sin(XPLMGetElapsedTime()) * 10.0f + i
}
toga_cdr_test_floatV2.setFloatV(animation_values)

-- Byte Array (String)
char byte_test[] = "xxxxx"
toga_cdr_test_byteV.setByte(strlen(byte_test), byte_test)

toga_cdr_test_byteStr.setByteStr("test byte string")

*/