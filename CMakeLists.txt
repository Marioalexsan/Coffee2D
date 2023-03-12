cmake_minimum_required(VERSION 3.18)

project(ProjectSilver-Coffee2DEdition)
include(FetchContent)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
	add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
elseif(MSVC)
	add_compile_options(/W4 /permissive- /wd4251 /wd4201)
endif()

cmake_minimum_required(VERSION 3.18)

add_subdirectory(Coffee2D)
add_subdirectory(ProjectSilver)
