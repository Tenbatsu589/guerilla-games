cmake_minimum_required(VERSION 3.10)

project(BoggleTest)

file(GLOB_RECURSE SRC "*.h" "*.cpp")

include_directories("../core")

add_executable(BoggleTest ${SRC})
target_link_libraries (BoggleTest BoggleCore)

if (UNIX)
	find_package(Threads REQUIRED)
	set(CMAKE_THREAD_PREFER_PTHREAD On)
	target_link_libraries (BoggleTest ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)