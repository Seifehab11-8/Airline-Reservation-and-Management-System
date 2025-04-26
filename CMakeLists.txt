cmake_minimum_required(VERSION 3.10)
project(Sudoku_Project VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Enable folder support
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure source directory exists
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src")
    message(FATAL_ERROR "Source directory 'src' not found!")
endif()

# List specific source files
set(SOURCES
    src/main.cpp
    src/creation/factory/user/ConcreteUserFactory.cpp
)

set(HEADERS
    header/creation/factory/user/ConcreteUserFactory.hpp
    header/creation/factory/user/ConcreteUserFactory.hpp
    header/creation/factory/user/ConcreteUserFactory.hpp
)

# Add executable with explicit source files
add_executable(AirlineAPP ${SOURCES} ${HEADERS})

# Set output directories
set_target_properties(AirlineAPP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

# Add compiler warnings
if(MSVC)
    target_compile_options(AirlineAPP PRIVATE 
        /W3       # Lower warning level from W4 to W3
        /wd4244   # Disable specific warning about possible data loss
        # Remove /WX to not treat warnings as errors
    )
endif()