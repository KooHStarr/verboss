cmake_minimum_required(VERSION 2.8)
project(ENGINE CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -pedantic")
set(CMAKE_CXX_DEBUG_FLAGS "-g")
set(CMAKE_CXX_RELEASE_FLAGS "-O2")

if (CMAKE_BUILD_TYPE STREQUAL "release")
    set(sfml_LINK_LIBRARIES sfml-graphics sfml-window sfml-system)
else()
    set(sfml_LINK_LIBRARIES sfml-graphics-d sfml-window-d sfml-system-d)
endif()

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)


add_executable(engine ${SOURCES} ${HEADERS})
target_link_libraries(engine ${sfml_LINK_LIBRARIES})
add_dependencies(engine SFML)

#Copy dlls to the engine directory.
if(WIN32)
add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/../sfml/bin"
        $<TARGET_FILE_DIR:engine>)
endif()