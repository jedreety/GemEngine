cmake_minimum_required(VERSION 3.10)
project(GemEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the paths to your custom include and lib directories
set(THIRD_PARTY_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Engine/ThirdParty/Include")
set(THIRD_PARTY_LIB_DIR "${CMAKE_SOURCE_DIR}/Engine/ThirdParty/Lib")

# Include directories
include_directories(${THIRD_PARTY_INCLUDE_DIR})

# Library directories
link_directories(${THIRD_PARTY_LIB_DIR})

# Source files
file(GLOB SOURCES "Engine/src/*.cpp" "Engine/src/Time/src/*.cpp" "Engine/src/Inputs/src/*.cpp" "Engine/src/Core/src/*.cpp" "Engine/src/Window/src/*.cpp")

# Executable
add_executable(GemEngine ${SOURCES})

# Set compiler options for the GemEngine target
if (MSVC)
    target_compile_options(GemEngine PRIVATE /utf-8)
endif()

# Link libraries
# Replace 'YourLibraryName' with the actual names of the libraries you need
target_link_libraries(GemEngine vulkan-1 SDL2 SDL2main spdlogd)
