set(APP_SOURCES
    intersection.c
    state_machine.c
)

# STM32 Target
if(CMAKE_CROSSCOMPILING)

    target_sources(${CMAKE_PROJECT_NAME}.elf PRIVATE 
        ${APP_SOURCES}
    )

# Host Target
else()

    add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${APP_SOURCES}
    )

    target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/tests
    )

    target_compile_definitions(${CMAKE_PROJECT_NAME}_lib PUBLIC NATIVE)

endif()
