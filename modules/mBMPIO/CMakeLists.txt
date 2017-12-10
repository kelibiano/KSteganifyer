
set(LIBRARY_NAME "mBMPIO")

file(GLOB SRCS "*.cpp")
file(GLOB HDRS "*.h")


include_directories(./
                    ${Boost_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/headers
                    ${PROJECT_SOURCE_DIR}/modules/mBMPIO)

ADD_LIBRARY(${LIBRARY_NAME} SHARED ${SRCS})

target_link_libraries (${LIBRARY_NAME} ${Boost_LIBRARIES})
target_link_libraries (${LIBRARY_NAME} api)