cmake_minimum_required(VERSION 3.10)
project(RSAEncode)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(RSAEncode    src/main.cpp
                            src/rsa.cpp
                            src/keys.cpp
                            src/mymath.cpp)

target_include_directories(RSAEncode PUBLIC src)