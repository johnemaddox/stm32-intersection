cmake_minimum_required(VERSION 3.16.3)

## Dependencies ##

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY_EXE})
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
else()
    message(STATUS "clang-tidy not found; skipping static analysis during compilation.")
endif()

## Project ##

get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}" NAME)
project(${PARENT_DIR} LANGUAGES C ASM) # CXX is added for HOST to support GoogleTest

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# STM32 Target
if(CMAKE_CROSSCOMPILING)
    message(STATUS "Configuring for Target STM32G071RB")
    
    # Preprocessor definitions for HAL & Device
    add_compile_definitions(STM32G071xx USE_HAL_DRIVER)

    add_compile_options(-Wall -Werror -Wextra -fdata-sections -ffunction-sections)

    set(DRIVER_DIR ${CMAKE_SOURCE_DIR}/drivers)

    # CMSIS & HAL Headers
    include_directories(
        include
        src/hw
        ${DRIVER_DIR}/CMSIS/Core/Include
        ${DRIVER_DIR}/CMSIS/Device/ST/STM32G0xx/Include
        ${DRIVER_DIR}/STM32G0xx_HAL_Driver/Inc
    )

    # Compile STM32 HAL drivers as a separate static library target to bypass clang-tidy
    add_library(stm32g0_hal STATIC
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_cortex.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc_ex.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_gpio.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr_ex.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash.c"
        "${DRIVER_DIR}/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash_ex.c"
    )
    if(CLANG_TIDY_EXE)
        set_target_properties(stm32g0_hal PROPERTIES
            C_CLANG_TIDY ""
        )
    endif()

    add_executable(${CMAKE_PROJECT_NAME}.elf)
    target_link_libraries(${CMAKE_PROJECT_NAME}.elf PRIVATE stm32g0_hal)

    # Ensure output is named appropriately
    set_target_properties(${CMAKE_PROJECT_NAME}.elf PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}.elf")
endif()

add_subdirectory(src)

# Host Target
if(NOT CMAKE_CROSSCOMPILING)
    if(NOT CMAKE_BUILD_TYPE OR NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
    endif()

    message(STATUS "Configuring for Host (Unit Testing) - Build Type: ${CMAKE_BUILD_TYPE}")
    
    # Compiler options for host
    enable_language(CXX)
    add_compile_options(-Wall -Werror -Wextra)

    add_subdirectory(tests)
endif()
