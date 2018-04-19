cmake_minimum_required(VERSION 3.9)
project(domain CXX)

set(DOMAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
	DOMAIN_SRCS
	Automobile.cpp
)

set(
	DOMAIN_HEADERS
	Automobile.h
)

add_library(domain STATIC ${DOMAIN_SRCS} ${DOMAIN_HEADERS})

include_directories(${utilities})

target_include_directories(domain PUBLIC ${DOMAIN_SRC_DIR})

target_link_libraries(domain utilities)