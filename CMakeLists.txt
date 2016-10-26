#Can be edited

OPTION(STATIC "Build a static library" OFF)

#Should not be modified

cmake_minimum_required(VERSION 3.1)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LPAGGREG_VERSION_MAJOR "3")
set(LPAGGREG_VERSION_MINOR "2")
set(LPAGGREG_VERSION_PATCH "1")
set(LPAGGREG_VERSION "${LPAGGREG_VERSION_MAJOR}.${LPAGGREG_VERSION_MINOR}.${LPAGGREG_VERSION_PATCH}")
#add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

set (CMAKE_CXX_STANDARD 11)

if ( CMAKE_COMPILER_IS_GNUCC )
  add_definitions ("-Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )


enable_testing()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

export(PACKAGE ${PROJECT_NAME})

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
