/*******************************************************************************
 * (c) Copyright 2012-2013 Microsemi SoC Products Group.  All rights reserved.
 *
 *
 * SmartFusion2 In System Programming using UART interface example application to demonstrate the
 * SmartFusion2 In System Programming capabilities.
 *
 *
 *
 * SVN $Revision:  $
 * SVN $Date:  $
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mss_uart.h"
#include "mss_sys_services.h"

#define BUFFER_SIZE 4096

//*&************************************************************
uint8_t g_page_buffer[BUFFER_SIZE];
uint32_t page_read_handler(uint8_t const ** pp_next_page);
void isp_completion_handler(uint32_t value);
//dummy
void dummy_isp_completion_handler(uint32_t value);
uint32_t dummy_page_read_handler(uint8_t const ** pp_next_page);
volatile uint8_t g_isp_operation_busy = 1;
uint8_t dummy_g_page_buffer[20];
/*==============================================================================
  UART selection.

  mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;
 */

mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;
static uint32_t g_src_image_target_address = 0;
uint32_t g_bkup = 0;
uint8_t g_mode = 0;
static uint32_t g_file_size = 0;
//***********************************************************

void delay(volatile uint8_t n)
{
	while(n)
		n--;
}

size_t
UART_Polled_Rx
(
    mss_uart_instance_t * this_uart,
    uint8_t * rx_buff,
    size_t buff_size
)
{
    size_t rx_size = 0U;


    while( rx_size < buff_size )
    {
       while ( ((this_uart->hw_reg->LSR) & 0x1) != 0U  )
       {
           rx_buff[rx_size] = this_uart->hw_reg->RBR;
           ++rx_size;
       }
    }

    return rx_size;
}



int main()
{

    uint8_t rx_buff[8] ;

    MSS_UART_init( gp_my_uart,
    		MSS_UART_57600_BAUD,
                  MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

      MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);
      /* start the handshake with the host */
      START_HANDSHAKE:
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
              ;
           if(rx_buff[0] == 'h')
              MSS_UART_polled_tx( gp_my_uart, (const uint8_t * )"a", 1 );
           else
        	   goto START_HANDSHAKE;
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
              ;
           if(rx_buff[0] == 'n')
              MSS_UART_polled_tx( gp_my_uart, (const uint8_t * )"d", 1 );
           while(!(UART_Polled_Rx (gp_my_uart, rx_buff, 1 )))
              ;
           if(rx_buff[0] == 's')
              MSS_UART_polled_tx( gp_my_uart, (const uint8_t * )"h", 1 );
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
              ;
           if(rx_buff[0] == 'a')
              MSS_UART_polled_tx( gp_my_uart, (const uint8_t * )"k", 1 );
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
              ;
           if(rx_buff[0] == 'e')
			{
		       MSS_UART_polled_tx( gp_my_uart, (const uint8_t * )"r", 1 );
			}
           /* poll for starting Ack message from the host as an acknowledgment
                   that the host is ready to send file size */

			while(!(UART_Polled_Rx (gp_my_uart, rx_buff, 1 )))
			   ;
			MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"a",1);
			/*poll for mode */
			MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"m",1);
			while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
									  ;
		    g_mode  = rx_buff[0];
			/*poll for file size*/
			MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"z",1);
			while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 8 )))
			              ;
			g_file_size = atoi((const char*)rx_buff);

			MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"a",1);
			switch(g_mode)
			{
			case '0':
				MSS_SYS_start_isp(MSS_SYS_PROG_AUTHENTICATE,page_read_handler,isp_completion_handler);
				break;
			case '1':
				MSS_SYS_start_isp(MSS_SYS_PROG_PROGRAM,page_read_handler,isp_completion_handler);
				break;
			case '2':
				//dummy program
				//g_isp_operation_busy = 1;
				/*
				MSS_SYS_start_isp(MSS_SYS_PROG_PROGRAM,dummy_page_read_handler,dummy_isp_completion_handler);
				while(g_isp_operation_busy)
				{
					;//wait
				}
				delay(100000);
				*/
				MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);
				MSS_SYS_start_isp(MSS_SYS_PROG_VERIFY,page_read_handler,isp_completion_handler);
				break;
			}
			while(1)
			{

			}

}



