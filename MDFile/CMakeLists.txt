cmake_minimum_required(VERSION 3.16)

add_library(MDFile
	include/MDFile.h
	src/MDFile.cpp
)

target_include_directories(MDFile
	PRIVATE
	./
)