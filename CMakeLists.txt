cmake_minimum_required(VERSION 3.23)
project(SpriteEditor)

set(CMAKE_CXX_STANDARD 14)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(SpriteEditor main.cpp Canvas.cpp Image.cpp Image.h)

target_link_libraries(SpriteEditor ${wxWidgets_LIBRARIES})

# to activate stb_image
target_compile_definitions(SpriteEditor PRIVATE STB_IMAGE_IMPLEMENTATION)
