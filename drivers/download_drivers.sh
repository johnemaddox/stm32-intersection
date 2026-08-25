#!/bin/bash
set -euo pipefail

# Download official STM32CubeG0
echo "Cloning STM32CubeG0 Drivers..."
rm -rf temp_cube drivers/CMSIS drivers/STM32G0xx_HAL_Driver
git clone --depth 1 --branch v1.6.2 --recurse-submodules --shallow-submodules https://github.com/STMicroelectronics/STM32CubeG0.git temp_cube

mkdir -p drivers
mv temp_cube/Drivers/CMSIS drivers/CMSIS
mv temp_cube/Drivers/STM32G0xx_HAL_Driver drivers/STM32G0xx_HAL_Driver
rm -rf temp_cube

echo "Drivers successfully set up in 'drivers/'"
