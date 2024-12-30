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
FetchContent_Declare(
    stb_image
    GIT_REPOSITORY  https://github.com/nothings/stb.git
    GIT_TAG         master
    GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(stb_image)
FetchContent_GetProperties(stb_image)
if(NOT stb_image_POPULATED)
    FetchContent_Populate(stb_image)
endif()
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

# Ajouter les textures en tant que ressources
set(TEXTURE_DIR ${CMAKE_SOURCE_DIR}/src/images)

# Vérifie que le dossier des textures existe
if(NOT EXISTS ${TEXTURE_DIR})
    message(FATAL_ERROR "Le dossier 'images' n'existe pas dans ${TEXTURE_DIR}")
endif()

# Liste des textures à copier
file(GLOB TEXTURE_FILES "${TEXTURE_DIR}/*")

# Répertoire de destination pour les textures
set(TEXTURE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/images)

# Ajoute une règle pour copier les textures
add_custom_target(copy_texture ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${TEXTURE_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${TEXTURE_FILES} ${TEXTURE_OUTPUT_DIR}
    COMMENT "Copie des textures dans le dossier de build"
)

############################################################################################

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/**/**/*.cpp")
add_executable(main src/main.cpp ${SOURCES})

############################################################################################

target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-build/src)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/_deps/glad-build/include)
target_include_directories(main PRIVATE ${stb_image_SOURCE_DIR})
target_compile_definitions(main PRIVATE STB_IMAGE_IMPLEMENTATION)
target_link_libraries(main PRIVATE glad glfw3 OpenGL::GL)

############################################################################################
# End of file : CMakeLists.txt
############################################################################################