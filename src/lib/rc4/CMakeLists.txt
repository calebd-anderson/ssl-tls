add_library(rc4 rc4.c)
target_include_directories(rc4 PUBLIC .)
target_link_libraries(rc4 hex)
