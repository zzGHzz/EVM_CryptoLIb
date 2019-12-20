cmake_minimum_required(VERSION 3.14)
project(Demo)

set(CMAKE_CXX_STANDARD 14)

find_package (openssl REQUIRED)

include_directories(include)

add_executable(Demo
        include/point.h
        include/secp256k1.h
        secp256k1.cpp
        main.cpp)

target_link_libraries (Demo OpenSSL::SSL)
t