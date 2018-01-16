include(CTest)

add_definitions(${MSVC_COMPILER_DEFS})
# ---- tesing
set(EXT_PROJECTS_DIR ext)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)


set(PROJECT_NAME_STR Steganifyer)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES *.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)

if(NOT WIN32 OR MINGW)
    target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )
else()
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

target_link_libraries(${PROJECT_TEST_NAME} 
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${Boost_LIBRARIES}
                      api)

add_test(test1 ../${PROJECT_TEST_NAME} --gtest_output=xml)