# ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
# •                                                       TOGA
# •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
# ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set_target_properties( PROPERTIES
        C_STANDARD "11" CXX_STANDARD "20")

# PROJECT NAME
project(b717)



# ENABLE OPTIONAL TEST HARNESS
# Leave Option set to "ON"
# See TestingReadMe.md to set up Clion for testing
# Once setup you can toggle testing on and off by selecting DEBUG or RELEASE in Clion
option(ENABLE_TESTS "Enable unit testing support" ON)

if(ENABLE_TESTS)
    message(STATUS "Building with ENABLE_TESTS")
    add_definitions(-DENABLE_TESTS)
endif()



# FLAGS FOR COPYING PLUGIN TO LOCAL ACF PLUGIN DIRECTORY
set(LOCAL_XP 1)


# PLUGIN VERSION
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
configure_file (lib/TOGA/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/lib/TOGA/version.h @ONLY)
message(${PROJECT_NAME} "v" ${PROJECT_VERSION})


# SET PATH TO ACF PLUGIN DIRECTORY
file(READ acf_path.txt ACF_DIRECTORY)


# PLATFORM CONFIGURATION
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
else()
    set(USE_VMPROTECT 1)
endif()




# PROJECT LIBRARIES AND FILES
set(TOGA_LIB_DIR lib/TOGA)
set(TOGA_LIB
        ${TOGA_LIB_DIR}/cdr.cpp
        ${TOGA_LIB_DIR}/cdr.h
        ${TOGA_LIB_DIR}/datatypes.h
        ${TOGA_LIB_DIR}/debug_flag.cpp
        ${TOGA_LIB_DIR}/debug_flag.h
        ${TOGA_LIB_DIR}/version.h
        ${TOGA_LIB_DIR}/xdr.cpp
        ${TOGA_LIB_DIR}/xdr.h
)

set(SRC_DIR src/)
set(SRC
        ${SRC_DIR}/02_xdatarefs/xdatarefs.cpp
        ${SRC_DIR}/02_xdatarefs/xdatarefs.h
        ${SRC_DIR}/04_cdatarefs/cdatarefs.cpp
        ${SRC_DIR}/04_cdatarefs/cdatarefs.h
        ${SRC_DIR}/main.cpp
)

set(ALL_SRC
        ${TOGA_LIB}
        ${SRC}
)

# APPEND TEST FILES ONLY IF ENABLE_TESTS IS ON in CMake
if(ENABLE_TESTS)
    list(APPEND ALL_SRC
            ${SRC_DIR}/xx_tests/tests_all.cpp
            ${SRC_DIR}/xx_tests/tests_cdatarefs.cpp
            ${SRC_DIR}/xx_tests/tests_xdatarefs.cpp
    )
endif()

add_library(${CMAKE_PROJECT_NAME} SHARED ${ALL_SRC})

# IMGUI CORE LIBRARY
set(IMGUI_LIB_DIR lib/IMGUI/)
add_library(IMGUI STATIC
        ${IMGUI_LIB_DIR}/imgui.cpp
        ${IMGUI_LIB_DIR}/imgui_draw.cpp
        ${IMGUI_LIB_DIR}/imgui_widgets.cpp
        ${IMGUI_LIB_DIR}/imgui_tables.cpp
        ${IMGUI_LIB_DIR}/backends/imgui_impl_opengl2.cpp
)






