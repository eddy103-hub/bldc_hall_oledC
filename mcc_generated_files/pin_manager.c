/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
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
    Section: Includes
*/

#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"

/**
 Section: File specific functions
*/
void (*HALL_B_InterruptHandler)(void) = NULL;
void (*SW1_InterruptHandler)(void) = NULL;
void (*SW3_InterruptHandler)(void) = NULL;
void (*SW2_InterruptHandler)(void) = NULL;
void (*HALL_C_InterruptHandler)(void) = NULL;

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x2014;
    LATE = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0x01FF;
    TRISC = 0x7FFF;
    TRISD = 0xFEA8;
    TRISE = 0x979E;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPDE = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;
    CNPUD = 0x0008;
    CNPUE = 0x1412;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x001F;
    ANSELB = 0x019F;
    ANSELC = 0x00CF;
    ANSELD = 0x2C00;
    ANSELE = 0x000E;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_RPCON(0x0000); // unlock PPS

    RPOR19bits.RP70R = 0x0005;    //RD6->SPI1:SDO1
    RPOR20bits.RP72R = 0x0006;    //RD8->SPI1:SCK1OUT
    RPINR18bits.U1RXR = 0x0043;    //RD3->UART1:U1RX
    RPINR20bits.SDI1R = 0x0047;    //RD7->SPI1:SDI1
    RPOR18bits.RP68R = 0x0001;    //RD4->UART1:U1TX

    __builtin_write_RPCON(0x0800); // lock PPS
    
    /****************************************************************************
     * Interrupt On Change: any
     ***************************************************************************/
    CNEN0Ebits.CNEN0E12 = 1;    //Pin : RE12
    CNEN0Ebits.CNEN0E8 = 1;    //Pin : RE8
    CNEN1Ebits.CNEN1E12 = 1;    //Pin : RE12
    CNEN1Ebits.CNEN1E8 = 1;    //Pin : RE8
    /****************************************************************************
     * Interrupt On Change: negative
     ***************************************************************************/
    CNEN1Ebits.CNEN1E4 = 1;    //Pin : RE4
    CNEN1Ebits.CNEN1E7 = 1;    //Pin : RE7
    CNEN1Ebits.CNEN1E9 = 1;    //Pin : RE9
    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    CNFEbits.CNFE12 = 0;    //Pin : RE12
    CNFEbits.CNFE4 = 0;    //Pin : RE4
    CNFEbits.CNFE7 = 0;    //Pin : RE7
    CNFEbits.CNFE8 = 0;    //Pin : RE8
    CNFEbits.CNFE9 = 0;    //Pin : RE9
    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    CNCONEbits.CNSTYLE = 1;    //Config for PORTE
    CNCONEbits.ON = 1;    //Config for PORTE
    
    /* Initialize IOC Interrupt Handler*/
    HALL_B_SetInterruptHandler(&HALL_B_CallBack);
    SW1_SetInterruptHandler(&SW1_CallBack);
    SW3_SetInterruptHandler(&SW3_CallBack);
    SW2_SetInterruptHandler(&SW2_CallBack);
    HALL_C_SetInterruptHandler(&HALL_C_CallBack);
    
    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS4bits.CNEIF = 0; //Clear CNEI interrupt flag
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void __attribute__ ((weak)) HALL_B_CallBack(void)
{

}

void __attribute__ ((weak)) SW1_CallBack(void)
{

}

void __attribute__ ((weak)) SW3_CallBack(void)
{

}

void __attribute__ ((weak)) SW2_CallBack(void)
{

}

void __attribute__ ((weak)) HALL_C_CallBack(void)
{

}

void HALL_B_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    HALL_B_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void HALL_B_SetIOCInterruptHandler(void *handler)
{ 
    HALL_B_SetInterruptHandler(handler);
}

void SW1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    SW1_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void SW1_SetIOCInterruptHandler(void *handler)
{ 
    SW1_SetInterruptHandler(handler);
}

void SW3_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    SW3_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void SW3_SetIOCInterruptHandler(void *handler)
{ 
    SW3_SetInterruptHandler(handler);
}

void SW2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    SW2_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void SW2_SetIOCInterruptHandler(void *handler)
{ 
    SW2_SetInterruptHandler(handler);
}

void HALL_C_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    HALL_C_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void HALL_C_SetIOCInterruptHandler(void *handler)
{ 
    HALL_C_SetInterruptHandler(handler);
}

/* Interrupt service routine for the CNEI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNEInterrupt ( void )
{
    if(IFS4bits.CNEIF == 1)
    {
        if(CNFEbits.CNFE4 == 1)
        {
            if(HALL_B_InterruptHandler) 
            { 
                HALL_B_InterruptHandler(); 
            }
            
            CNFEbits.CNFE4 = 0;  //Clear flag for Pin - RE4

        }
        
        if(CNFEbits.CNFE7 == 1)
        {
            if(SW1_InterruptHandler) 
            { 
                SW1_InterruptHandler(); 
            }
            
            CNFEbits.CNFE7 = 0;  //Clear flag for Pin - RE7

        }
        
        if(CNFEbits.CNFE9 == 1)
        {
            if(SW3_InterruptHandler) 
            { 
                SW3_InterruptHandler(); 
            }
            
            CNFEbits.CNFE9 = 0;  //Clear flag for Pin - RE9

        }
        
        if(CNFEbits.CNFE8 == 1)
        {
            if(SW2_InterruptHandler) 
            { 
                SW2_InterruptHandler(); 
            }
            
            CNFEbits.CNFE8 = 0;  //Clear flag for Pin - RE8

        }
        
        if(CNFEbits.CNFE12 == 1)
        {
            if(HALL_C_InterruptHandler) 
            { 
                HALL_C_InterruptHandler(); 
            }
            
            CNFEbits.CNFE12 = 0;  //Clear flag for Pin - RE12

        }
        
        
        // Clear the flag
        IFS4bits.CNEIF = 0;
    }
}

