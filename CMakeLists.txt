project(cwmp)
cmake_minimum_required(VERSION 2.4.0)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTNETWORK TRUE)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project

#include_directories(src/cwmpd)

add_subdirectory(src)

