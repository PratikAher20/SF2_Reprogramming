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
#include "mss_nvm/mss_nvm.h"
#include "mss_spi/mss_spi.h"
#include "winbondflash.h"

#define BUFFER_SIZE 4096

//*&************************************************************
uint8_t g_page_buffer[BUFFER_SIZE];
uint8_t prog_buf[BUFFER_SIZE];
uint8_t rx_buff[BUFFER_SIZE] ;
uint32_t NVM_Read_Addr = 0x60000000;
uint32_t Flash_Read_Addr = 0x000000;
volatile uint32_t spi_offset = 0;
uint8_t g_read_buf[512];
uint32_t page_read_handler(uint8_t const ** pp_next_page);
static uint32_t read_page_from_host_through_uart
(
    uint8_t * g_buffer,
    uint32_t length
);
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

mss_uart_instance_t * const gp_my_uart = &g_mss_uart0;
static uint32_t g_src_image_target_address = 0;
uint32_t g_bkup = 0;
uint8_t g_mode = 0;
uint8_t page_read_counts = 0;
static uint32_t g_file_size = 0;
//***********************************************************


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

void delay ( volatile unsigned int n)
{
	while(n!=0)
	{
		n--;
	}
}

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


uint8_t write_to_spi(const void *buff,	/* Pointer to the data to be written */
		uint32_t btw			/* Number of bytes to write */

)
{
	volatile uint32_t ret= 0;
	const uint8_t *wbuff = (const uint8_t*)buff;
	uint32_t length = btw;
	if ((length%4) != 0)
	{
		length += (4-(length%4));
	}
	//memcpy(g_write_buf,wbuff,length);
	FLASH_program(Flash_Read_Addr+spi_offset,wbuff,length);

	flash_read(Flash_Read_Addr+spi_offset,g_read_buf,length);

	if (memcmp(g_read_buf,wbuff,length) != 0)
	{
		MSS_UART_polled_tx(gp_my_uart,"F\t",2);
		//printf("o=%d ",spi_offset);

	}
	else
	{
		MSS_UART_polled_tx(gp_my_uart,"S\t",2);
	}
	if(length>256)
	{
		//FLASH_program(destAddr+spi_offset,g_write_buf,256);
		//FLASH_program(destAddr+spi_offset+256,g_write_buf+256,length-256);
	}
	else
	{
		//FLASH_program(destAddr+spi_offset,g_write_buf,length);
	}

#if 0
	delay(5000);
	FLASH_read(destAddr+spi_offset,g_read_buf,length);  //cross check
	ret= memcmp(g_read_buf,g_write_buf,length); //cross check
	if (ret != 0)
	{
		FLASH_program(destAddr+spi_offset,g_write_buf,length);
		FLASH_read(destAddr+spi_offset,g_read_buf,length);  //cross check
		ret= memcmp(g_read_buf,g_write_buf,length); //cross check
	}
	if(ret!=0)
	{
		printf("f\t");
		//printf("1=%s\n",wbuff);
		//printf("2=%s\n",read_buf);
	}
	else
	{
		//printf("\t*\t");
	}
#endif
	spi_offset += length;
//	if(spi_offset%10240 == 0)
//	{
//		MSS_UART_polled_tx(&g_mss_uart1,".",1);
//	}
	return ret;
}



