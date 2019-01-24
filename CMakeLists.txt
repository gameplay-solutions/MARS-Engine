cmake_minimum_required(VERSION 3.4)

project(MARS)

if(MSVC)
	add_definitions(-c -W4)
else()
	add_definitions(-c -Wall -msse2)
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
add_definitions( -O2 )
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

file(GLOB_RECURSE HDRS
	${MARS_SOURCE_DIR}/Engine/Classes/*.h
	${MARS_SOURCE_DIR}/Engine/Classes/*.hpp
	${MARS_SOURCE_DIR}/Engine/Platform/*.h
	${MARS_SOURCE_DIR}/Engine/*.h
	${MARS_SOURCE_DIR}/Engine/*.hpp
)

file(GLOB_RECURSE SRCS
	${MARS_SOURCE_DIR}/Engine/Source/*.cpp
	${MARS_SOURCE_DIR}/Engine/Source/*.c
	${MARS_SOURCE_DIR}/Engine/Platform/*.c
	${MARS_SOURCE_DIR}/Engine/Platform/*.cpp
	${MARS_SOURCE_DIR}/Engine/*.cpp
	${MARS_SOURCE_DIR}/Engine/*.c
)

find_package(OpenGL REQUIRED)

include_directories(
	${MARS_SOURCE_DIR}/Engine/Classes
	${MARS_SOURCE_DIR}/Engine/Source
	${MARS_SOURCE_DIR}/Engine/Platform/Windows
	${MARS_SOURCE_DIR}/Engine/
	${MARS_SOURCE_DIR}/Thirdparty/Includes
	${OPENGL_INCLUDE_DIRS}
)

link_directories(
	${MARS_SOURCE_DIR}/Thirdparty/Libs
)

add_executable(MARS ${HDRS} ${SRCS})

target_link_libraries( MARS
	${OPENGL_LIBRARIES}
	glfw3.lib
	assimp.lib
	SDL2.lib
	SDL2main.lib
	SDL2test.lib
)

if(WIN32)
	string(REPLACE "/" "\\" source_path_windows "${MARS_SOURCE_DIR}/Resources")
	string(REPLACE "/" "\\" build_path_windows "${MARS_BINARY_DIR}/Resources")
	execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
else()
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${MARS_SOURCE_DIR}/Resources ${MARS_BINARY_DIR}/Resources RESULT_VARIABLE exitcode)
endif()

if(NOT ${exitcode} EQUAL 0)
	MESSAGE("SYMLINKING FAILED: ${exitcode}")
	MESSAGE("FALLING BACK TO COPYING")
endif()

file(GLOB_RECURSE RES RELATIVE ${MARS_SOURCE_DIR}/Resources/ ${MARS_SOURCE_DIR}/Resources/*.*)
foreach(file IN LISTS RES)
	configure_file(${MARS_SOURCE_DIR}/Resources/${file} ${MARS_BINARY_DIR}/Resources/${file} COPYONLY)
endforeach()

if(MSVC_IDE)
	foreach(source IN LISTS SRCS HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${MARS_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()