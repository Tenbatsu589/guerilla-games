cmake_minimum_required(VERSION 3.10)

project(Core)

file(GLOB_RECURSE SRC "*.h" "*.cpp")

if (MSVC)
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS /Yupch.h )
	set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS /Ycpch.h )
endif(MSVC)

add_library(BoggleCore ${SRC})