# DIRECTORIES
include_directories(
        ${TOGA_LIB_DIR}
        ${SRC_DIR}/02_xdatarefs
        ${SRC_DIR}/04_cdatarefs
        ${SRC_DIR}/06_xcommands
        ${SRC_DIR}/08_ccommands
        ${SRC_DIR}/20_airframe_systems
        ${SRC_DIR}/20_airframe_systems/00_general
        ${SRC_DIR}/20_airframe_systems/21_air_conditioning
        ${SRC_DIR}/20_airframe_systems/22_auto_flight
        ${SRC_DIR}/20_airframe_systems/23_communications
        ${SRC_DIR}/20_airframe_systems/24_electrical
        ${SRC_DIR}/20_airframe_systems/25_equip_furnishings
        ${SRC_DIR}/20_airframe_systems/26_fire_protection
        ${SRC_DIR}/20_airframe_systems/27_flight_controls
        ${SRC_DIR}/20_airframe_systems/28_fuel
        ${SRC_DIR}/20_airframe_systems/29_hydraulic
        ${SRC_DIR}/20_airframe_systems/30_ice_rain_protection
        ${SRC_DIR}/20_airframe_systems/31_indicating_recording
        ${SRC_DIR}/20_airframe_systems/32_landing_gear
        ${SRC_DIR}/20_airframe_systems/33_lights
        ${SRC_DIR}/20_airframe_systems/34_navigation
        ${SRC_DIR}/20_airframe_systems/35_oxygen
        ${SRC_DIR}/20_airframe_systems/36_pneumatic
        ${SRC_DIR}/20_airframe_systems/37_vacuum
        ${SRC_DIR}/20_airframe_systems/38_water_waste
        ${SRC_DIR}/20_airframe_systems/39_electronic_pnls & multipurp_comp
        ${SRC_DIR}/20_airframe_systems/41_water_ballast
        ${SRC_DIR}/20_airframe_systems/42_integrated_modular_avionics
        ${SRC_DIR}/20_airframe_systems/44_cabin_systems
        ${SRC_DIR}/20_airframe_systems/45_central_maint_system
        ${SRC_DIR}/20_airframe_systems/46_information_sys
        ${SRC_DIR}/20_airframe_systems/47_inert_gas_system
        ${SRC_DIR}/20_airframe_systems/49_airborne_auxiliary_power
        ${SRC_DIR}/20_airframe_systems/50_cargo_and_accy_compartments
        ${SRC_DIR}/51_structures/00_general
        ${SRC_DIR}/51_structures/52_doors
        ${SRC_DIR}/51_structures/53_fuselage
        ${SRC_DIR}/51_structures/54_nacelles_pylons
        ${SRC_DIR}/51_structures/55_stabliizers
        ${SRC_DIR}/51_structures/56_windows
        ${SRC_DIR}/51_structures/57_wings
        ${SRC_DIR}/60_prop_rotor
        ${SRC_DIR}/60_prop_rotor/00_general
        ${SRC_DIR}/60_prop_rotor/62_rotors
        ${SRC_DIR}/60_prop_rotor/63_rotor_drives
        ${SRC_DIR}/60_prop_rotor/64_tail_rotor
        ${SRC_DIR}/60_prop_rotor/65_tail_rotor_drive
        ${SRC_DIR}/60_prop_rotor/66_folding_blades_&_tail_pylon
        ${SRC_DIR}/60_prop_rotor/67_rotors_flight_control
        ${SRC_DIR}/70_power_plant
        ${SRC_DIR}/70_power_plant/00_general
        ${SRC_DIR}/70_power_plant/72_engine
        ${SRC_DIR}/70_power_plant/73_engine_fuel_&_control
        ${SRC_DIR}/70_power_plant/74_ignition
        ${SRC_DIR}/70_power_plant/75_air
        ${SRC_DIR}/70_power_plant/76_engine_controls
        ${SRC_DIR}/70_power_plant/77_engine_indicating
        ${SRC_DIR}/70_power_plant/78_exhaust
        ${SRC_DIR}/70_power_plant/79_oil
        ${SRC_DIR}/70_power_plant/80_starting
        ${SRC_DIR}/70_power_plant/81_turbines
        ${SRC_DIR}/70_power_plant/82_water_injection
        ${SRC_DIR}/70_power_plant/83_accessory_gear_boxes
        ${SRC_DIR}/70_power_plant/84_propulsion_augmentation
        ${SRC_DIR}/xx_imgui_xp_impl
        ${SRC_DIR}/xx_examples
        ${SRC_DIR}/xx_examples/imgui
        ${SRC_DIR}/xx_tests
    )

target_include_directories(IMGUI PUBLIC
        ${IMGUI_LIB_DIR}
        ${IMGUI_LIB_DIR}/backends
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "lib/SDK/CHeaders/XPLM"
        "lib/SDK/CHeaders/Widgets"
        "lib/SDK/CHeaders/Wrappers"
        "lib"
)






# PLATFORM DEFINITIONS
if(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_definitions(-DIBM=1)
elseif(APPLE)
    add_definitions(-DAPL=1)
else()
    add_definitions(-DLIN=1)
endif()

# TARGET SDK VERSIONS
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
        -DHAS_XPLM
        -DXPLM200=1
        -DXPLM210=1
        -DXPLM300=1
        -DXPLM301=1
        -DXPLM302=1
        -DXPLM400=1
        -DXPLM401=1
        -DXPLM411=1)




# LINKING CONFIGURATION
if (APPLE)
    find_library(OPENGL_FRAMEWORK OpenGL)
elseif(WIN32)
    find_library(OPENGL_FRAMEWORK opengl32 "${CMAKE_CURRENT_SOURCE_DIR}/GL_for_Windows/lib")
else()
    set(OPENGL_FRAMEWORK "")
endif()

if(WIN32)
    find_library(XPLM_LIBRARY XPLM_64 "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDK/Libraries/Win/")
    find_library(XPWIDGETS_LIBRARY XPWidgets_64 "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDK/Libraries/Win/")
elseif(APPLE)
    find_library(XPLM_LIBRARY XPLM "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDK/Libraries/Mac")
    find_library(XPWIDGETS_LIBRARY XPWidgets "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDK/Libraries/Mac")
else()
    set(XPLM_LIBRARY "")
    set(XPWIDGETS_LIBRARY "")
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI
        ##IMGUI_WRAPPER
        ${XPLM_LIBRARY}
        ${XPWIDGETS_LIBRARY}
        ${OPENGL_FRAMEWORK}
        OpenGL::GL
)




# PLUGIN OUTPUT CONFIGURATION
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX "")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}.xpl")

# OUTPUT THE PLUGIN FILE
if(WIN32)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}_out/win_x64")
elseif(APPLE)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}_out/mac_x64")
else()
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}_out/lin_x64")
endif()




# COPY PLUGIN .XPL FILE TO AIRCRAFT PLUGIN DIRECTORY
if(APPLE AND LOCAL_XP)
    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}_out/mac_x64/${CMAKE_PROJECT_NAME}.xpl
            ${ACF_DIRECTORY}/plugins/${CMAKE_PROJECT_NAME}/mac_x64/
    )
endif()
