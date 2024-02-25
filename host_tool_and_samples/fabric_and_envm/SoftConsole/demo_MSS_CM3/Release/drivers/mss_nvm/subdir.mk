################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_nvm/mss_nvm.c 

OBJS += \
./drivers/mss_nvm/mss_nvm.o 

C_DEPS += \
./drivers/mss_nvm/mss_nvm.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_nvm/%.o: ../drivers/mss_nvm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\CMSIS" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\CMSIS\startup_gcc" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers\mss_hpdma" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers\mss_nvm" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers\mss_sys_services" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers\mss_timer" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers\mss_uart" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers_config" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\drivers_config\sys_config" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\hal" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\hal\CortexM3" -I"F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\SoftConsole\demo_MSS_CM3\hal\CortexM3\GNU" -std=gnu11 --specs=cmsis.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


