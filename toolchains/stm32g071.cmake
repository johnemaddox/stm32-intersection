set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(MCU_FLAGS "-mcpu=cortex-m0plus -mthumb")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -Wextra -Werror -fdata-sections -ffunction-sections" CACHE INTERNAL "C Compiler flags")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -Wall -Wextra -Werror -fdata-sections -ffunction-sections" CACHE INTERNAL "C++ Compiler flags")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "ASM Compiler flags")

set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/STM32G071RBTX_FLASH.ld -Wl,-Map=\${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs" CACHE INTERNAL "Linker flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
