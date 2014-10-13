cmake_minimum_required(VERSION 2.8)
project(verboss)
#set various cmake variables

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_EXECUTABLE_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

include(ExternalProject)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
    message("No build type specified, defaulting to RelWithDebInfo")
endif(NOT CMAKE_BUILD_TYPE)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/sfml/cmake/modules")


########################################################################################################
# Let's get SFML up and running.
set(sfml_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/sfml")
set(sfml_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/sfml")
set(sfml_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sfml_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})


#add sfml from source
ExternalProject_Add(SFML
    PREFIX ${sfml_PREFIX}
    SOURCE_DIR "extlibs/sfml/"
    INSTALL_DIR ${sfml_INSTALL_DIR}
    CMAKE_ARGS ${sfml_CMAKE_ARGS}
    )

include_directories(${sfml_INSTALL_DIR}/include)
link_directories(${sfml_INSTALL_DIR}/lib)
########################################################################################################



########################################################################################################
#add lua
set(lua_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/lua")
set(lua_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/lua")
set(lua_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${lua_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

ExternalProject_Add(lua
    PREFIX ${lua_PREFIX}
    SOURCE_DIR "extlibs/lua/"
    INSTALL_DIR ${lua_INSTALL_DIR}
    CMAKE_ARGS ${lua_CMAKE_ARGS}
    )

include_directories(${lua_INSTALL_DIR}/src)
include_directories(${lua_INSTALL_DIR}/include)
link_directories(${lua_INSTALL_DIR}/lib)
########################################################################################################


########################################################################################################
#add luabind
#set(luabind_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/luabind")
#set(luabind_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/luabind")
#set(luabind_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${luabind_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#                       -DCMAKE_LIB_PATH=${lua_INSTALL_DIR}/lib -DCMAKE_INCLUDE_PATH=${lua_INSTALL_DIR}/include)

#ExternalProject_Add(luabind DEPENDS lua
#    PREFIX ${luabind_PREFIX}
#    SOURCE_DIR "extlibs/luabind/"
#    INSTALL_DIR ${luabind_INSTALL_DIR}
#    CMAKE_ARGS ${luabind_CMAKE_ARGS}
#    )

#include_directories(${luabind_INSTALL_DIR}/include)
#link_directories(${luabind_INSTALL_DIR}/lib)
########################################################################################################
include_directories("extlibs/luabridge/Source/LuaBridge")
include_directories("extlibs/luabridge/Source/LuaBridge/detail")


# Our actual engine project.
add_subdirectory(engine)