project(prezu_cwmp)
cmake_minimum_required(VERSION 2.4.0)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTDBUS TRUE)
set(QT_DONT_USE_QTGUI TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project
find_package(QCA2 REQUIRED)

#find_package(LibBSON ${LIBBSON_REQUIRED_VERSION} REQUIRED CONFIGS libbson-1.0-config.cmake)
#find_package(LibMongoC ${LIBMONGOC_REQUIRED_VERSION} REQUIRED CONFIGS libmongoc-1.0-config.cmake)
# set(CMAKE_C_STANDARD 11)
# libmongoc
include_directories("/usr/include/libmongoc-1.0")
link_libraries("/usr/lib/x86_64-linux-gnu/libmongoc-1.0.so.0")
# libbson
include_directories("/usr/include/libbson-1.0")
link_libraries("/usr/lib/x86_64-linux-gnu/libbson-1.0.so.0")

#########

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall ${CMAKE_CXX_FLAGS_RELEASE}")
#set(CMAKE_CXX_FLAGS_DEBUG "-Wall ${CMAKE_CXX_FLAGS_DEBUG} $(pkg-config --cflags --libs libmongocxx)")
#set(CMAKE_CXX_FLAGS_RELEASE "-Wall ${CMAKE_CXX_FLAGS_RELEASE} $(pkg-config --cflags --libs libmongocxx)")

add_subdirectory(src)
add_subdirectory(doc)

