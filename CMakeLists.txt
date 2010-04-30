project(cwmp)
cmake_minimum_required(VERSION 2.4.0)
set(QT_USE_QTXML TRUE)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project

add_subdirectory(src)

