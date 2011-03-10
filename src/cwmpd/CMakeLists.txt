# the next line sets up include and link directories and defines some variables that we will use.
# you can modify the behavior by setting some variables, e.g.
#   set(QT_USE_OPENGL TRUE)
# -> this will cause cmake to include and link against the OpenGL module
include(${QT_USE_FILE})
# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list

include_directories(${QCA2_INCLUDE_DIRS})
link_directories(${QCA2_LIBRARY_DIRS})
add_definitions(${QCA2_CFLAGS_OTHER})
# the variable "cwmp_SRCS" contains all .cpp files of this project
set(cwmpd_SRCS
    cwmpCtx.cpp
    cwmpdAdapter.cpp
    cwmpDeviceID.cpp
    cwmpDeviceIDParser.cpp
    cwmpEvent.cpp
    cwmpEventParser.cpp
    cwmpGetParameterValues.cpp
    cwmpGetParameterValuesMethod.cpp
    cwmpGetParameterValuesResponse.cpp
    cwmpGetParameterValuesResponseParser.cpp
    cwmpInform.cpp
    cwmpInformParser.cpp
    cwmpInformResponse.cpp
    cwmpInformResponseMethod.cpp
    cwmpMethod.cpp
    cwmpParameterValueStruct.cpp
    cwmpParameterListParser.cpp
    cwmpServer.cpp
    main.cpp
    tcpSessionThread.cpp)

set(cwmpd_MOC_HDRS
    cwmpdAdapter.h
    cwmpServer.h
    tcpSessionThread.h)

# tell cmake to create .moc files for all files in the variable cwmp_SRCS that require such a file.
# note: this assumes that you use #include "header.moc" in your files
#qt4_automoc(${cwmpd_SRCS})
qt4_wrap_cpp(cwmpd_MOC_SRCS ${cwmpd_MOC_HDRS})

# create an executable file named "cwmp" from the source files in the variable "cwmp_SRCS".
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_executable(cwmpd ${cwmpd_SRCS} ${cwmpd_MOC_SRCS})

# link the "cwmp" target against the Qt libraries. which libraries exactly, is defined by the "include(${QT_USE_FILE})" line above, which sets up this variable.
target_link_libraries(cwmpd ${QT_LIBRARIES} ${PC_QCA2_LIBRARIES})
install(TARGETS cwmpd 
        RUNTIME DESTINATION bin)

