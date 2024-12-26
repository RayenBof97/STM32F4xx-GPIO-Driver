/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <string.h>
#include <stm32f401xx.h>

void delay(){
    int i = 0;
    for (i=0;i<200000;i++);
}

int main(void) {
    GPIOx_Handler_t GPIOLed,GPIOButton;
    //Initialise Handlers
    memset(&GPIOLed,0,sizeof(GPIOLed));
    memset(&GPIOButton,0,sizeof(GPIOButton));


    GPIOLed.pGPIOx = GPIOA;
    GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;
    GPIOLed.GPIO_PinConfig.PinOPType =  GPIO_OUT_TYPE_PP;

    GPIOButton.pGPIOx = GPIOC;
    GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    GPIOButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIOButton.GPIO_PinConfig.PinOPType = GPIO_OUT_TYPE_PP;


    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_PeriClockControl(GPIOC,ENABLE);

    GPIO_Init(&GPIOLed);
    GPIO_Init(&GPIOButton);

    //IRQ Configuration
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, IRQ_PRIO_NO15);
    GPIO_IRQITConfig(IRQ_NO_EXTI15_10,ENABLE);

    //

    while(1);

    return 0;
}

void EXTI15_10_IRQHandler(void){
	delay(); //Solve debouncing of the button
	GPIO_IRQHandling(GPIO_PIN_13);
	GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}


