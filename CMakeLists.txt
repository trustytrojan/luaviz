cmake_minimum_required(VERSION 3.18)
project(luaviz LANGUAGES CXX)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.24)
	cmake_policy(SET CMP0135 NEW)
endif()

option(LUAVIZ_EXECUTABLE "Make luaviz an executable that executes Lua scripts with the binding included" OFF)
option(LUAVIZ_BUILD_LUA "Build Lua from source for luaviz" OFF)

set(BUILD_SHARED_LIBS OFF) # static preferred
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
	# for homebrew setups
	link_directories(/opt/homebrew/lib)
	include_directories(/opt/homebrew/include)
endif()

if(CMAKE_BUILD_TYPE MATCHES Rel)
	add_compile_options(-march=native)
endif()

if(WIN32)
	# using a shared library loaded by devcom's lua.exe just freezes up the system? force executable on windows
	# this COULD be only happening on my dev laptop which has hybrid graphics... test on other systems.
	# but since a standalone executable works basically the same way, this is a sane default.
	set(LUAVIZ_EXECUTABLE ON CACHE BOOL "" FORCE)
endif()

file(GLOB LUAVIZ_SOURCES src/*.cpp)

if(LUAVIZ_EXECUTABLE)
	add_executable(luaviz ${LUAVIZ_SOURCES} src/exe/main.cpp)
else()
	add_library(luaviz MODULE ${LUAVIZ_SOURCES} src/lib/extern.cpp)
	set_target_properties(luaviz PROPERTIES PREFIX "") # remove `lib` prefix from filename
endif()

include(deps.cmake)

target_include_directories(luaviz PUBLIC include)
target_link_libraries(luaviz PUBLIC audioviz)
