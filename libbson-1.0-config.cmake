# Specify the minimum version you require.
 include_directories("/usr/include/libmongoc-1.0")
 include_directories("/usr/include/libbson-1.0")
 target_link_libraries(main.o /usr/lib/x86_64-linux-gnu/libmongoc-1.0.so.0 /usr/lib/x86_64-linux-gnu/libbson-1.0.so.0)

