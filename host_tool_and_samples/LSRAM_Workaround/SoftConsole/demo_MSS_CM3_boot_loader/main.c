/*******************************************************************************
 * (c) Copyright 2012-2013 Microsemi SoC Products Group.  All rights reserved.
 *
 *
 * SmartFusion2 In System Programming using UART interface example application to demonstrate the
 * SmartFusion2 In System Programming capabilities.
 * This Application is start up for the demo to copy the ISP appication to eSRAM to execute the code form eSRAM.
 *
 *
 *
 * SVN $Revision:  $
 * SVN $Date:  $
 */


#include "m2sxxx.h"
#include "mss_uart.h"
#define ESRAM0_REMAP_BASE_ADDR 0x20000000
#define ENVM_ISPDEMO_IMAGE_STORED_ADDR 0x60020000
mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;

/* function to copy code to eSRAM*/
void copy_image_to_esram()
{
    unsigned int ii=0;
    unsigned long *exeDestAddr, *exeSrcAddr;
	exeDestAddr = (unsigned long *)ESRAM0_REMAP_BASE_ADDR;
	exeSrcAddr = (unsigned long *)ENVM_ISPDEMO_IMAGE_STORED_ADDR;
	/* 60 K B = 60 KB /4 ptr increments by 4bytes*/
	for (ii=0; ii<15360; ii++ )
	{
		*exeDestAddr++ = *exeSrcAddr++;
	}
}
/* function to remap eSRAM to cortex - M3 code region*/
void remap_user_code_eSRAM_0(void)
{
   int * address = (int *)0x20000004; 		//pointer to reset handler of application
   __set_MSP(*(int*)0x20000000); 			//set the stack pointer to that of the application
   SYSREG->ESRAM_CR |= 0x1;
   ((void (*)())(*address))(); 				// pointer recast as function pointer and the dereferenced/called
   while(1){ }; 						    //This instruction never executed
}

int main()
{



		/* Initialization all necessary hardware components */
	    MSS_UART_init( gp_my_uart,
	        		MSS_UART_57600_BAUD,
	                      MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	    MSS_UART_polled_tx_string(gp_my_uart,(uint8_t *)"\n\r\n\r*** SmartFusion2 ISP Demo ***\n\r");

		MSS_UART_polled_tx_string(gp_my_uart,(uint8_t *)"\n\rRemmaping the main application code to eSRAM_0 \n\r");
		copy_image_to_esram();
		remap_user_code_eSRAM_0();
		while(1)
		{
	          // execution never comes here
		}

	    return 0;
}
