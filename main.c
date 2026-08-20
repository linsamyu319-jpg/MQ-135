#include<stdio.h>
#include"pico/stdlib.h"
#include"hardware/adc.h"
#include"hardware/uart.h"

#define UART_ID  uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define MQ135_ADC_PIN 26
#define MQ135_ADC_CH 0

int main(void)
{
	stdio_init_all();
	uart_init(UART_ID,BAUD_RATE);
	
	gpio_set_function(UART_TX_PIN,GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN,GPIO_FUNC_UART);
	
	adc_init();
	adc_gpio_init(MQ135_ADC_PIN);
	adc_select_input(MQ135_ADC_CH);
	
	sleep_ms(3000);

	printf("MQ135 START\n");
	uart_puts(UART_ID,"MQ135_START\r\n");

	while(true){
		uint32_t total = 0;

		for(int i = 0;i<10;i++){
			total += adc_read();
			sleep_ms(10);
		}
		uint16_t raw = total/10;

		uint32_t millivolts = ((uint32_t)raw*3300)/4095;

		printf("MQ135 RAW=%u,Voltage=%umV\n",raw,millivolts);

		char message[64];

		snprintf(message,sizeof(message),"MQ135,RAW=%u,MV=%u\r\n",raw,millivolts);
		uart_puts(UART_ID,message);
		sleep_ms(1000);
	}
	return 0 ;
}
