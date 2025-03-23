##  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
##  •                                                       TOGA
##  •                                    COPYRIGHT (c) 2025  -  ALL RIGHTS RESERVED
##  ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••


cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set_target_properties( PROPERTIES
        C_STANDARD "11" CXX_STANDARD "20")


# FLAGS FOR COPYING PLUGIN TO LOCAL ACF PLUGIN DIRECTORY
set(LOCAL_XP 1)         # Are we building to a local directory? (ie. home desktop computer) 0=NO COPY PERFORMED



# PROJECT NAME
project(b717)



# PLUGIN VERSION    (set these 3 values manually when a new version is released)
#                   (you can then use version.h in C++ as needed)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
configure_file (lib/TOGA/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/lib/TOGA/version.h @ONLY)
message(${PROJECT_NAME} "v" ${PROJECT_VERSION})





# SET PATH TO ACF PLUGIN DIRECTORY
file(READ acf_path.txt ACF_DIRECTORY)






if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")     # Minimum MacOS
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
else()
    set(USE_VMPROTECT 1)
endif()






# PROJECT LIBRARIES AND FILES
set(TOGA_LIB_DIR lib/TOGA/)
set(TOGA_LIB
        ${TOGA_LIB_DIR}/debug_flag.cpp
        ${TOGA_LIB_DIR}/debug_flag.h
        ${TOGA_LIB_DIR}/imgui_wrapper.cpp
        ${TOGA_LIB_DIR}/imgui_wrapper.h
        ${TOGA_LIB_DIR}/version.h
)

set(SRC_DIR src/)
set(SRC
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/imgui_impl_xplane.cpp
        ${SRC_DIR}/imgui_impl_xplane.h
)

set(ALL_SRC
        ${TOGA_LIB}
        ${SRC}
)

add_library(${CMAKE_PROJECT_NAME} SHARED ${ALL_SRC})



set(IMGUI_LIB_DIR lib/IMGUI/)
add_library(IMGUI STATIC
        #lib/IMGUI/imgui.cpp
        #lib/IMGUI/imgui_draw.cpp
        #lib/IMGUI/imgui_widgets.cpp
        #lib/IMGUI/imgui_tables.cpp
        #lib/IMGUI/backends/imgui_impl_opengl2.cpp
        #src/imgui_impl_xplane.cpp

        ${IMGUI_LIB_DIR}/imgui.cpp
        ${IMGUI_LIB_DIR}/imgui_draw.cpp
        ${IMGUI_LIB_DIR}/imgui_widgets.cpp
        ${IMGUI_LIB_DIR}/imgui_tables.cpp
        ${IMGUI_LIB_DIR}/backends/imgui_impl_opengl2.cpp
        ${SRC_DIR}/imgui_impl_xplane.cpp
)







# DIRECTORIES
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${IMGUI_LIB_DIR}
        ${IMGUI_LIB_DIR}/backends
)


include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    "lib/SDK/CHeaders/XPLM"
    "lib/SDK/CHeaders/Widgets"
    "lib/SDK/CHeaders/Wrappers"
    "lib"
)







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





# LINKING
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
    # not needed on Linux
    set(XPLM_LIBRARY "")
    set(XPWIDGETS_LIBRARY "")
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI
        ${XPLM_LIBRARY}
        ${XPWIDGETS_LIBRARY}
        ${OPENGL_FRAMEWORK}
        OpenGL::GL
)






# SET THE PLUGIN OUTPUT FILE NAME
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





# COPY PLUGIN .xpl FILE TO AIRCRAFT PLUGIN DIRECTORY
if(APPLE AND LOCAL_XP)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}_out/mac_x64/${CMAKE_PROJECT_NAME}.xpl
            ${ACF_DIRECTORY}/plugins/${CMAKE_PROJECT_NAME}/mac_x64/
    )
endif()


