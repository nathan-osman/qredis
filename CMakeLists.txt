# CMake 2.8.9 is required in order to use the new Qt 5 functions.
cmake_minimum_required(VERSION 2.8.9)

project(qredis)

# These options can be used to control the build process.
option(BUILD_TESTS "Build the QRedis test suite" ON)

# These definitions are used to set the target properties later on.
set(QREDIS_MAJOR 0)
set(QREDIS_MINOR 1)
set(QREDIS_PATCH 0)
set(QREDIS_VERSION "${QREDIS_MAJOR}.${QREDIS_MINOR}.${QREDIS_PATCH}")

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
    include/qredis/request.h
    src/client_p.h
    src/request_p.h)

# Create the client library.
add_library(qredis SHARED
    ${QREDIS_SRC}
    ${QREDIS_MOC})

# Set the client library's properties.
set_target_properties(qredis PROPERTIES
    VERSION   ${QREDIS_VERSION}
    SOVERSION ${QREDIS_MAJOR})

# This causes the appropriate libraries to be included in the link process.
qt5_use_modules(qredis Core Network)

# Specify the proper installation paths.
install(TARGETS qredis
    LIBRARY       DESTINATION lib
    ARCHIVE       DESTINATION lib
    RUNTIME       DESTINATION bin
    PUBLIC_HEADER DESTINATION include/qredis)

# If the tests are to be built, then add them to the project.
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
