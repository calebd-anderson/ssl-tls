add_library(aes aes aes.c)
target_include_directories(aes PUBLIC .)
target_link_libraries(aes hex)
