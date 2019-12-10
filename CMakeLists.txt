cmake_minimum_required(VERSION 3.10...3.16)

project(Hello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(GENERATE_TESTS FALSE CACHE BOOL "Generate tests")

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(SOURCES ${SRC_DIR}/argParser.cpp)

add_executable(main
			   ${SRC_DIR}/main.cpp
			   ${SOURCES}
			   )


if(GENERATE_TESTS)

	enable_testing()
	find_package(GTest REQUIRED)
	include(GoogleTest)

	add_executable(tests
				   tests/argParser.cpp
				   ${SOURCES})

    target_include_directories(tests PRIVATE ${SRC_DIR})
	target_link_libraries(tests GTest::GTest GTest::Main)

	gtest_discover_tests(tests)

endif()
