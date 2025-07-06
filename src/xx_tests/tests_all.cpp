// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
#include <cstdio>


//--[ X-PLANE SDK LIBRARY HEADERS ]-------------------------------------------------------------------------------------
#include "XPLMUtilities.h"


//--[ IMGUI LIBRARY HEADER INCLUDES ]-----------------------------------------------------------------------------------


//--[ IMGUI XP IMPLEMENTATION HEADERS ]------------------------------------------------------------------------------------


//--[ TOGA LIBRARY HEADERS ]--------------------------------------------------------------------------------------------
#include "cdr.h"
#include "xdr.h"


//--[ AIRCRAFT HEADERS ]------------------------------------------------------------------------------------------------


//--[ TEST HEADERS ]----------------------------------------------------------------------------------------------------
#include "tests_cdatarefs.h"
#include "tests_xdatarefs.h"
#include "tests_all.h"


//--[ EXAMPLES HEADERS ]------------------------------------------------------------------------------------------------



//======================================================================================================================



#ifdef ENABLE_TESTS

static XPLMCommandRef gRunAllTestsCmd = nullptr;

void runAllTests() {
    std::printf("\n");
    std::printf("[=================================================]\n");
    std::printf("All registered tests in progress...\n");
    run_cdr_tests();
    run_xdr_tests();

    std::printf("\nAll registered tests completed.\n");
    std::printf("[=================================================]\n");
    std::printf("\n");
}

int run_all_tests_cb(XPLMCommandRef, XPLMCommandPhase phase, void*) {
    if (phase == xplm_CommandBegin) {
        runAllTests();
    }
    return 1;
}

void registerTestCommand() {
    gRunAllTestsCmd = XPLMCreateCommand("toga/gnrl/xxxx/cmd/run_all_tests", "Run all tests");
    XPLMRegisterCommandHandler(gRunAllTestsCmd, run_all_tests_cb, 1, nullptr);
}

void unregisterTestCommand() {
    if (gRunAllTestsCmd) {
        XPLMUnregisterCommandHandler(gRunAllTestsCmd, run_all_tests_cb, 1, nullptr);
        gRunAllTestsCmd = nullptr;
    }
}

#endif
