#Can be edited

OPTION(CROSS_WIN "Cross compilation for Windows" OFF)
OPTION(STATIC "Build a static library" OFF)
OPTION(TIMERS "Activate the timers (Linux Only)" OFF)
OPTION(COUNTERS "Activate the counters" OFF)

#Should not be modified

project(lpaggreg)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(LPAGGREG_VERSION_MAJOR "4")
set(LPAGGREG_VERSION_MINOR "0")
set(LPAGGREG_VERSION_PATCH "0")
set(LPAGGREG_VERSION "${LPAGGREG_VERSION_MAJOR}.${LPAGGREG_VERSION_MINOR}.${LPAGGREG_VERSION_PATCH}")
#add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")



aux_source_directory(src SRC_LIST)
if(STATIC)
    add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
else()
    add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
endif(STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LPAGGREG_VERSION} SOVERSION ${LPAGGREG_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h")

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
