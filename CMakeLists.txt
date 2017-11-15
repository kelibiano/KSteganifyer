# Minimum version
cmake_minimum_required (VERSION 2.6)

# Project definition
set (PROJECT_NAME "Steganifyer" CXX)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

project (${PROJECT_NAME})

# Defining variables
set (Steganifyer_VERSION_MAJOR 1)
set (Steganifyer_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BOOST CONFIG
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF) 
# FIND BOOST
find_package(Boost 1.63.0 COMPONENTS program_options log REQUIRED)

if(Boost_FOUND)
    # INCLUDE SUB FOLDERS
    add_subdirectory(modules)

    # INCLUDES
    include_directories(${Boost_INCLUDE_DIR}
                        ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/headers
                        ${PROJECT_SOURCE_DIR}/modules/mSteganifyer
                        ${PROJECT_SOURCE_DIR}/modules/mBMPIO)
    
    file(GLOB APP_SRC "src/*.cpp")
    # MAIN EXECUTABLE
    add_executable(${PROJECT_NAME} ${APP_SRC})
    #LINKING 
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries (${PROJECT_NAME} mSteganifyer)
    target_link_libraries (${PROJECT_NAME} mBMPIO)
endif()

#set(FooTestArgs --foo 1 --bar 2)
#add_executable(FooTest FooUnitTest.cc)
#GTEST_ADD_TESTS(FooTest "${FooTestArgs}" FooUnitTest.cc)