INCLUDE(CPack)
# Minimum version
cmake_minimum_required (VERSION 2.6)
enable_testing()
# Project definition
set (PROJECT_NAME "Steganifyer" C CXX)
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

project (${PROJECT_NAME})

if(UNIX) 
    add_definitions("-fPIC")
endif()

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

find_package(Boost COMPONENTS filesystem unit_test_framework REQUIRED)

if(Boost_FOUND)
    # INCLUDE SUB FOLDERS
    add_subdirectory(modules)
    add_subdirectory(test)

    # INCLUDES
    include_directories(${Boost_INCLUDE_DIR}
                        ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/headers)
    
    file(GLOB APP_SRC "src/*.cpp")
    # MAIN EXECUTABLE
    add_executable(${PROJECT_NAME} ${APP_SRC})
    #LINKING 
    target_link_libraries (${PROJECT_NAME} api ${Boost_LIBRARIES})
    if (UNIX)
        target_link_libraries (${PROJECT_NAME} dl)
    #do something
    endif (UNIX)

    install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin
                                     LIBRARY DESTINATION lib)
endif()

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    #add_custom_target( doc_doxygen ALL
    #    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    #    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #    COMMENT "Generating API documentation with Doxygen"
    #    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
