cmake_minimum_required(VERSION 3.9)
project(main CXX)

set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
	MAIN_SRCS
)

set(
	MAIN_HEADERS
	main.cpp
)

add_executable(main ${MAIN_HEADERS} ${MAIN_SRCS})

target_include_directories(main
	PUBLIC ${MAIN_SRC_DIR}
)

target_link_libraries(main domain utilities)