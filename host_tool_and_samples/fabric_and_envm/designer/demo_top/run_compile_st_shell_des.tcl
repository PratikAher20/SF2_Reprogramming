set_device \
    -family  SmartFusion2 \
    -die     PA4M7500_TS \
    -package fg484 \
    -speed   -1 \
    -tempr   {COM} \
    -voltr   {COM}
set_def {VOLTAGE} {1.2}
set_def {VCCI_1.2_VOLTR} {COM}
set_def {VCCI_1.5_VOLTR} {COM}
set_def {VCCI_1.8_VOLTR} {COM}
set_def {VCCI_2.5_VOLTR} {COM}
set_def {VCCI_3.3_VOLTR} {COM}
set_def USE_TCGEN 1
set_def NETLIST_TYPE EDIF
set_name demo_top
set_workdir {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\designer\demo_top}
set_log     {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\fabric_and_envm\designer\demo_top\demo_top_sdc.log}
set_design_state pre_layout
