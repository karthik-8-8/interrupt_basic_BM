\# STM32F401RE Bare-Metal External Interrupt (EXTI)



\## 1. Project Overview



This project demonstrates \*\*external interrupt programming on the STM32F401RE microcontroller using bare-metal register-level programming in C\*\*.



The objective was to understand how a microcontroller responds to an external GPIO event using interrupts instead of continuously polling the input pin.



This is my \*\*first hands-on implementation of interrupt programming\*\*.



In my earlier RP2040 bare-metal work, I explored GPIO, UART, SPI, I2C, ADC, PWM and timers, but I had not implemented interrupt programming. I chose the STM32F401RE to understand the interrupt mechanism from the register level.



\## 2. Hardware and Development Environment



\- \*\*Microcontroller:\*\* STM32F401RE

\- \*\*Development Board:\*\* NUCLEO-F401RE

\- \*\*IDE:\*\* STM32CubeIDE

\- \*\*Programming Language:\*\* C

\- \*\*Programming Approach:\*\* Bare-metal register-level programming

\- \*\*Libraries:\*\* No HAL or CMSIS peripheral driver structures used



\## 3. Project Functionality



The project uses an external interrupt connected to GPIO pin PA0.



\- PA0 is configured as the external interrupt input (EXTI0).

\- The EXTI peripheral is configured to detect a falling-edge event.

\- The NVIC is configured to enable the EXTI0 interrupt.

\- When the interrupt handler executes, it clears the pending interrupt flag.

\- The onboard LED connected to PA5 is toggled inside the interrupt handler.



The main program initializes the clock, GPIO and interrupt configuration, then enters an infinite loop.



The CPU does not need to continuously check the PA0 input in that loop. The interrupt handler is invoked when the configured interrupt event occurs.



\## 4. Interrupt Execution Flow



1\. Configure PA5 as a GPIO output for the LED.

2\. Configure PA0 as a GPIO input.

3\. Enable the SYSCFG peripheral clock.

4\. Configure the EXTI0 line to use PA0.

5\. Configure the falling-edge trigger.

6\. Unmask EXTI0 using the EXTI interrupt mask register.

7\. Enable EXTI0 in the NVIC.

8\. Wait in the main loop.

9\. When the configured external event occurs, the processor enters `EXTI0\_IRQHandler()`.

10\. Clear the EXTI pending flag and toggle the LED.



\## 5. Important Registers Used



| Register | Purpose |

|---|---|

| RCC\_AHB1ENR | Enables the GPIOA peripheral clock |

| RCC\_APB2ENR | Enables the SYSCFG peripheral clock |

| SYSCFG\_EXTICR1 | Selects GPIOA as the source for EXTI0 |

| EXTI\_FTSR | Configures falling-edge detection |

| EXTI\_IMR | Unmasks the EXTI0 interrupt |

| EXTI\_PR | Clears the pending interrupt flag |

| NVIC\_ISER0 | Enables the EXTI0 interrupt in the NVIC |

| GPIOA\_MODER | Configures GPIO pin modes |

| GPIOA\_ODR / BSRR | Controls the LED output |



\## 6. Interrupt Service Routine (ISR)



The interrupt handler implemented in this project is:



```c

void EXTI0\_IRQHandler(void)

{

&#x20;   EXTI\_PR = (1U << 0);

&#x20;   GPIO\_Toggle(GPIOA, 5);

}

```



\*\*Understanding the ISR:\*\*



\- `EXTI0\_IRQHandler()` is the interrupt service routine for EXTI line 0.

\- Writing `1` to bit 0 of `EXTI\_PR` clears the pending interrupt flag (write-one-to-clear).

\- `GPIO\_Toggle(GPIOA, 5)` changes the state of the onboard LED.



The ISR is kept short so that interrupt processing remains simple.



\## 7. Key Concepts Learned



Through this project, I gained practical exposure to:



\- The difference between polling and interrupt-based programming.

\- The role of the EXTI peripheral in detecting external events.

\- Mapping GPIO pins to EXTI lines through SYSCFG.

\- Edge-triggered interrupt configuration.

\- The role of the NVIC in enabling and managing processor interrupts.

\- Interrupt pending flags and write-one-to-clear behavior.

\- Writing and understanding an interrupt service routine.

\- Interacting with STM32 peripherals through direct register access.



\## 8. Project Structure



```text

interrupt\_basic\_BM/

│

├── Inc/

│   ├── gpio.h

│   └── stm32f401\_baremetal.h

│

├── Src/

│   ├── main.c

│   ├── gpio.c

│   └── stm32f401\_baremetal.c

│

├── Startup/

│   └── startup\_stm32f401retx.s

│

├── STM32F401RETX\_FLASH.ld

├── STM32F401RETX\_RAM.ld

├── .project

├── .cproject

└── .gitignore

```



\## 9. Learning Status and Future Improvements



This is my first step into interrupt-driven embedded programming using STM32.



The main goal was not just to make an LED toggle, but to understand how an external event travels through the EXTI peripheral and NVIC before the processor executes the corresponding interrupt handler.



\*\*Planned improvements:\*\*



\- Explore interrupt priority and preemption.

\- Understand interrupt handling for timers.

\- Implement UART interrupts.

\- Explore interrupt-driven peripheral communication.

\- Study interrupt latency and shared data between ISRs and main code.



\---



\*\*Project Status:\*\* Initial EXTI0 interrupt implementation completed.



