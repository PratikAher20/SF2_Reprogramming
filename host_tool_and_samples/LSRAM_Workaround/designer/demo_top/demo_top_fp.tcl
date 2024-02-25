new_project \
         -name {demo_top} \
         -location {F:\Microsemi\work\isp_uart\sf2_isp_using_uart_interface_demo_df\libero\designer\demo_top\demo_top_fp} \
         -mode {chain} \
         -connect_programmers {FALSE}
add_actel_device \
         -device {M2S090TS} \
         -name {M2S090TS}
enable_device \
         -name {M2S090TS} \
         -enable {TRUE}
save_project
close_project
