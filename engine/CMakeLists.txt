cmake_minimum_required(VERSION 2.8)
project(ENGINE CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -pedantic")
set(CMAKE_CXX_DEBUG_FLAGS "-g")
set(CMAKE_CXX_RELEASE_FLAGS "-O2")

if (CMAKE_BUILD_TYPE STREQUAL "release")
    set(LINK_LIBRARIES sfml-graphics sfml-window sfml-system lua.dll)
else()
    set(LINK_LIBRARIES sfml-graphics-d sfml-window-d sfml-system-d lua.dll libphysfs.a libBox2D.a tgui-d thor-d libentityx.a)
endif()

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)
include_directories("ResourceManagerImpl")

add_executable(engine ${SOURCES} ${HEADERS})
add_dependencies(engine SFML)
add_dependencies(engine lua)
add_dependencies(engine physfs)
add_dependencies(engine Box2D)
add_dependencies(engine TGUI)
add_dependencies(engine Thor)
add_dependencies(engine entityx)
#add_dependencies(engine sfml-tmxloader)
target_link_libraries(engine ${LINK_LIBRARIES})


#Copy dlls to the engine directory.
if(WIN32)
add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/../sfml/bin"
        $<TARGET_FILE_DIR:engine>)
endif()