

include(CTest)


set(PROJECT_NAME_STR Steganifyer)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)

find_package(Boost COMPONENTS filesystem unit_test_framework REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/headers
                    ${Boost_INCLUDE_DIR})

file(GLOB TEST_SRC_FILES *.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})


target_link_libraries(${PROJECT_TEST_NAME} 
                      ${Boost_LIBRARIES}
                      api)

add_test(test1 ../${PROJECT_TEST_NAME} --color_output -m XML -e test.xml -r detailed)