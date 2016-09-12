cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig REQUIRED)

project(lpaggreg-reader)

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/lpaggreg-reader/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/lpaggreg-reader/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${lpaggreg_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}/include")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

target_link_libraries(${PROJECT_NAME} lpaggreg)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LPAGGREG_VERSION} SOVERSION ${LPAGGREG_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
