cmake_minimum_required(VERSION 3.9)
project(utilities CXX)

set(UTILITIES_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
	UTILITIES_SRCS
	MyTimer.cpp
)

set(
	UTILITIES_HEADERS
	MyTimer.h
	MyRandom.h
	Node.h
	List.h
	LinkedList.h
	LinkedQueue.h
	RingList.h
	IndexException.h
	EmptyStructureException.h
	FullStructureException.h
	InvalidDataException.h
	RedSignException.h
)

add_library(utilities STATIC ${UTILITIES_HEADERS} ${UTILITIES_SRCS})

target_include_directories(utilities PUBLIC ${UTILITIES_SRC_DIR})