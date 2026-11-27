#include "stm32f401_baremetal.h"
#include "gpio.h"







void EXTI0_IRQHandler(void)
{
EXTI_PR =(1U<<0);
GPIO_Toggle(GPIOA,5);

}



int main(void)
{

	 GPIO_Config_t led_config =
	    {
	        .pin = 5,
	        .mode = GPIO_MODE_OUTPUT,
	        .pull = GPIO_NOPULL,
	        .speed = GPIO_SPEED_LOW,
	        .output_type = GPIO_PUSH_PULL,
	        .alternate = 0
	    };

	    /* PA0 = Button */
	    GPIO_Config_t button_config =
	    {
	        .pin = 0,
	        .mode = GPIO_MODE_INPUT,
	        .pull = GPIO_PULLUP,
	        .speed = GPIO_SPEED_LOW,
	        .output_type = GPIO_PUSH_PULL,
	        .alternate = 0
	    };


	    SystemClock_Config();
	    GPIO_Init(GPIOA,&led_config);
	    GPIO_Init(GPIOA,&button_config);

	    RCC_APB2ENR|=(1U<<14U);//enabled CLK for SYSCFG peripheral

	    SYSCFG_EXTICR1&=~(0x0F<<0U); //set EXTI0 for PA0

	    EXTI_FTSR|=(1<<0);
	    EXTI_IMR |=(1<<0);

	    NVIC_ISER0 |= (1U<<6);

	    while(1)
	    {
	    }

}
