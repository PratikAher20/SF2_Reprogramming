set_device \
    -fam SmartFusion2 \
    -die PA4M7500_TS \
    -pkg fg484
set_input_cfg \
	-path {F:/11.8/sf2_isp_using_uart_interface_demo_df/host_tool_and_samples/LSRAM_Workaround/component/work/demo_MSS/ENVM.cfg}
set_output_efc \
    -path {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.efc}
set_proj_dir \
    -path {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround}
gen_prg -use_init false
