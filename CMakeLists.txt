cmake_minimum_required(VERSION 3.18)

project(text-based-game
	VERSION 0.1
	DESCRIPTION "console(=text) managed game"
	LANGUAGES CXX
	)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")


add_executable(text-based-game.exe main.cpp)
