cmake_minimum_required(VERSION 3.21)
project(SpriteEditor)

set(CMAKE_CXX_STANDARD 14)

set(EXTERNAL_LIBS_DIR external/)

add_subdirectory(${EXTERNAL_LIBS_DIR}/wxWidgets)

add_executable(SpriteEditor main.cpp Canvas.cpp Image.cpp)
target_link_libraries(SpriteEditor wx::core wx::base)

# to activate stb_image
target_compile_definitions(SpriteEditor PRIVATE STB_IMAGE_IMPLEMENTATION)
