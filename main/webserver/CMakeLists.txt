add_library(cgi cgi.h)
add_library(htmldata htmldata.c)
add_library(lwipopts lwipopts.h)
add_library(ssi ssi.h)

execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(webserver cgi htmldata lwipopts ssi)

