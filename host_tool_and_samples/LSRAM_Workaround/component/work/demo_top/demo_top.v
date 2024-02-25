//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Mar 05 11:02:13 2015
// Version: v11.5 11.5.0.26
//////////////////////////////////////////////////////////////////////

`timescale 1 ns/100 ps

// demo_top
module demo_top(
    // Inputs
    DEVRST_N,
    MMUART_1_RXD,
    // Outputs
    LED1,
    LED2,
    LED3,
    LED4,
    MMUART_1_TXD
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  DEVRST_N;
input  MMUART_1_RXD;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output LED1;
output LED2;
output LED3;
output LED4;
output MMUART_1_TXD;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   demo_0_FAB_CCC_GL0;
wire   demo_0_MSS_READY;
wire   demo_0_POWER_ON_RESET_N;
wire   DEVRST_N;
wire   LED1_net_0;
wire   LED2_net_0;
wire   LED3_net_0;
wire   LED4_net_0;
wire   MMUART_1_RXD;
wire   MMUART_1_TXD_net_0;
wire   MMUART_1_TXD_net_1;
wire   LED1_net_1;
wire   LED2_net_1;
wire   LED3_net_1;
wire   LED4_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire   VCC_net;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net = 1'b1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign MMUART_1_TXD_net_1 = MMUART_1_TXD_net_0;
assign MMUART_1_TXD       = MMUART_1_TXD_net_1;
assign LED1_net_1         = LED1_net_0;
assign LED1               = LED1_net_1;
assign LED2_net_1         = LED2_net_0;
assign LED2               = LED2_net_1;
assign LED3_net_1         = LED3_net_0;
assign LED3               = LED3_net_1;
assign LED4_net_1         = LED4_net_0;
assign LED4               = LED4_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------BLINK_LED
BLINK_LED BLINK_LED_0(
        // Inputs
        .FAB_CLK  ( demo_0_FAB_CCC_GL0 ),
        .FAB_LOCK ( demo_0_MSS_READY ),
        // Outputs
        .LED1     ( LED1_net_0 ),
        .LED2     ( LED2_net_0 ),
        .LED3     ( LED3_net_0 ),
        .LED4     ( LED4_net_0 ) 
        );

//--------demo
demo demo_0(
        // Inputs
        .MMUART_1_RXD     ( MMUART_1_RXD ),
        .FAB_RESET_N      ( VCC_net ),
        .DEVRST_N         ( DEVRST_N ),
        // Outputs
        .MMUART_1_TXD     ( MMUART_1_TXD_net_0 ),
        .POWER_ON_RESET_N ( demo_0_POWER_ON_RESET_N ),
        .INIT_DONE        (  ),
        .FAB_CCC_GL0      ( demo_0_FAB_CCC_GL0 ),
        .FAB_CCC_LOCK     (  ),
        .MSS_READY        ( demo_0_MSS_READY ) 
        );

//--------Dev_Restart_after_ISP_blk
Dev_Restart_after_ISP_blk Dev_Restart_after_ISP_blk_0(
        // Inputs
        .CLK    ( demo_0_FAB_CCC_GL0 ),
        .RESETn ( demo_0_POWER_ON_RESET_N ) 
        );


endmodule
