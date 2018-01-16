
include (GenerateExportHeader)

set(LIBRARY_NAME "api")

file(GLOB SRCS "*.cpp")
file(GLOB HDRS "*.h")

include_directories(./
                    ${Boost_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/headers
                    ${PROJECT_SOURCE_DIR}/modules/mSteganifyer
                    ${PROJECT_SOURCE_DIR}/modules/mBMPIO)

ADD_LIBRARY(${LIBRARY_NAME} STATIC ${SRCS})

GENERATE_EXPORT_HEADER(${LIBRARY_NAME}
             BASE_NAME sharelib
             EXPORT_MACRO_NAME SHARED_EXPORT
             EXPORT_FILE_NAME shared_EXPORTS.h
             STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)