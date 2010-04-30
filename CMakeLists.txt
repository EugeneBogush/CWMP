project(cwmp)
cmake_minimum_required(VERSION 2.4.0)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_DONT_USE_QTGUI TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project
find_package(QCA2 REQUIRED)

add_subdirectory(src)

