//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Thu Mar 05 11:02:12 2015
// Version: v11.5 11.5.0.26
//////////////////////////////////////////////////////////////////////

`timescale 1 ns/100 ps

// Dev_Restart_after_ISP_blk
module Dev_Restart_after_ISP_blk(
    // Inputs
    CLK,
    RESETn
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  CLK;
input  RESETn;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire         CLK;
wire         Ram_intferface_0_o_reset_n;
wire   [5:0] Ram_intferface_0_o_TPSRAM_RADDR_sv;
wire         Ram_intferface_0_o_TPSRAM_REN;
wire   [5:0] Ram_intferface_0_o_TPSRAM_WADDR_sv;
wire   [7:0] Ram_intferface_0_o_TPSRAM_WD;
wire         Ram_intferface_0_o_TPSRAM_WEN;
wire         RESETn;
wire   [7:0] TPSRAM_0_RD;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire         GND_net;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign GND_net = 1'b0;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------Ram_intferface
Ram_intferface Ram_intferface_0(
        // Inputs
        .CLK               ( CLK ),
        .RESETn            ( RESETn ),
        .i_TPSRAM_RD_sv    ( TPSRAM_0_RD ),
        // Outputs
        .o_reset_n         ( Ram_intferface_0_o_reset_n ),
        .o_TPSRAM_WADDR_sv ( Ram_intferface_0_o_TPSRAM_WADDR_sv ),
        .o_TPSRAM_RADDR_sv ( Ram_intferface_0_o_TPSRAM_RADDR_sv ),
        .o_TPSRAM_WD       ( Ram_intferface_0_o_TPSRAM_WD ),
        .o_TPSRAM_WEN      ( Ram_intferface_0_o_TPSRAM_WEN ),
        .o_TPSRAM_REN      ( Ram_intferface_0_o_TPSRAM_REN ) 
        );

//--------Dev_Restart_after_ISP_blk_TAMPER2_0_TAMPER2   -   Actel:SgCore:TAMPER2:2.1.200
Dev_Restart_after_ISP_blk_TAMPER2_0_TAMPER2 TAMPER2_0(
        // Inputs
        .RESET_N              ( Ram_intferface_0_o_reset_n ),
        // Outputs
        .JTAG_ACTIVE          (  ),
        .LOCK_TAMPER_DETECT   (  ),
        .MESH_SHORT_ERROR     (  ),
        .DETECT_CATEGORY      (  ),
        .DETECT_ATTEMPT       (  ),
        .DETECT_FAIL          (  ),
        .DIGEST_ERROR         (  ),
        .SC_ROM_DIGEST_ERROR  (  ),
        .TAMPER_CHANGE_STROBE (  ) 
        );

//--------Dev_Restart_after_ISP_blk_TPSRAM_0_TPSRAM   -   Actel:SgCore:TPSRAM:1.0.101
Dev_Restart_after_ISP_blk_TPSRAM_0_TPSRAM TPSRAM_0(
        // Inputs
        .WD    ( Ram_intferface_0_o_TPSRAM_WD ),
        .WADDR ( Ram_intferface_0_o_TPSRAM_WADDR_sv ),
        .RADDR ( Ram_intferface_0_o_TPSRAM_RADDR_sv ),
        .WEN   ( Ram_intferface_0_o_TPSRAM_WEN ),
        .REN   ( Ram_intferface_0_o_TPSRAM_REN ),
        .CLK   ( CLK ),
        // Outputs
        .RD    ( TPSRAM_0_RD ) 
        );


endmodule
