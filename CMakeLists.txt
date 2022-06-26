cmake_minimum_required(VERSION 3.14)
project(Python)

set(CMAKE_CXX_STANDARD 14)

add_executable(Python main.cpp
        ./src/runtime/interpreter.cpp
        ./src/code/binaryFileParser.cpp
        ./src/object/pyString.cpp
        ./src/object/pyInteger.cpp
        ./src/object/pyObject.cpp
        ./src/runtime/universal.cpp
        ./src/container/bufferedInputStream.cpp
        ./src/code/codeObject.cpp
        ./src/container/arrayList.cpp
        ./src/object/klass.cpp
        ./src/runtime/frameObject.cpp
        ./src/object/functionObject.cpp
        )

include_directories("./")