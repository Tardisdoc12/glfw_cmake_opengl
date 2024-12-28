############################################################################################
# Name of this file : CMakeLists.txt
# Author : Jean Anquetil
# Date : 27/12/2024
############################################################################################

cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

############################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(GLFW)
find_package(OpenGL REQUIRED)
# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(glad)

############################################################################################

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/**/**/*.cpp")
add_executable(main src/main.cpp ${SOURCES})

############################################################################################

target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-build/src)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build/include)
target_link_libraries(main PRIVATE glfw3 glad OpenGL::GL)

############################################################################################
# End of file : CMakeLists.txt
############################################################################################