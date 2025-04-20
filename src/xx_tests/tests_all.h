//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
//  •                                                       TOGA
//  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
//  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


#ifndef TESTS_ALL_H
#define TESTS_ALL_H


#ifdef ENABLE_TESTS

// Master test entry point
void runAllTests();

// Command registration helpers
void registerTestCommand();
void unregisterTestCommand();

#endif



#endif //TESTS_ALL_H
