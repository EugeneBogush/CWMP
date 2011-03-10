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

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall ${CMAKE_CXX_FLAGS_RELEASE}")

add_subdirectory(src)
add_subdirectory(doc)


