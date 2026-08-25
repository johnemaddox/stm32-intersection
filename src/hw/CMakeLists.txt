target_sources(${CMAKE_PROJECT_NAME}.elf PRIVATE 
    system_stm32g0xx.c
    startup_stm32g071xx.s
    leds.c
)