\*\*Repository:\*\* \[interrupt\_basic\_BM](https://github.com/karthik-8-8/interrupt\_basic\_BM)# STM32F401RE Bare-Metal External Interrupt (EXTI)



\## 1. Project Overview



This project demonstrates \*\*external interrupt programming on the STM32F401RE microcontroller using bare-metal register-level programming in C\*\*.



The objective was to understand how a microcontroller responds to an external GPIO event using interrupts instead of continuously polling the input pin.



This is my \*\*first hands-on implementation of interrupt programming\*\*.



In my earlier RP2040 bare-metal work, I explored GPIO, UART, SPI, I2C, ADC, PWM and timers, but I had not implemented interrupt programming. I chose the STM32F401RE to understand the interrupt mechanism from the register level.



\## 2. Hardware and Development Environment



\- \*\*Microcontroller:\*\* STM32F401RE

\- \*\*Development Board:\*\* NUCLEO-F401RE

\- \*\*IDE:\*\* STM32CubeIDE

\- \*\*Programming Language:\*\* C

\- \*\*Programming Approach:\*\* Bare-metal register-level programming

\- \*\*Libraries:\*\* No HAL or CMSIS peripheral driver structures used



\## 3. Project Functionality



The project uses an external interrupt connected to GPIO pin PA0.



\- PA0 is configured as the external interrupt input (EXTI0).

\- The EXTI peripheral is configured to detect a falling-edge event.

\- The NVIC is configured to enable the EXTI0 interrupt.

\- When the interrupt handler executes, it clears the pending interrupt flag.

\- The onboard LED connected to PA5 is toggled inside the interrupt handler.



The main program initializes the clock, GPIO and interrupt configuration, then enters an infinite loop.



The CPU does not need to continuously check the PA0 input in that loop. The interrupt handler is invoked when the configured interrupt event occurs.



\## 4. Interrupt Execution Flow



1\. Configure PA5 as a GPIO output for the LED.

2\. Configure PA0 as a GPIO input.

3\. Enable the SYSCFG peripheral clock.

4\. Configure the EXTI0 line to use PA0.

5\. Configure the falling-edge trigger.

6\. Unmask EXTI0 using the EXTI interrupt mask register.

7\. Enable EXTI0 in the NVIC.

8\. Wait in the main loop.

9\. When the configured external event occurs, the processor enters `EXTI0\_IRQHandler()`.

10\. Clear the EXTI pending flag and toggle the LED.



\## 5. Important Registers Used



| Register | Purpose |

|---|---|

| RCC\_AHB1ENR | Enables the GPIOA peripheral clock |

| RCC\_APB2ENR | Enables the SYSCFG peripheral clock |

| SYSCFG\_EXTICR1 | Selects GPIOA as the source for EXTI0 |

| EXTI\_FTSR | Configures falling-edge detection |

| EXTI\_IMR | Unmasks the EXTI0 interrupt |

| EXTI\_PR | Clears the pending interrupt flag |

| NVIC\_ISER0 | Enables the EXTI0 interrupt in the NVIC |

| GPIOA\_MODER | Configures GPIO pin modes |

| GPIOA\_ODR / BSRR | Controls the LED output |



\## 6. Interrupt Service Routine (ISR)



The interrupt handler implemented in this project is:



```c

void EXTI0\_IRQHandler(void)

{

&#x20;   EXTI\_PR = (1U << 0);

&#x20;   GPIO\_Toggle(GPIOA, 5);

}

```



\*\*Understanding the ISR:\*\*



\- `EXTI0\_IRQHandler()` is the interrupt service routine for EXTI line 0.

\- Writing `1` to bit 0 of `EXTI\_PR` clears the pending interrupt flag (write-one-to-clear).

\- `GPIO\_Toggle(GPIOA, 5)` changes the state of the onboard LED.



The ISR is kept short so that interrupt processing remains simple.



\## 7. Key Concepts Learned



Through this project, I gained practical exposure to:



\- The difference between polling and interrupt-based programming.

\- The role of the EXTI peripheral in detecting external events.

\- Mapping GPIO pins to EXTI lines through SYSCFG.

\- Edge-triggered interrupt configuration.

\- The role of the NVIC in enabling and managing processor interrupts.

\- Interrupt pending flags and write-one-to-clear behavior.

\- Writing and understanding an interrupt service routine.

\- Interacting with STM32 peripherals through direct register access.



\## 8. Project Structure



```text

interrupt\_basic\_BM/

│

├── Inc/

│   ├── gpio.h

│   └── stm32f401\_baremetal.h

│

├── Src/

│   ├── main.c

│   ├── gpio.c

│   └── stm32f401\_baremetal.c

│

├── Startup/

│   └── startup\_stm32f401retx.s

│

├── STM32F401RETX\_FLASH.ld

├── STM32F401RETX\_RAM.ld

├── .project

├── .cproject

└── .gitignore

```



\## 9. Learning Status and Future Improvements



This is my first step into interrupt-driven embedded programming using STM32.



The main goal was not just to make an LED toggle, but to understand how an external event travels through the EXTI peripheral and NVIC before the processor executes the corresponding interrupt handler.



\*\*Planned improvements:\*\*



\- Explore interrupt priority and preemption.

\- Understand interrupt handling for timers.

\- Implement UART interrupts.

\- Explore interrupt-driven peripheral communication.

\- Study interrupt latency and shared data between ISRs and main code.



\---



\*\*Project Status:\*\* Initial EXTI0 interrupt implementation completed.



\*\*Repository:\*\* \[interrupt\_basic\_BM](https://github.com/karthik-8-8/interrupt\_basic\_BM)

