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
    GIT_TAG master
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(glad)

############################################################################################

# Ajouter les shaders en tant que ressources
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/src/shaders)

# Vérifie que le dossier des shaders existe
if(NOT EXISTS ${SHADER_DIR})
    message(FATAL_ERROR "Le dossier 'shaders' n'existe pas dans ${SHADER_DIR}")
endif()

# Liste des shaders à copier
file(GLOB SHADER_FILES
    "${SHADER_DIR}/*"
)
# Répertoire de destination pour les shaders
set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/shaders)

# Ajoute une règle pour copier les shaders
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_FILES} ${SHADER_OUTPUT_DIR}
    COMMENT "Copie des shaders dans le dossier de build"
)


############################################################################################

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/**/**/*.cpp")
add_executable(main src/main.cpp ${SOURCES})

############################################################################################

target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-build/src)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build/include)
target_link_libraries(main PRIVATE glad glfw3 OpenGL::GL)

############################################################################################
# End of file : CMakeLists.txt
############################################################################################