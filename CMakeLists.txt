cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0048 NEW)
PROJECT(jlink65c02 VERSION 0.0.1)

string(REPLACE "." ";" JLINK_VERSION_LIST "${CMAKE_PROJECT_VERSION}")
list(GET JLINK_VERSION_LIST 0 JLINK_VERSION_MAJOR)
list(GET JLINK_VERSION_LIST 1 JLINK_VERSION_MINOR)
list(GET JLINK_VERSION_LIST 2 JLINK_VERSION_REL)

INCLUDE(CheckSymbolExists)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

option(MODELCHECK_REQUIRED "Require Model Checking")

#minunit package
find_package(minunit REQUIRED)

#jemu65c02 package
find_package(jemu65c02 REQUIRED)

#Build config.h
configure_file(config.h.cmake include/jlink65c02/config.h)

#includes
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

#source files
AUX_SOURCE_DIRECTORY(src/bootstrap_linker JLINK_BOOTSTRAP_SOURCES)
AUX_SOURCE_DIRECTORY(src JLINK_SOURCES)

ADD_EXECUTABLE(jlink_bootstrap ${JLINK_BOOTSTRAP_SOURCES})
ADD_EXECUTABLE(jlink65c02 ${JLINK_SOURCES})
TARGET_COMPILE_OPTIONS(
    jlink65c02 PRIVATE -O3 ${JEMU65C02_CFLAGS} -Wall -Werror -Wextra -Wpedantic
                     -Wno-unused-command-line-argument)
TARGET_LINK_LIBRARIES(
    jlink65c02 PRIVATE ${JEMU65C02_LDFLAGS})
ADD_CUSTOM_TARGET(
    model_checks
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/models)

if (MODELCHECK_REQUIRED)
    ADD_DEPENDENCIES(jlink65c02 model_checks)
endif()

#Build a pkg-config file
SET(JLINK_PC "${CMAKE_BINARY_DIR}/jlink65c02.pc")
FILE(WRITE  ${JLINK_PC} "Name: jlink65c02")
FILE(APPEND ${JLINK_PC} "\nDescription: JEMU 65C02 Linker")
FILE(APPEND ${JLINK_PC} "\nVersion: ${CMAKE_PROJECT_VERSION}")
FILE(APPEND ${JLINK_PC} "\nURL: https://github.com/nanolith/jlink65c02")
FILE(APPEND ${JLINK_PC} "\nprefix=${CMAKE_INSTALL_PREFIX}")
FILE(APPEND ${JLINK_PC} "\nlibdir=\${prefix}/lib")
FILE(APPEND ${JLINK_PC} "\nbindir=\${prefix}/bin")
INSTALL(FILES ${JLINK_PC} DESTINATION lib/pkgconfig)

#Install binaries
INSTALL(TARGETS jlink65c02 jlink_bootstrap
        RUNTIME DESTINATION bin)
