# add_library(des des des.c)
add_executable(des des des.c)
add_definitions(-DTEST_DES)
target_include_directories(des PUBLIC .)
target_link_libraries(des hex)

