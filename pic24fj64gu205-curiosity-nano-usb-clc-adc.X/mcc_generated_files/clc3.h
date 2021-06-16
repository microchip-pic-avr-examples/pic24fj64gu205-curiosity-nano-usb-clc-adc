/**
  CLC3 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    clc3.h

  @Summary
    This is the generated header file for the CLC3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for CLC3.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GU205
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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

#ifndef _CLC3_H
#define _CLC3_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: CLC3 APIs
*/

/**
  @Summary
    Initializes the CLC3

  @Description
    This routine configures the CLC3 specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment
    

  @Example
    <code>
    CLC3_Initialize();
    </code>
*/
void CLC3_Initialize(void);

/**
  @Summary
    Callback for CLC3.

  @Description
    This routine is callback for CLC3

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to CLC3_Initialize(); for an example
*/
void CLC3_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    CLC3_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to CLC3_Initialize(); for an example
    
*/
void CLC3_Tasks(void);

/**
  @Summary
    Returns output pin status of the CLC module.

  @Description
    This routine returns output pin status of the CLC module.

  @Param
    None.

  @Returns
    Output pin status
 
  @Example 
    <code>
    bool outputStatus;
    outputStatus = CLC3_OutputStatusGet();
    </code>
*/

bool CLC3_OutputStatusGet(void);

/******************************************************************************
*                                                                             
*    Function:			CLC3_Enable
*    Description:       Enables the CLC module                                     
*      
*	 Parameters:		None                                       
*    Return Value:      None
******************************************************************************/
inline static void CLC3_Enable(void)
{
    CLC3CONLbits.LCEN = 1;
}

/******************************************************************************
*                                                                             
*    Function:			CLC3_Disable
*    Description:       Disables the CLC module                                     
*      
*	 Parameters:		None                                       
*    Return Value:      None
******************************************************************************/
inline static void CLC3_Disable(void)
{
    CLC3CONLbits.LCEN = 0;
}

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _CLC3_H
/**
 End of File
*/

