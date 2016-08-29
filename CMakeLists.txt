
###################################################################################
#
#  Copyright (c) 2015, webvariants GmbH, http://www.webvariants.de
#
#  This file is released under the terms of the MIT license. You can find the
#  complete text in the attached LICENSE file or online at:
#
#  http://www.opensource.org/licenses/mit-license.php
#
#  @author: Tino Rusch (tino.rusch@webvariants.de)
#
###################################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(libsusi)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system program_options)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++11" )

file( GLOB SUSICPP_SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/TCPClient.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/SSLClient.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/SusiClient.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/EventManager.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/LineFramer.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/base64.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/sources/sha3.cpp )

add_library( susi SHARED ${SUSICPP_SRCFILES})
target_link_libraries( susi
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    bson)

install(TARGETS susi LIBRARY DESTINATION "/usr/local/lib")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION /usr/local/include)

set(CPACK_GENERATOR "DEB")
set(CPACK_SET_DESTDIR ON)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tino Rusch")
set(CPACK_PACKAGE_VERSION "0.2.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")
include(CPack)
