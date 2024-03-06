//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//
// DESIGNER NAME: Gavin McAllister
//
//     FILE NAME: Lab6_part2
//
//          DATE: 03/04/2024
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//
//         
//*****************************************************************************

#define LINES_PER_LCD 2
#define LINES_PER_LCD_LINE 16
#define TOTAL_LINES LINES_PER_LCD * LINES_PER_LCD_LINE
#define LINE_ONE_ADDR 0x00
#define LINE_TWO_ADDR 0x40

#define COUNT_VALUE_FINAL 0

#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
#include "csc202_lab_support.h"

void main(void) {

    uint8 a;
    uint8 i;
    uint8 runCount;
    uint8 done = FALSE;
    
    
    PLL_init();
    lcd_init();
    led_disable();
    seg7_disable();
    SW_enable();
    keypad_enable();
    
    i = 0;
    runCount = 0;
        
    while(!done) 
    {
        
        a = keyscan();
        
        if(a <= 16) 
        {
            // checks every run to see if the limit of lcd has been reached
            if(runCount >= LINES_PER_LCD_LINE)
            {
            
                set_lcd_addr(0x40 + (i / 10)); // Sets the address to bottom line
                hex2lcd(a);
                
                i++;  
                runCount++; 
                
            } /* if */
            // runs through the top line of lcd 
            else 
            {
                
              set_lcd_addr(0x00 + (i / 10));
                hex2lcd(a);
                
                i++;
                runCount++;  
            
            }      
        } /* if*/
         
        // checks to see id switch five has been pressed  
        if(SW5_down())
        {
          clear_lcd();
          set_lcd_addr(0x00);
          i = 0; 
          runCount = 0; 
        } /* if */
        // checks to see if switch 2 has been pressed
        if(SW2_down())
        {
          done = TRUE; // exits the while loop
        } /* if*/
        
        
    } /* while */
    
    clear_lcd();
    type_lcd("Program Stopped");  
        
}/* main */
