add_executable(http http.c)
if (WIN32)
    target_link_libraries(http ws2_32)
endif()