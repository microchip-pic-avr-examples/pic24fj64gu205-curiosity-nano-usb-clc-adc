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
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  PIC24FJ64GU205
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.35
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
#include <stdio.h>
#include "mcc_generated_files/system.h"
#include "button.h"
#include "led.h"
#include "console.h"
#include "timer_1ms.h"
#include "mcc_generated_files/usb/usb_device.h"
#include "voltage_measure.h"
#include "usb_status_indicator.h"
#include "mcc_generated_files/tmr1.h"

extern void MCC_USB_CDC_DemoTasks(void);

static bool IsWelcomeMessageNeeded(void);

static void PrintWelcomeMessage(void);
static void PrintFeaturesMessage(void);
static void PrintAnalogInputVoltage(void); 
static void PrintSwitchStatusMessage(void);

enum {
            PRINT_WELCOME,
            STATUS_READ, 
            REPEAT_SAMPLE,
            STOP
} consoleState;
            
int main(void)
{    
    SYSTEM_Initialize();
    consoleState = PRINT_WELCOME;
    LED_Enable();
    (void)TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
        
    while (1)
    { 
        USBDeviceAttach();
        switch(consoleState)
        {
            case PRINT_WELCOME:
                if(IsWelcomeMessageNeeded() == true)
                {
                    PrintWelcomeMessage();
                    PrintFeaturesMessage();
                    consoleState = STATUS_READ;
                }
                break;
            case STATUS_READ:
                    //Start Displaying status of Swith and analog input.
                    TMR1_Initialize();
                    TMR1_Start();
                    consoleState = STOP;
                break;
            case STOP:
            default:
                consoleState = STOP;
                break;
        }
        
        CONSOLE_Tasks();
        MCC_USB_CDC_DemoTasks();
        USB_STATUS_INDICATOR_Tasks();
    }

    return 1;
}

void TMR1_CallBack(void)
{
    PrintSwitchStatusMessage();
    PrintAnalogInputVoltage();
}

static bool IsWelcomeMessageNeeded(void)
{
    bool result = false;
    
    if(USBGetDeviceState() != CONFIGURED_STATE)
    {
        result = false;
    }
    else
    {
        if(BUTTON_IsPressed() == true)
        {
            if(consoleState == PRINT_WELCOME)
            {
                result = true;
            }
        }
    }
    
    return result;
}

static void PrintWelcomeMessage(void)
{
    CONSOLE_Print("\r\n");
    CONSOLE_Print("*******************************************************\r\n");
    CONSOLE_Print("PIC24FJ64GU205 Curiosity Nano Demo\r\n");
    CONSOLE_Print("*******************************************************\r\n");
}

static void PrintFeaturesMessage(void)
{
    
    CONSOLE_Print("DEMO KEY FEATURES:\r\n");
    CONSOLE_Print("1. USB CDC Class communication using the on-chip USB peripheral on PIC24FJ64GU205\r\n");
    CONSOLE_Print("2. Hardware de-bouncing of SW0 using 3 Configurable Logic Cells(CLC)\r\n");  
    CONSOLE_Print("3. Analog input conversion of RC0 using ADC with Threshold Detect\r\n\r\n\r\n");  
}

static void PrintSwitchStatusMessage(void)
{
    CONSOLE_Print("Switch status : ");
    if(BUTTON_IsPressed())
    {
        CONSOLE_Print("PRESSED  \r\n\r\n");
    }
    else
    {
        CONSOLE_Print("UNPRESSED\r\n\r\n");
    }
}

static void PrintAnalogInputVoltage(void)
{
    char strVoltage[6];
    double floatVoltage;
    floatVoltage = ADC_Channel_Voltage_Get();
    //make the number into string using sprintf function
    sprintf(strVoltage, "%.2f", floatVoltage);
    strVoltage[5] = '\0';
    CONSOLE_Print("Analog Input Conversion value(RC0): ");
    CONSOLE_Print(strVoltage);
    CONSOLE_Print(" V \r\n");
    CONSOLE_Print("\033[F\033[F\033[F");
}
    


