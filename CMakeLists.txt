cmake_minimum_required(VERSION 3.21)
project(Pixee)

set(CMAKE_CXX_STANDARD 14)

set(EXTERNAL_LIBS_DIR external/)

# statically compile the application on windows to avoid dll headaches
if(WIN32)
	set(wxBUILD_SHARED OFF)
endif()
add_subdirectory(${EXTERNAL_LIBS_DIR}/wxWidgets)
FILE(GLOB_RECURSE SOURCE_FILES src/**)


add_executable(Pixee WIN32 ${SOURCE_FILES})
target_link_libraries(Pixee wx::core wx::base)
