cmake_minimum_required(VERSION 3.10...3.16)

project(Hello VERSION 1.0 LANGUAGES CXX)

set(GENERATE_TESTS FALSE CACHE BOOL "Generate tests")

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(SOURCES ${SRC_DIR}/task.cpp 
			${SRC_DIR}/argParser.cpp
			${SRC_DIR}/nativeCommandRunner.cpp)

add_executable(main
			   ${SRC_DIR}/main.cpp
			   ${SOURCES}
			   )

set_target_properties(main PROPERTIES CXX_STANDARD 14)


if(GENERATE_TESTS)

	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        release-1.8.0
	)
	FetchContent_MakeAvailable(googletest)
	FetchContent_GetProperties(googletest)

	enable_testing()

	add_executable(tests
				   tests/argParser.test.cpp
				   tests/task.test.cpp
				   ${SOURCES})

	set_target_properties(tests PROPERTIES CXX_STANDARD 14)

    target_include_directories(tests PRIVATE ${SRC_DIR})
	target_link_libraries(tests gtest gtest_main gmock gmock_main)

	add_test(MyTest tests)

endif()
