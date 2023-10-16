/*
 * File:   print_data.c
 * Author: M67252
 *
 * Created on August 29, 2023, 11:04 AM
 */


#include <xc.h>
#include <stdio.h>
#include "print_data.h"
#include "mcc_generated_files/oledC.h"
#include "mcc_generated_files/oledC_colors.h"
#include "mcc_generated_files/oledC_shapeHandler.h"
#include "mcc_generated_files/oledC_shapes.h"
#include "mcc_generated_files/delay.h"

static uint16_t backgroundColor;
double current = 0.5;
double voltage = 1.65;

char message[100];

static const uint32_t logo[] = 
{ 
    0b11111111111000000000011111111111,
    0b11111111100000000000001111111111,
    0b11111111000000000000000111111111,
    0b11111110000000000000000111111111,
    0b11111100000000000000000011111111,
    0b11111000000010000000100011111111,
    0b11111000000110000001100001111111,
    0b11110000001111000011110000111111,
    0b11110000001111100011111000111111,
    0b11110000000111100001111000011111,
    0b11110000000111110001111100001111,
    0b11110001000011110000111110001111,
    0b11110001100011111000111110001111,
    0b11110011110001111100011111001111,
    0b11110111110000111100001111001111,
    0b11111111100000111100001111111111,
    0b11111111100000011100000111111111,
    0b11111111000000011000000011111111,
    0b11111110000000000000000011111111,
    0b11111110000000000000000001111111,
    0b11111110000000000000000001111111,
    0b11111111100000000000000111111111,
    0b11111111111000000000011111111111
};

void setUpOled(void) {  
    setBackgroundColor(OLEDC_COLOR_BLACK);
    shape_params_t params;
    params.bitmap.color = OLEDC_COLOR_RED;
    params.bitmap.x = 14;
    params.bitmap.y = 25;
    params.bitmap.sx = 2;
    params.bitmap.sy = 2;
    params.bitmap.bit_array = (uint32_t *) & logo[0];
    params.bitmap.array_length = 23;
    oledC_addShape(0, OLED_SHAPE_BITMAP, &params);
    oledC_redrawAll();
    DELAY_milliseconds(5000);
    clearOledScreen(OLEDC_COLOR_BLACK);

}

void setBackgroundColor(uint16_t color) {
    backgroundColor = color;
    clearOledScreen(OLEDC_COLOR_BLACK);
}

void clearOledScreen(uint16_t color) {   
    oledC_DrawRectangle(0,0,95,95,color);
}

void print_data(void){
    
    clearOledScreen(OLEDC_COLOR_BLACK);
    sprintf(message, "Current: %.1f A    ",current);
    oledC_DrawString(2, 20, 1, 2, message, GREEN);
    sprintf(message , "Voltage: %.lf V   ", voltage);
    oledC_DrawString(2, 40, 1, 2, message, GREEN);       
}

