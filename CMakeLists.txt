INCLUDE(CPack)
# Minimum version
cmake_minimum_required (VERSION 2.6)
enable_testing()
# Project definition
set (PROJECT_NAME "Steganifyer" C CXX)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

project (${PROJECT_NAME})

# Defining variables
set (Steganifyer_VERSION_MAJOR 1)
set (Steganifyer_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)


# BOOST CONFIG
set(Boost_USE_STATIC_LIBS   ON)
set(BOOST_ALL_DYN_LINK ON)

# FIND BOOST

find_package(Boost COMPONENTS program_options log REQUIRED)

if(Boost_FOUND)
    # INCLUDE SUB FOLDERS
    add_subdirectory(modules)
    add_subdirectory(test)

    # INCLUDES
    include_directories(${Boost_INCLUDE_DIR}
                        ${GTEST_INCLUDE_DIRS}
                        ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/headers)
    
    file(GLOB APP_SRC "src/*.cpp")
    # MAIN EXECUTABLE
    add_executable(${PROJECT_NAME} ${APP_SRC})
    #LINKING 
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries (${PROJECT_NAME} api)

    install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin
                                     LIBRARY DESTINATION lib)
endif()
