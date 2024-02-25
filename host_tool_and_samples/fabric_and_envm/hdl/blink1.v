// blink1.v
/*-------------------------------------------------------------------------------
-- Title      : Custom AHB slave
-------------------------------------------------------------------------------
-- File       : blink_leds.v
-- Author     :
-- Company    : Actel Corporation
-- Device     : SmartFusion2
-- Standard   : Verilog
-------------------------------------------------------------------------------
-- Description:
-------------------------------------------------------------------------------
-- Copyright (c) 2009   Actel Corporation
--                      All rights reserved.
-------------------------------------------------------------------------------
-- Revisions  : V1.0
-------------------------------------------------------------------------------*/
module BLINK_LED (

                             input            FAB_CLK	,
                             input            FAB_LOCK	,

                             output reg       LED1	,
                             output reg       LED2	,
                             output reg       LED3	,
                             output reg       LED4

                           );

   reg  [31:0]  counter;


always@(posedge FAB_CLK or negedge FAB_LOCK)
if(~FAB_LOCK)
  begin
    counter <= 32'h00000000;
    LED1 <= 1'b0;
    LED2 <= 1'b0;
    LED3 <= 1'b0;
    LED4 <= 1'b0;
  end
else
  begin
    if(counter == 32'h01312D00)
      begin
         counter <= counter + 1;
         LED1 <= ~LED1;
         LED2 <= LED2;
         LED3 <= LED3;
         LED4 <= ~LED4;
      end
    else if(counter == 32'h02625A00)
        begin
          counter <= 32'h00000000;
          LED1 <= LED1;
          LED2 <= ~LED2;
          LED3 <= ~LED3;
          LED4 <= LED4;
        end
    else
      begin
        counter <= counter + 1;
      end
  end

endmodule