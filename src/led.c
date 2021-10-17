#include "led.h"
#include "stm32l031xx.h"

Led led_array[21]={{LED_CTRL_3,LED_CTRL_0},
    {LED_CTRL_2,LED_CTRL_1},
    {LED_CTRL_5,LED_CTRL_0},
    {LED_CTRL_4,LED_CTRL_0},
    {LED_CTRL_4,LED_CTRL_5},
    {LED_CTRL_1,LED_CTRL_0},
    {LED_CTRL_2,LED_CTRL_0},
    {LED_CTRL_2,LED_CTRL_4},
    {LED_CTRL_2,LED_CTRL_5},
    {LED_CTRL_3,LED_CTRL_4},
    {LED_CTRL_3,LED_CTRL_5},
    {LED_CTRL_1,LED_CTRL_4},
    {LED_CTRL_1,LED_CTRL_5},
    {LED_CTRL_2,LED_CTRL_3},
    {LED_CTRL_0,LED_CTRL_4},
    {LED_CTRL_0,LED_CTRL_5},
    {LED_CTRL_1,LED_CTRL_2},
    {LED_CTRL_1,LED_CTRL_3},
    {LED_CTRL_0,LED_CTRL_1},
    {LED_CTRL_0,LED_CTRL_2},
    {LED_CTRL_0,LED_CTRL_3}};



void blink_led(uint8_t gpio_anode,uint8_t gpio_cathode)
{
    GPIOA->MODER |= ((1<<(gpio_anode*2))|(1<<(gpio_cathode*2)));
    GPIOA->MODER &= ~((1<<(gpio_anode*2+1))|(1<<(gpio_cathode*2+1)));
    GPIOA->ODR |= (1 << gpio_anode);
    GPIOA->ODR &= ~(1 << gpio_cathode);
    GPIOA->MODER |= ((1<<(gpio_anode*2))|(1<<(gpio_cathode*2)));
    GPIOA->MODER |=((1<<(gpio_anode*2+1))|(1<<(gpio_cathode*2+1)));

}

void blink_led_struct(Led led)
{
    GPIOA->MODER |= ((1<<(led.anode*2))|(1<<(led.cathode*2)));
    GPIOA->MODER &= ~((1<<(led.anode*2+1))|(1<<(led.cathode*2+1)));
    GPIOA->ODR |= (1 << led.anode);
    GPIOA->ODR &= ~(1 << led.cathode);
    GPIOA->MODER |= ((1<<(led.anode*2))|(1<<(led.cathode*2)));
    GPIOA->MODER |=((1<<(led.anode*2+1))|(1<<(led.cathode*2+1)));
}

void bcd_to_display(uint32_t bcd_data)
{
    for(int i=0;i<22;i++)
    {
        if((bcd_data >> i) & 1)
            blink_led_struct(*(led_array+i));
    }
}

void led_test(void)
{
    blink_led(LED_CTRL_0,LED_CTRL_1);
    blink_led(LED_CTRL_0,LED_CTRL_2);
    blink_led(LED_CTRL_0,LED_CTRL_3);
    blink_led(LED_CTRL_0,LED_CTRL_4);
    blink_led(LED_CTRL_0,LED_CTRL_5);
    blink_led(LED_CTRL_1,LED_CTRL_2);
    blink_led(LED_CTRL_1,LED_CTRL_3);
    blink_led(LED_CTRL_1,LED_CTRL_4);
    blink_led(LED_CTRL_1,LED_CTRL_5);
    blink_led(LED_CTRL_2,LED_CTRL_3);
    blink_led(LED_CTRL_2,LED_CTRL_4);
    blink_led(LED_CTRL_2,LED_CTRL_5);
    blink_led(LED_CTRL_3,LED_CTRL_4);
    blink_led(LED_CTRL_3,LED_CTRL_5);
    blink_led(LED_CTRL_4,LED_CTRL_5);
    blink_led(LED_CTRL_1,LED_CTRL_0);
    blink_led(LED_CTRL_2,LED_CTRL_0);
    blink_led(LED_CTRL_3,LED_CTRL_0);
    blink_led(LED_CTRL_2,LED_CTRL_1);
    blink_led(LED_CTRL_5,LED_CTRL_0);
    blink_led(LED_CTRL_4,LED_CTRL_0);
}

void led_test_array(Led *led_arr)
{
    uint8_t i=0u;
    uint32_t dummy_delay=0u;
    while(i<22u)
    {
        dummy_delay++;
        if(dummy_delay>1000)//5000 for 1sec
        {
            dummy_delay=0;
            i++;
        }
        blink_led_struct(*(led_arr+i));
    }

}

