project(prezu_cwmp)
cmake_minimum_required(VERSION 2.4.0)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_DONT_USE_QTGUI TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project
find_package(QCA2 REQUIRED)

find_package(Doxygen)

add_subdirectory(src)

if(DOXYGEN_FOUND)
    if(DOXYGEN_DOT_FOUND)
        set(DOXYGEN_DOT_YES_NO YES)
    else(DOXYGEN_DOT_FOUND)
        set(DOXYGEN_DOT_YES_NO NO)
    endif(DOXYGEN_DOT_FOUND)
    
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cwmp.doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/cwmp.doxyfile)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/cwmp.doxyfile)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        DESTINATION share/doc/prezu_cwmp/api-documentation)
    
    add_dependencies(cwmpd doc)
endif(DOXYGEN_FOUND)

