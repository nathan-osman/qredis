## QRedis

QRedis provides a modern Qt client library for communicating with a [Redis server](http://redis.io/). The code uses many new constructs introduced in [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) and compiles exclusively with Qt 5, ensuring years of compatibility down the road.

### Building QRedis

QRedis uses [CMake](http://www.cmake.org/) for building the client library, which simplifies the necessary steps across all supported platforms. Assuming you have Qt 5 installed in a location that CMake can find, the client library can be built with the following steps:

1. Open a terminal and navigate to the directory containing the QRedis source code.

2. Create a new directory that will contain the object and binary files produced by the build system and change to that directory:

        mkdir build
        cd build

3. Run CMake, which will produce the appropriate Makefile for your platform:

        cmake ..

4. On Unix-based build systems (including [MSYS](http://www.mingw.org/wiki/MSYS) and [Cygwin](http://www.cygwin.com/)), run:

        make

   For Microsoft Visual C++, run:

        nmake

### Usage

[TODO]