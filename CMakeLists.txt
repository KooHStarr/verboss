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
# Let's get TGUI up and running.
set(tgui_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/TGUI")
set(tgui_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/TGUI")
set(tgui_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${tgui_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DSFML_ROOT=${sfml_PREFIX})


#add tgui from source
ExternalProject_Add(TGUI DEPENDS SFML
    PREFIX ${tgui_PREFIX}
    SOURCE_DIR "extlibs/TGUI/"
    INSTALL_DIR ${tgui_INSTALL_DIR}
    CMAKE_ARGS ${tgui_CMAKE_ARGS}
    )

include_directories(${tgui_INSTALL_DIR}/include)
link_directories(${tgui_INSTALL_DIR}/lib)
########################################################################################################



########################################################################################################
# Let's get Thor up and running.
set(Thor_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/Thor")
set(Thor_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/Thor")
set(Thor_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${Thor_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DSFML_ROOT=${sfml_PREFIX})


#add Thor from source
ExternalProject_Add(Thor DEPENDS SFML
    PREFIX ${Thor_PREFIX}
    SOURCE_DIR "extlibs/Thor/"
    INSTALL_DIR ${Thor_INSTALL_DIR}
    CMAKE_ARGS ${Thor_CMAKE_ARGS}
    )

include_directories(${Thor_INSTALL_DIR}/include)
link_directories(${Thor_INSTALL_DIR}/lib)
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
#add physfs
set(physfs_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/physfs")
set(physfs_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/physfs")
set(physfs_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${physfs_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

ExternalProject_Add(physfs
    PREFIX ${physfs_PREFIX}
    SOURCE_DIR "extlibs/physfs/"
    INSTALL_DIR ${physfs_INSTALL_DIR}
    CMAKE_ARGS ${physfs_CMAKE_ARGS}
    )

include_directories(${physfs_INSTALL_DIR})
include_directories(${physfs_INSTALL_DIR}/zlib123)
link_directories(${physfs_INSTALL_DIR}/lib)
########################################################################################################



########################################################################################################
#add Box2D
set(Box2D_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/Box2D/Box2D")
set(Box2D_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/Box2D/Box2D")
set(Box2D_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${Box2D_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                     -DBOX2D_INSTALL=ON -DBOX2D_BUILD_STATIC=ON -DBOX2D_BUILD_SHARED=ON)

ExternalProject_Add(Box2D
    PREFIX ${Box2D_PREFIX}
    SOURCE_DIR "extlibs/Box2D/Box2D"
    INSTALL_DIR ${Box2D_INSTALL_DIR}
    CMAKE_ARGS ${Box2D_CMAKE_ARGS}
    )

include_directories(${Box2D_INSTALL_DIR}/include)
link_directories(${Box2D_INSTALL_DIR}/lib)
########################################################################################################


include_directories("extlibs/luabridge/Source/LuaBridge")
include_directories("extlibs/luabridge/Source/LuaBridge/detail")


########################################################################################################
# Let's get entityx up and running.
set(entityx_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/entityx")
set(entityx_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/entityx")
set(entityx_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${entityx_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})


#add entityx from source
ExternalProject_Add(entityx
    PREFIX ${entityx_PREFIX}
    SOURCE_DIR "extlibs/entityx/"
    INSTALL_DIR ${entityx_INSTALL_DIR}
    CMAKE_ARGS ${entityx_CMAKE_ARGS}
    )

include_directories(${entityx_INSTALL_DIR}/include)
link_directories(${entityx_INSTALL_DIR}/lib)
########################################################################################################


########################################################################################################
#add zlib
set(zlib_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/zlib")
set(zlib_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/zlib")
set(zlib_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${zlib_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

ExternalProject_Add(zlib
    PREFIX ${zlib_PREFIX}
    SOURCE_DIR "extlibs/zlib"
    INSTALL_DIR ${zlib_INSTALL_DIR}
    CMAKE_ARGS ${zlib_CMAKE_ARGS}
    )

include_directories(${zlib_INSTALL_DIR}/include)
link_directories(${zlib_INSTALL_DIR}/lib)
########################################################################################################


########################################################################################################
#add sfml-tmxloader
set(sfml-tmxloader_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/extlibs/sfml-tmxloader")
set(sfml-tmxloader_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/extlibs/sfml-tmxloader")
set(sfml-tmxloader_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sfml-tmxloader_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                              -DSFML_ROOT=${sfml_PREFIX} -DBOX2D_ROOT=${Box2D_PREFIX} -DZLIB_ROOT=${zlib_PREFIX}
                              -DSFML_INCLUDE_DIR=${sfml_PREFIX}"/include/" -DBOX2D_INCLUDE_DIR=${Box2D_PREFIX}"/include/"
                              -DBOX2D_LIBRARIES=${Box2D_PREFIX}"/lib/libBox2D.dll.a")

ExternalProject_Add(sfml-tmxloader DEPENDS SFML zlib Box2D
    PREFIX ${sfml-tmxloader_PREFIX}
    SOURCE_DIR "extlibs/sfml-tmxloader"
    INSTALL_DIR ${sfml-tmxloader_INSTALL_DIR}
    CMAKE_ARGS ${sfml-tmxloader_CMAKE_ARGS}
    )

include_directories(${sfml-tmxloader_INSTALL_DIR}/include)
link_directories(${sfml-tmxloader_INSTALL_DIR}/lib)
########################################################################################################


# Our actual engine project.
add_subdirectory(engine)