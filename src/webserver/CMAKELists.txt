add_executable(webserver webserver.c)
if (WIN32)
    target_link_libraries(webserver ws2_32)
endif()
