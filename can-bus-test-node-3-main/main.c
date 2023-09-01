 /**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26K83
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

const unsigned long canId = 3; 


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    uCAN_MSG ReceiveMsg;
    uCAN_MSG SendMsg;
    SendMsg.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    SendMsg.frame.id = canId; 
    SendMsg.frame.dlc = 1; 
    SendMsg.frame.data0 = 0x33;
    uint8_t x = 0;
    //LATCbits.LC2 = 1;
    //__delay_ms(100);
    //LATCbits.LC2 = 0;
    //CAN_transmit(&SendMsg);
    while (1)
    {
        // Add your application code
        /*
        while(!x){
            x = CAN_transmit(&SendMsg);
            LATCbits.LC2 = 1;
            
        }
        x = 0;        
        LATCbits.LC2 = 0;
        __delay_ms(2000);
        
        */
        
        if(CAN_receive(&ReceiveMsg)){
           LATCbits.LC2 = 1;
           __delay_ms(3000);
           LATCbits.LC2 = 0;
           if(ReceiveMsg.frame.data0 == 0x32){
           while(!x){
            x = CAN_transmit(&SendMsg);
            //LATCbits.LC2 = 1;
            
            }
            x = 0;
            }
        }
         
        
    }
}
/**
 End of File
*/