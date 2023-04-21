cmake_minimum_required(VERSION 3.16)

add_executable(MDFile-Playground
	main.cpp
)

target_link_libraries(MDFile-Playground
	PRIVATE
		MDFile
)

target_include_directories(MDFile-Playground
	PRIVATE
		./../MDFile/include
)
