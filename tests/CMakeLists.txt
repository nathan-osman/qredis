# The QtTest libraries are required for building the tests.
find_package(Qt5Test REQUIRED)

# Create the test executable.
add_executable(qredis-tests
    main.cpp)

# Specify the Qt modules the test executable links against.
qt5_use_modules(qredis-tests Core Test)

# Naturally, we also link against the QRedis library.
target_link_libraries(qredis-tests qredis)
