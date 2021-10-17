#include "stm32l031xx.h"
#include "main.h"
#include "led.h"

int main(void)
{
RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
while(1)
{
led_test();
} 
return 0;

}

