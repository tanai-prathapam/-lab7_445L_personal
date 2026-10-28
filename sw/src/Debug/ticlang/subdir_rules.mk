################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ticlang/%.o: ../ticlang/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"C:/ti/ccs2100/ccs/tools/compiler/ti-cgt-armllvm_5.1.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug" -I"C:/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_11_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ticlang/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/jonat/OneDrive/Documents/UT 2026-2027/ECE 445L/ece445l_lab7-10_fall26-4-ew-js-tp-ak/sw/src/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


