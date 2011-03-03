find_package(Doxygen)

if(DOXYGEN_FOUND)
    if(DOXYGEN_DOT_FOUND)
        set(DOXYGEN_DOT_YES_NO YES)
    else(DOXYGEN_DOT_FOUND)
        set(DOXYGEN_DOT_YES_NO NO)
    endif(DOXYGEN_DOT_FOUND)
    
    configure_file(${CMAKE_SOURCE_DIR}/cwmp.doxyfile.in
        ${CMAKE_BINARY_DIR}/cwmp.doxyfile)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/cwmp.doxyfile)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        DESTINATION share/doc/prezu_cwmp/api-documentation
        OPTIONAL)
    
else(DOXYGEN_FOUND)
    message(WARNING "Doxygen was not found on the system, thus API documentation will NOT be generated")
endif(DOXYGEN_FOUND)