int main()
{
	nvm_status_t status;
	uint16_t length, i;
	uint8_t auth_status;
	uint8_t prog_status;
	i = 0;
	uint8_t rx_buf[1];

    for(;i<16;i++){
    	rx_buff[i] = 0;
    }
    i = 0;
    uint8_t dummy[2] = {0x90, 0xAB};
    uint8_t msg[33] = "I have been recovered with 50MHZ\n";
    uint8_t wr_cmd[] = {0x20};
    uint8_t count;
	unsigned long long int Flash_read_address = 0x000000;
	unsigned long long int NVM_Write_Addr = 0x00000;
//	unsigned long long int NVM_Read_Addr = 0x60000000;

//	NVM_Read_Addr = 0x60000000;

    MSS_UART_init(gp_my_uart, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

//    uint8_t idata[815] = {"Y"};
//	status = NVM_write(NVM_Write_Addr, dummy, sizeof(dummy), NVM_DO_NOT_LOCK_PAGE);
//
//    uint32_t *a;
//    a = (uint32_t *) NVM_Read_Addr;
//    rx_buff[0] = a[0];
//    NVM_Read_Addr += 1;
//    a = (uint32_t *) NVM_Read_Addr;
//    rx_buff[1] = a[0];
//    rx_buff[2] = a[2];
//    count = *a;
        uint8_t sr_read1 = READ_STAT_REG1;
		uint8_t sr_read3 = READ_STAT_REG3;
		uint8_t isp_status;

//while(1){
//	MSS_UART_polled_tx(gp_my_uart, msg, 33);
//}

		MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);
		MSS_SPI_init( &g_mss_spi0 );

		MSS_SPI_configure_master_mode
			(
				&g_mss_spi0,
				MSS_SPI_SLAVE_0,
				MSS_SPI_MODE3,
				8u,
				8
			);
////////
//////		isp_status = MSS_SYS_start_isp(MSS_SYS_PROG_AUTHENTICATE, page_read_handler, isp_completion_handler);
		MSS_SPI_set_slave_select( &g_mss_spi0, MSS_SPI_SLAVE_0 ); // Slave SELECT signal asserted
//		Flash_write_enable(WREN);
		g_mss_spi0.hw_reg->CONTROL |= (0x04000000);
		delay(80000);
////
////		while(1){
//			auth_status = MSS_SYS_initiate_iap(MSS_SYS_PROG_AUTHENTICATE, 0x000000);
////			wait_ready();
////		}
////
////
//		delay(80000);
//
//		if(auth_status)
//		{
//
//			MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t * )"IAP operation failed\n\r");
//
//		}
//		else
//		{
//			MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t * )"IAP operation is successful\n\r");
//
//		}

		prog_status = MSS_SYS_initiate_iap(MSS_SYS_PROG_PROGRAM, 0x000000);

		uint16_t ite_4096;
		uint8_t ite_256;
		uint8_t remain_bytes;
	//	MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
	//	MSS_SPI_transfer_block(&g_mss_spi0, CMD0, 1, rx_buf, 1);  //Reset Enable
	//	MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
	//
	//	MSS_SPI_set_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);
	//	MSS_SPI_transfer_block(&g_mss_spi0, CMD1, 1, rx_buf, 1); //Reset
	//	MSS_SPI_clear_slave_select(&g_mss_spi0, MSS_SPI_SLAVE_0);

	//	while(1){
		uint8_t device_id;
		uint8_t write_sr3[] = {0x11, 0x64};

	Read_mgf_id();

	flash_erase();

	flash_fast_read(Flash_read_address, rx_buff, sizeof(rx_buff));




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

			ite_4096 = g_file_size / 4096;


			switch(g_mode)
			{
			case '0':
				MSS_SYS_start_isp(MSS_SYS_PROG_AUTHENTICATE,page_read_handler,isp_completion_handler);
				break;
			case '1':
				MSS_SYS_start_isp(MSS_SYS_PROG_PROGRAM,page_read_handler,isp_completion_handler);
				break;
			case '2':

				MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);

//				length = read_page_from_host_through_uart(g_page_buffer, BUFFER_SIZE);
//				status = NVM_write(0x0, g_page_buffer, sizeof(g_page_buffer), NVM_DO_NOT_LOCK_PAGE);

				for(;i<ite_4096;i++){
					length = read_page_from_host_through_uart(prog_buf, BUFFER_SIZE);

					write_to_spi(prog_buf, BUFFER_SIZE);

				}

				i = 0;

				if(ite_4096 % 4096 != 0){
					if((g_file_size % 4096) < 256){
						remain_bytes = g_file_size % 4096;
						length = read_page_from_host_through_uart(prog_buf, remain_bytes);
						write_to_spi(prog_buf, remain_bytes);
					}
					else{
						ite_256 = (g_file_size % 4096) / 256;
						remain_bytes = (g_file_size % 4096) % 256;
						for(;i<ite_256;i++){
							length = read_page_from_host_through_uart(prog_buf, 256);
							write_to_spi(prog_buf, 256);
						}
						if(remain_bytes != 0){
							length = read_page_from_host_through_uart(prog_buf, remain_bytes);
							write_to_spi(prog_buf, remain_bytes);
						}
					}
				}

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

