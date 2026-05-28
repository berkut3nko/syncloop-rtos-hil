cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME FreeRTOSonSTM32)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Add option to enable tests.
# Defaults to OFF, so the project builds for STM32 by default.
option(BUILD_TESTING "Build Host Unit Tests" OFF)

if(BUILD_TESTING)
    # ---------------------------------------------------------
    # MODE 1: Host Build for Unit Tests
    # ---------------------------------------------------------
    project(${CMAKE_PROJECT_NAME}_tests C)
    
    # Enable testing support in CMake
    enable_testing()
    
    # Include the tests directory
    add_subdirectory(tests)

else()
    # ---------------------------------------------------------
    # MODE 2: Cross-compile Build for STM32 (Original Code)
    # ---------------------------------------------------------
    
    # Core project settings
    project(${CMAKE_PROJECT_NAME})
    message("Build type: " ${CMAKE_BUILD_TYPE})

    # Enable CMake support for ASM and C languages
    enable_language(C ASM)

    # Create an executable object type
    add_executable(${CMAKE_PROJECT_NAME})

    # Add STM32CubeMX generated sources
    add_subdirectory(cmake/stm32cubemx)

    # Link directories setup
    target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined library search paths
    )

    # Add sources to executable
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user sources here
    )

    # Add include paths
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined include paths
    )

    # Add project symbols (macros)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined symbols
    )

    # Print firmware size after a successful build
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    )
endif()