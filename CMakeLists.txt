# Minimum version
cmake_minimum_required (VERSION 2.6)

# Project definition
set (PROJECT_NAME "Steganifyer" CXX)
project (${PROJECT_NAME})

# Defining variables
set (Steganifyer_VERSION_MAJOR 1)
set (Steganifyer_VERSION_MINOR 0)

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package(Boost 1.63.0 COMPONENTS program_options REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR}
                        ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/headers
                        ${PROJECT_SOURCE_DIR}/modules)
    add_executable(${PROJECT_NAME}  src/main.cpp 
                                    src/Application.cpp
                                    src/CommandContext.cpp
                                    src/ModulesManager.cpp
                                    src/CommandFactory.cpp
                                    src/CommandChain.cpp
                                    modules/Steganifyer.cpp)
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

# Executables
