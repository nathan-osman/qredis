## QRedis

QRedis provides a modern Qt client library for communicating with a [Redis server](http://redis.io/). The code compiles exclusively with Qt 5, ensuring years of compatibility down the road.

### Requirements

To compile QRedis, the following requirements must be met:

* GCC or Microsoft Visual C++
* Qt 5+

*It is not necessary to have Redis installed in order to build the client library. However, you will be unable to run the test suite.*

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

In order to send commands to a Redis server, you need to create an instance of the `Client` class and connect to the server. For example, if Redis is running on the same server as your application, your code might look something like this:

    #include <qredis/client.h>
    
    QRedis::Client client;
    client.connectToHost("localhost");

Once the connection is complete, the client will emit the `connected()` signal. You can then begin executing commands. For example, to send the `PING` command:

    QRedis::Command * command = client.sendCommand("PING");

The `sendCommand()` method returns a `Command *`, which provides signals to indicate when the command has completed or when an error occurs.
