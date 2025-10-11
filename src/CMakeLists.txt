add_subdirectory(lib)
add_subdirectory(webserver EXCLUDE_FROM_ALL)
add_executable(http http.c)
