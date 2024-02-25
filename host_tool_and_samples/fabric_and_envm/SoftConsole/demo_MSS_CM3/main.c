#include "mss_uart.h"
#include "mss_timer.h"
#include "system_m2sxxx.h"
#include <stdio.h>
#define DELAY 80000

const uint8_t greating[] = "\rISP programming successful. LEDs are blinking\n\r";
void delay(volatile uint32_t n)
{
	while(n!=0)
	{
	    n--;
	}
}
void Timer1_IRQHandler(void)
{
	MSS_UART_polled_tx( &g_mss_uart1, greating, sizeof(greating) );
	MSS_TIM1_stop();
	SystemCoreClockUpdate();
	MSS_TIM1_load_immediate(g_FrequencyPCLK0*2);
	MSS_TIM1_clear_irq();
	MSS_TIM1_start();


}

int main()
{




	 	    /* Turn off the watchdog */
	 //SYSREG->WDOG_CR = 0;
	 //SYSREG->SOFT_RST_CR &= ~SYSREG_HPDMA_SOFTRESET_MASK;// taking HPDMA out of reset
	 //MSS_HPDMA_init();
	 MSS_UART_init( &g_mss_uart1, MSS_UART_57600_BAUD, MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT );
	 MSS_UART_polled_tx( &g_mss_uart1, greating, sizeof(greating) );
	 MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);
	 MSS_TIM1_load_immediate(g_FrequencyPCLK0*2);
	 MSS_TIM1_start();
	 MSS_TIM1_enable_irq();

		while( 1 )
	 {


	 }


}