# The QtTest libraries are required for building the tests.
find_package(Qt5Test REQUIRED)

# Specify the source files for the tests.
set(QREDIS_TESTS_SRC
    main.cpp
    testclient.cpp)

# Specify the files that need to be MOC'd.
qt5_wrap_cpp(QREDIS_TESTS_MOC
    testclient.h)

# Create the test executable.
add_executable(qredis-tests
    ${QREDIS_TESTS_SRC}
    ${QREDIS_TESTS_MOC})

# Specify the Qt modules the test executable links against.
qt5_use_modules(qredis-tests Core Test)

# Naturally, we also link against the QRedis library.
target_link_libraries(qredis-tests qredis)

# Register the target as a test.
add_test(tests qredis-tests)
