cmake_minimum_required(VERSION 3.10)
project(VantageEngine CXX C) # Added 'C' support for glad.c

set(CMAKE_CXX_STANDARD 17)

# 1. Gather all C++ source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")

# 2. Explicitly include your GLAD C file
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c")

# 3. Create the executable with both C++ and C files
add_executable(my_program ${SOURCES} ${GLAD_SOURCE})

# 4. Explicitly tell CMake where to find glad headers if needed
target_include_directories(my_program PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/glad")

# 5. Link all the exact libraries from your g++ flags
target_link_libraries(my_program PRIVATE 
    glfw 
    GL 
    X11 
    pthread 
    Xrandr 
    Xi 
    dl
)

# 6. Optional: Set output directory to match your old "Bin/TestGame" path
set_target_properties(my_program PROPERTIES 
    OUTPUT_NAME "TestGame"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin"
)