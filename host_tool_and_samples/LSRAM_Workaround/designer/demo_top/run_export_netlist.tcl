set_device -fam SmartFusion2
read_edif  \
    -file {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\synthesis\demo_top.edn}
write_verilog -file {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\synthesis\demo_top.v}
