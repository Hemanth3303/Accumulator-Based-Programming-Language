file(GLOB_RECURSE ACCBPL_SRC CONFIGURE_DEPENDS "*.h" "*.c")

add_executable(accbpl
	${ACCBPL_SRC}
)

set_target_properties(accbpl PROPERTIES
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	OUTPUT_NAME accbpl
)

target_include_directories(accbpl
	PUBLIC

	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(accbpl
	PUBLIC

	PRIVATE
		ACCBPL
)

cmake_base_target_platform_definitions(accbpl ACCBPL)
cmake_base_target_architecture_definitions(accbpl ACCBPL)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(accbpl
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)

	if(MSVC)
		target_compile_options(accbpl
			PUBLIC

			PRIVATE
		)
	elseif(MINGW)
		target_link_libraries(accbpl
			PUBLIC
				m
			PRIVATE

		)
		target_link_options(accbpl
			PUBLIC

			PRIVATE
				-static
				-static-libgcc
		)
	elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(accbpl
			PUBLIC

			PRIVATE
		)
		target_link_options(accbpl
			PUBLIC

			PRIVATE
				-static
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(accbpl
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
		target_link_options(accbpl
			PUBLIC

			PRIVATE

		)
	elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(accbpl
			PUBLIC

			PRIVATE
		)
		target_link_options(accbpl
			PUBLIC

			PRIVATE

		)
	endif()

endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(accbpl
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:ACCBPL_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:ACCBPL_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:ACCBPL_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)

# POST-BUILD RESOURCE COPY

add_custom_command(
	TARGET accbpl POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/examples"
		"$<TARGET_FILE_DIR:accbpl>/examples"
	COMMENT "Copying examples folder to binary directory"
)