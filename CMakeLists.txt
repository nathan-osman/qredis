# CMake 2.8.9 is required in order to use the new Qt 5 functions.
cmake_minimum_required(VERSION 2.8.9)

project(qredis)

# These definitions are used to set the target properties later on.
set(QREDIS_MAJOR 0)
set(QREDIS_MINOR 1)
set(QREDIS_PATCH 0)
set(QREDIS_VERSION "${QREDIS_MAJOR}.${QREDIS_MINOR}.${QREDIS_PATCH}")

# C++11 support must be enabled in GCC.
if(CMAKE_COMPILER_IS_GNUCXX)
    # Ensure that we are using at least GCC 4.6+.
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.6)
        message(FATAL_ERROR "GCC 4.6+ is required (" ${CMAKE_CXX_COMPILER_VERSION} " detected).")
    endif()
    # Enable C++11 features.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

# The QtCore and QtNetwork libraries are both required.
find_package(Qt5Core    REQUIRED)
find_package(Qt5Network REQUIRED)

# Specify where QRedis includes are located.
include_directories(include)

# QRedis source files.
set(QREDIS_SRC
    src/client.cpp
    src/request.cpp)

# QRedis header files requiring MOC.
qt5_wrap_cpp(QREDIS_MOC
    include/qredis/client.h
    include/qredis/request.h)

# Create the client library.
add_library(qredis SHARED
    ${QREDIS_SRC}
    ${QREDIS_MOC})

# Set the client library's properties.
set_target_properties(qredis PROPERTIES
    VERSION   ${QREDIS_VERSION}
    SOVERSION ${QREDIS_MAJOR})

# This causes the appropriate libraries to be included in the link process.
qt5_use_modules(qredis Network)

# Specify the proper installation paths.
install(TARGETS qredis
    LIBRARY       DESTINATION lib
    ARCHIVE       DESTINATION lib
    RUNTIME       DESTINATION bin
    PUBLIC_HEADER DESTINATION include/qredis)
