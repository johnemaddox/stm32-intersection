# STM32 Target
if(CMAKE_CROSSCOMPILING)

    target_sources(${CMAKE_PROJECT_NAME}.elf PRIVATE 
        main.c
    )

    add_subdirectory(hw)

endif()

# Host target does not use main.c or hw/*. Skip to app directory.

add_subdirectory(app)
