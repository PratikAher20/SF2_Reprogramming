################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_uart/mss_uart.c 

OBJS += \
./drivers/mss_uart/mss_uart.o 

C_DEPS += \
./drivers/mss_uart/mss_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_uart/%.o: ../drivers/mss_uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\CMSIS" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers\mss_hpdma" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers\mss_nvm" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers\mss_sys_services" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers\mss_timer" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers\mss_uart" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers_config" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\drivers_config\sys_config" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\hal" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\hal\CortexM3" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\SoftConsole\demo_MSS_CM3_boot_loader\hal\CortexM3\GNU" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


