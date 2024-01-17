cmake_minimum_required(VERSION 3.26)

project("Accumulator-Based-Programming-Language" LANGUAGES C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited Configs" FORCE)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ACCBPL)

include(cmake/print.cmake)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

print(CMAKE_BUILD_TYPE)

# Use the generator expression $<0:> so that the specified folder is used directly, without any configuration-dependent suffix.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/$<0:>")

print(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
print(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
print(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

add_executable(ACCBPL
	"src/config.h"
	"src/main.c"
	"src/accbpl.h"
	"src/accbpl.c"
)

set_target_properties(ACCBPL PROPERTIES
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME accbpl
)

target_include_directories(ACCBPL PUBLIC
	${PROJECT_SOURCE_DIR}/src
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(ACCBPL PRIVATE
		NOMINMAX
		_CRT_SECURE_NO_WARNINGS
		WIN32_LEAN_AND_MEAN
		ACCBPL_WINDOWS
	)
	if (MSVC)
		target_compile_options(ACCBPL PRIVATE
		)
	elseif (MINGW)
		target_link_libraries(ACCBPL PRIVATE
			m
		)
		target_link_options(ACCBPL PRIVATE
			-static
			-static-libgcc
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(ACCBPL PRIVATE
			# clang stuff
		)
		target_link_options(ACCBPL PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(ACCBPL PRIVATE
		ACCBPL_LINUX
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(ACCBPL PRIVATE
			dl
			m
  			pthread
		)
		target_link_options(ACCBPL PRIVATE
			-static
			-static-libgcc
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(ACCBPL PRIVATE
			# clang stuff
		)
		target_link_options(ACCBPL PRIVATE
			-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions(ACCBPL PRIVATE
		ACCBPL_OSX
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(ACCBPL PRIVATE
		ACCBPL_DEBUG
		DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(ACCBPL PRIVATE
		ACCBPL_RELEASE
		NDEBUG
	)
endif()
