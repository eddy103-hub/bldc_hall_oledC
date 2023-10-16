/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include <bits/alltypes.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "stdio.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/X2Cscope/X2Cscope.h"
#include "mcc_generated_files/pwm.h"
#include"mcc_generated_files/spi1_driver.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "print_data.h"
#include "constants.h"

// Block Commutation
const uint16_t PWM_STATE1[8] = {0x3000, 0x3400, 0x3000, 0x1000, 0x1000, 0x3000, 0x3400, 0x3000};
const uint16_t PWM_STATE2[8] = {0x3000, 0x3000, 0x3400, 0x3400, 0x3000, 0x1000, 0x1000, 0x3000};
const uint16_t PWM_STATE3[8] = {0x3000, 0x1000, 0x1000, 0x3000, 0x3400, 0x3400, 0x3000, 0x3000};

// Hall sequence translated to block sequence
uint8_t commutation_sector[8] = {0, 1, 5, 6, 3, 2, 4, 0};

uint16_t state = 0;
uint16_t duty_cycle = MIN_DUTY;
uint16_t speed = 10;

int16_t I_a;
int16_t I_b;
int16_t I_c;
double Ia,Ib,Ic;

int16_t I_sum;
int16_t V_pot;
uint8_t hall_value;
uint8_t pwm_idx;

uint8_t direction = 1;


void SW1_Interrupt(void) {
    state ^= 1;
    if (state) {
        LED2_SetHigh();
    } else {
        LED2_SetLow();
    }
}

void SW2_Interrupt(void) {
    LED1_Toggle();
}

void SW3_Interrupt(void) {
    uint8_t tmp;
    direction ^= 1;
    for (uint8_t i = 1; i < 4; i++) {
        tmp = commutation_sector[i];
        commutation_sector[i] = commutation_sector[7 - i];
        commutation_sector[7 - i] = tmp;
    }
}

void limitSpeedAndDuty() {
    if (speed >= MAX_PERIOD) {
        speed = MAX_PERIOD;
    }
    if (speed <= MIN_PERIOD) {
        speed = MIN_PERIOD;
    }
    if (duty_cycle >= MAX_DUTY) {
        duty_cycle = MAX_DUTY;
    }
    if (duty_cycle <= MIN_DUTY) {
        duty_cycle = MIN_DUTY;
    }
}

void AdcCallBack(void);


/*
                         Main application
 */
int main(void) {
    
    SYSTEM_Initialize();
    SW1_SetInterruptHandler(SW1_Interrupt);
    SW2_SetInterruptHandler(SW2_Interrupt);
    SW3_SetInterruptHandler(SW3_Interrupt);
    ADC1_SetPOT_SpeedInterruptHandler(AdcCallBack);
    setUpOled();
    TMR1_SetInterruptHandler(timerCB);
    while (1) {
        X2CScope_Communicate();
        oledTask();
    }
    return 1;
}

void PWM_Generator1_CallBack(void) {
    hall_value = (0x0007 & ((HALL_A_GetValue() << 2) + (HALL_C_GetValue() << 1) + HALL_B_GetValue()));
    pwm_idx = commutation_sector[hall_value];
    if (state) {
        PG1IOCONL = PWM_STATE1[pwm_idx];
        PG2IOCONL = PWM_STATE2[pwm_idx];
        PG4IOCONL = PWM_STATE3[pwm_idx];
    } else {
        PG1IOCONL = PWM_STATE1[0];
        PG2IOCONL = PWM_STATE2[0];
        PG4IOCONL = PWM_STATE3[0];
    }
}

void AdcCallBack(void) {


    V_pot = ADC1_ConversionResultGet(POT_Speed);

    /*current Calculation*/
    I_a = ADC1_ConversionResultGet(I_A);
    I_b = ADC1_ConversionResultGet(I_B);
   
    Ia =(double) CURRENT(I_a);
    Ib = (double)CURRENT(I_b);
    Ic = -(Ia + Ib);

    {
        duty_cycle = V_pot / 2;
        limitSpeedAndDuty();
        PG1DC = duty_cycle;
        PG2DC = duty_cycle;
        PG4DC = duty_cycle;

    }

    X2CScope_Update();

}
/**
 End of File
 */

