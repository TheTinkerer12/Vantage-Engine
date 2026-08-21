cmake_minimum_required(VERSION 3.10)
project(VantageEngine CXX C)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")

set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c")

add_executable(my_program ${SOURCES} ${GLAD_SOURCE})

target_include_directories(my_program PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/glad")

target_link_libraries(my_program PRIVATE 
    glfw 
    GL 
    X11 
    pthread 
    Xrandr 
    Xi 
    dl
)

set_target_properties(TestGame PROPERTIES 
    OUTPUT_NAME "TestGame"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin"
)