void set_time(uint8_t hours,uint8_t min,uint8_t sec,Time *time_struct)
{
    time_struct->hours=hours;
    time_struct->min=min;
    time_struct->sec=sec;
}
void time_to_binary(Time time)
{
    switch((time.sec)%10)
    {
        case(1):
            blink_led(LED_CTRL_3,LED_CTRL_0);
            break;
        case(2):
            blink_led(LED_CTRL_2,LED_CTRL_1);
            break;
        case(3):
            blink_led(LED_CTRL_3,LED_CTRL_0);
            blink_led(LED_CTRL_2,LED_CTRL_1);
            break;
        case(4):
            blink_led(LED_CTRL_5,LED_CTRL_0);
            break;
        case(5):
            blink_led(LED_CTRL_5,LED_CTRL_0);
            blink_led(LED_CTRL_3,LED_CTRL_0);
            break;
        case(6):
            blink_led(LED_CTRL_5,LED_CTRL_0);
            blink_led(LED_CTRL_2,LED_CTRL_1);
            break;
        case(7):
            blink_led(LED_CTRL_5,LED_CTRL_0);
            blink_led(LED_CTRL_3,LED_CTRL_0);
            blink_led(LED_CTRL_2,LED_CTRL_1);
            break;
        case(8):
            blink_led(LED_CTRL_4,LED_CTRL_0);
            break;
        case(9):
            blink_led(LED_CTRL_4,LED_CTRL_0);
            blink_led(LED_CTRL_3,LED_CTRL_0);
            break;
        default:
            break;
    }

    switch(time.sec/10)
    {
        case(1):
            blink_led(LED_CTRL_4,LED_CTRL_5);
            break;
        case(2):
            blink_led(LED_CTRL_1,LED_CTRL_0);
            break;	
        case(3):
            blink_led(LED_CTRL_4,LED_CTRL_5);
            blink_led(LED_CTRL_1,LED_CTRL_0);
            break;
        case(4):
            blink_led(LED_CTRL_2,LED_CTRL_0);
            break;
        case(5):
            blink_led(LED_CTRL_2,LED_CTRL_0);
            blink_led(LED_CTRL_4,LED_CTRL_5);
            break;
        default:
            break;
    }

    switch((time.min)%10)
    {
        case(1):
            blink_led(LED_CTRL_2,LED_CTRL_4);
            break;
        case(2):
            blink_led(LED_CTRL_2,LED_CTRL_5);
            break;
        case(3):
            blink_led(LED_CTRL_2,LED_CTRL_4);
            blink_led(LED_CTRL_2,LED_CTRL_5);
            break;
        case(4):
            blink_led(LED_CTRL_3,LED_CTRL_4);
            break;
        case(5):
            blink_led(LED_CTRL_3,LED_CTRL_4);
            blink_led(LED_CTRL_2,LED_CTRL_4);
            break;
        case(6):
            blink_led(LED_CTRL_3,LED_CTRL_4);
            blink_led(LED_CTRL_2,LED_CTRL_5);
            break;
        case(7):
            blink_led(LED_CTRL_3,LED_CTRL_4);
            blink_led(LED_CTRL_2,LED_CTRL_5);
            blink_led(LED_CTRL_2,LED_CTRL_4 );
            break;
        case(8):
            blink_led(LED_CTRL_3,LED_CTRL_5);
            break;
        case(9):
            blink_led(LED_CTRL_3,LED_CTRL_5);
            blink_led(LED_CTRL_2,LED_CTRL_4);
            break;
        default:
            break;
    }
    switch(time.min/10)
    {
        case(1):
            blink_led(LED_CTRL_1,LED_CTRL_4);
            break;
        case(2):
            blink_led(LED_CTRL_1,LED_CTRL_5);
            break;
        case(3):
            blink_led(LED_CTRL_1,LED_CTRL_5);
            blink_led(LED_CTRL_1,LED_CTRL_4);
            break;
        case(4):
            blink_led(LED_CTRL_2,LED_CTRL_3);
            break;
        case(5):
            blink_led(LED_CTRL_2,LED_CTRL_3);
            blink_led(LED_CTRL_1,LED_CTRL_4);
            break;
        default:
            break;
    }
    switch((time.hours)%10)
    {
        case(1):
            blink_led(LED_CTRL_0,LED_CTRL_4);
            break;
        case(2):
            blink_led(LED_CTRL_0,LED_CTRL_5);
            break;
        case(3):
            blink_led(LED_CTRL_0,LED_CTRL_5);
            blink_led(LED_CTRL_0,LED_CTRL_4);
            break;
        case(4):
            blink_led(LED_CTRL_1,LED_CTRL_2);
            break;
        default:
            break;
    }
    switch(time.hours/10)
    {
        case(1):
            blink_led(LED_CTRL_0,LED_CTRL_1);
            break;
        case(2):
            blink_led(LED_CTRL_0,LED_CTRL_2);
            break;
        default:
            break;
    }
}