/*==============================================================================
  ISP function to get status after completion of ISP operation.
 */

void isp_completion_handler(uint32_t value)
{
  if (value == MSS_SYS_SUCCESS)
  {

	  MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"p",1);


  }
  else
  {
	  MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"q",1);
	  MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )&value,8);
  }
}



/*==============================================================================
  function to get programming file data from host pc
 */

static uint32_t read_page_from_host_through_uart
(
    uint8_t * g_buffer,
    uint32_t length
)
{
    uint32_t num_bytes,factor,temp;

    num_bytes = length;
    char crc;
    size_t rx_size = 0;
   	uint8_t rx_buff[1];
    //Write Ack "b" to indicate beginning of the transaction from the target
    	if(g_bkup != g_src_image_target_address)
    	{
    		if(g_src_image_target_address == 0)
    			g_src_image_target_address = g_bkup;
    	}
    	if(g_src_image_target_address + length > g_file_size )
	   {
    		num_bytes = g_file_size - g_src_image_target_address;
	   }
    	if(g_src_image_target_address>= g_file_size)
    	{
    		return 0;
    	}
    	CRCFAIL:
           MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"b",1);
           //poll for Ack message from the host as an acknowledgment that the host is ready for receiving the transaction
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
           	;
           //transmit the address to the host
           temp = g_src_image_target_address/8;
           if(rx_buff[0]== 'a')
           MSS_UART_polled_tx( gp_my_uart,(const uint8_t * )&temp, 8 );
           //poll for Ack message from the host as an acknowledgment that the host received the address
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
           	;
           //transmit the returnbytes to the host
           if(rx_buff[0]== 'a')
           MSS_UART_polled_tx( gp_my_uart,(const uint8_t * )&num_bytes, 4 );

           //poll for Ack message from the host as an acknowledgment that the host received the returnbytes
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
           	;

           //read the data from the host for the request number of bytes
           if(rx_buff[0]== 'a')
        	   rx_size = UART_Polled_Rx(gp_my_uart, g_buffer, num_bytes);

           //send Ack message to indicate one transaction is done
           MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"a",1);
           //Recive 1-byte CRC for data of size num_bytes
           while(!(UART_Polled_Rx ( gp_my_uart, rx_buff, 1 )))
                      	;
           factor = 1;
           crc = 0;
           while((num_bytes-1)/factor)
           {
              crc = crc^g_buffer[factor];
              factor = factor*2;
           }
           if(crc == (char)rx_buff[0])
           {
        	   g_src_image_target_address += rx_size;
        	   g_bkup = g_bkup + rx_size;
        	   MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"a",1);
           }
           else
           {
        	   MSS_UART_polled_tx(gp_my_uart,(const uint8_t * )"n",1);
        	   goto CRCFAIL;
           }

      return rx_size;
}
/* function called by COMM_BLK for input data bit stream*/
uint32_t page_read_handler
(
    uint8_t const ** pp_next_page
)
{
    uint32_t length;

    length = read_page_from_host_through_uart(g_page_buffer, BUFFER_SIZE);
    *pp_next_page = g_page_buffer;

    return length;
}

/* function called by COMM_BLK for input data bit stream*/
uint32_t dummy_page_read_handler
(
    uint8_t const ** pp_next_page
)
{
    uint32_t length;
    int i = 0;

    for(i = 0;i<20;i++ )
    {
    	dummy_g_page_buffer[i] = '1';
    }
    length = 20;
    *pp_next_page = dummy_g_page_buffer;

    return length;
}
/*==============================================================================
  ISP function to get status after completion of ISP operation.
 */

void dummy_isp_completion_handler
(
	uint32_t value
)
{

	g_isp_operation_busy = 0;

}

