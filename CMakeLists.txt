cmake_minimum_required(VERSION 2.8)
project(verboss)

#set various cmake variables
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR})

include(ExternalProject)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
    message("No build type specified, defaulting to RelWithDebInfo")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/sfml/cmake/modules")

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


# Our actual engine project.
add_subdirectory(engine)