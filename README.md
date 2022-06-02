# UARM-EE-Sentry

This is the test version of UARM sentry robot control code. 

## Available Hardware Allocation

UART

* UART7: Enabled but not used.
* USART6: Used for receive packages from micro-computer (NVIC Interrupt)
  * Preempt Priority 5, Sub Priority 1 (Supposed to be lower than Chassis)
  * UART Pin Trigger

Timer

* TIM4: PWM signal for shoot task (No interrupt)
* TIM5: Increment uwTick (Interrupt), used for timeout for hardwares.
  * Triggered each 1/1000 s
* TIM12: Buzzer (No interrupt)
* TIM13: 
  * Time counter for Chassis task (NVIC interrupt)
    * Preempt Priority 5, Sub Priority 0
    * Triggered each 1s
  * Ultrasound Sensor Timer - Not enabled
* TIM14: Not used

CAN:

* Only used for driving chassis motor(s).