cmake_minimum_required(VERSION 2.8)

project(test_opartitioner)

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/test/opartitioner/sources/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/test/opartitioner/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${lpaggreg_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

target_link_libraries(${PROJECT_NAME} lpaggreg)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LPAGGREG_VERSION} SOVERSION ${LPAGGREG_VERSION_MAJOR})

add_test (NAME TestOPartitioner COMMAND test_opartitioner)
