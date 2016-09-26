#Can be edited

OPTION(STATIC "Build a static library" OFF)

#Not implemented yet
OPTION(CROSS_WIN "Cross compilation for Windows" OFF)
OPTION(TIMERS "Activate the timers (Linux Only)" OFF)
OPTION(COUNTERS "Activate the counters" OFF)
OPTION(OPENMP "Use the parallel version" OFF)

#Should not be modified

project(lpaggreg)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LPAGGREG_VERSION_MAJOR "3")
set(LPAGGREG_VERSION_MINOR "2")
set(LPAGGREG_VERSION_PATCH "1")
set(LPAGGREG_VERSION "${LPAGGREG_VERSION_MAJOR}.${LPAGGREG_VERSION_MINOR}.${LPAGGREG_VERSION_PATCH}")
#add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

ADD_SUBDIRECTORY(src)

export(PACKAGE ${PROJECT_NAME})

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
