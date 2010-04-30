find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_QCA2 REQUIRED qca2)
set(QCA2_DEFINITIONS ${PC_QCA2_CFLAGS_OTHER})

if(NOT PC_QCA2_FOUND)
    message(FATAL_ERROR "QCA2 library not found!")
endif(NOT PC_QCA2_FOUND)
pkg_search_module(QCA2 REQUIRED qca2)

