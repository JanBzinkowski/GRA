cmake_minimum_required(VERSION 3.26)
project(GRA)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
include_directories("${CMAKE_SOURCE_DIR}/src/include")
include_directories("C:/SFML/SFML-3.0.0/include")
set(SFML_DIR "C:/SFML/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
link_directories("C:/SFML/SFML-3.0.0/lib")
add_executable(GRA ${SOURCES})
#set_target_properties(GRA PROPERTIES WIN32_EXECUTABLE TRUE)
add_definitions(-DSFML_STATIC)
target_link_libraries(GRA
		sfml-graphics-s
		sfml-window-s
		sfml-system-s
		sfml-graphics-s-d
		sfml-window-s-d
		sfml-system-s-d
		freetype
		opengl32
		winmm
		gdi32
		ucrt
		)