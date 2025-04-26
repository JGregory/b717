// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
// •                                                       TOGA
// •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
// •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

//--[ C/C++ LIBRARY INCLUDES ]------------------------------------------------------------------------------------------
//#include <cstring>
//#include <string>
//#include <iostream>
//#include <vector>
//#include <cstdio>
//#include <cassert>

//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;
//using std::printf;


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
#include "XPLMProcessing.h"
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

/*
 * TOGA DATAREF NAME (STRING) STRUCTURE:
 * –––––––––––––––––––––––––––––––------------------------------
 *    Example: toga/b717/[CATEGORY]/[ATA GROUP]/[TYPE]/[SUFFIX]
 *
 *    [CATEGORY]
 *    ––––––––––
 *    gnrl = GENERAL
 *    acft = AIRCRAFT
 *    greq = GROUND EQUIPMENT
 *    misc = MISCELLANEOUS
 *
 *
 *    [ATA GROUP]
 *    –––––––––––
 *      AIRFRAME:
 *        agnl = AIRFRAME:GENERAL
 *        acon = AIRFRAME:AIR CONDITIONING
 *        aflt = AIRFRAME:AUTO FLIGHT
 *        comm = AIRFRAME:COMMUNICATIONS
 *        elec = AIRFRAME:ELECTRICAL
 *        eqfn = AIRFRAME:EQUIPMENT/FURNISHONGS
 *        fire = AIRFRAME:FIRE PROTERCTION
 *        fctl = AIRFRAME:FLIGHT CONTROLS
 *        fuel = AIRFRAME:FUEL
 *        hydr = AIRFRAME:HYDRAULIC
 *        icrn = AIRFRAME:ICE & RAIN PROTECTION
 *        indr = AIRFRAME:INDICATING RECORDING
 *        gear = AIRFRAME:LANDING GEAR
 *        lits = AIRFRAME:LIGHTS
 *        navg = AIRFRAME:NAVIGATION
 *        oxyg = AIRFRAME:OXYGEN
 *        pneu = AIRFRAME:PNEUMATIC
 *        vacm = AIRFRAME:VACUUM
 *        wtwa = AIRFRAME:WATER & WASTE
 *        epmc = AIRFRAME:ELECTRONIC PANELS & MULTUIPURPOSE COMPONENTS
 *        wtrb = AIRFRAME:WATER BALLAST
 *        inma = AIRFRAME:INTEGRATED MODULAR AVIONICS
 *        cabn = AIRFRAME:CABIN SYSTEMS
 *        cmnt = AIRFRAME:CENTRAL MAINTENTANCE SYSTEM
 *        info = AIRFRAME:INFORMATION SYSTEMS
 *        intg = AIRFRAME:INERT GAS SYSTEM
 *        auxp = AIRFRAME:AUXILIARY POWER
 *        cacm = AIRFRAME:CARGO AND ACCESSORY COMPARTMENTS
 *
 *      STRUCTURES:
 *        sgnl = STRUCTURES:GENERAL
 *        door = STRUCTURES:DOORS
 *        fuse = STRUCTURES:FUSELAGE
 *        nacl = STRUCTURES:NACELLES
 *        stab = STRUCTURES:STABILIZERS
 *        wndw = STRUCTURES:WINDOWS
 *        wing = STRUCTURES:WINGS
 *
 *      PROP/ROTOR:
 *        pgnl = PROP/ROTOR:GENERAL
 *        rotr = PROP/ROTOR:ROTORS
 *        rtdr = PROP/ROTOR:ROTOR DRIVES
 *        trtr = PROP/ROTOR:TAIL ROTOR
 *        trdr = PROP/ROTOR:TAIL ROTOR DRIVE
 *        blpy = PROP/ROTOR:FOlDING BLADES & TAIL PYLON
 *        rctl = PROP/ROTOR:ROTORS FLIGHT CONTROL
 *
 *      POWER PLANT:
 *        ppgl = POWER PLANT:GENERAL
 *        engn = POWER PLANT:ENGINE
 *        eflc = POWER PLANT:ENGNE FUEL & CONTROL
 *        ignt = POWER PLANT:IGNITION
 *        eair = POWER PLANT:AIR
 *        ectl = POWER PLANT:ENGINE CONTROLS
 *        eind = POWER PLANT:ENGINE INDICATING
 *        exst = POWER PLANT:EXHAUST
 *        eoil = POWER PLANT:OIL
 *        strt = POWER PLANT:STARTING
 *        turb = POWER PLANT:TURBINES
 *        winj = POWER PLANT:WATER INJECTION
 *        agbx = POWER PLANT:ACCESSORY GEAR BOXES
 *        paug = POWER PLANT:PROPULSION AUGMENTATION
 *
 *      NOT APPLICABLE:
 *       xxxx
 *
 *
 *    [TYPE]
 *     ––––––
 *     mnp = manipulator
 *     cmd = command
 *     anm = animation
 *     ann = annunciator
 *     dat = data
 *     lit = LIT value
 *     xpl = example
 *     tst = test
 *     dbg = debug
 *
 */


// Example:
CDataref b717dr_aflt_ap_hdg_knob_mnp("toga/b717/acft/aflt/mnp/ap_hdg_knob", float_cdr_T, 1);
CDataref b717dr_aflt_ap_hdg_knob_anm("toga/b717/acft/aflt/anm/ap_hdg_knob", float_cdr_T, 1);




