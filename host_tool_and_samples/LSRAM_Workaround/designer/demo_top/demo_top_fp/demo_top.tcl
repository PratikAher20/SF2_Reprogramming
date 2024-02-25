open_project -project {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top_fp\demo_top.pro}\
         -connect_programmers {FALSE}
load_programming_data \
    -name {M2S090TS} \
    -fpga {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.map} \
    -header {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.hdr} \
    -envm {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.efc}  \
    -spm {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.spm} \
    -dca {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\demo_top.dca}
export_single_stapl \
    -name {M2S090TS} \
    -file {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\export\demo_top.stp} \
    -secured
export_spi_master \
    -name {M2S090TS} \
    -file {F:\11.8\sf2_isp_using_uart_interface_demo_df\host_tool_and_samples\LSRAM_Workaround\designer\demo_top\export\demo_top.spi} \
    -secured
set_programming_file -name {M2S090TS} -no_file
save_project
close_project
