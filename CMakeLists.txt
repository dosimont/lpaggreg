#Can be edited

OPTION(STATIC "Build a static library" OFF)

#Should not be modified

cmake_minimum_required(VERSION 3.1)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LPAGGREG_VERSION_MAJOR "4")
set(LPAGGREG_VERSION_MINOR "0")
set(LPAGGREG_VERSION_PATCH "0")
set(LPAGGREG_VERSION "${LPAGGREG_VERSION_MAJOR}.${LPAGGREG_VERSION_MINOR}.${LPAGGREG_VERSION_PATCH}")
#add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

set (CMAKE_CXX_STANDARD 11)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

enable_testing()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

export(PACKAGE ${PROJECT_NAME})

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
