################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Clock.d_raw" -MT"Clock.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LaunchPad.d_raw" -MT"LaunchPad.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MCP4921.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/MCP4921.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"MCP4921.d_raw" -MT"MCP4921.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/SPI.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"SPI.d_raw" -MT"SPI.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735_SDC.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/ST7735_SDC.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ST7735_SDC.d_raw" -MT"ST7735_SDC.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: C:/Users/jonat/OneDrive/Documents/UT\ 2026-2027/ECE\ 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/inc/Timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Timer.d_raw" -MT"Timer.o" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


