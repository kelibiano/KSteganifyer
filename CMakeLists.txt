
cmake_minimum_required (VERSION 2.6)

project (Steganifyer)

set (Steganifyer_VERSION_MAJOR 1)
set (Steganifyer_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(Steganifyer src/main.cpp)
