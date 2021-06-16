//Copyright 2016 Microchip Technology Inc. (www.microchip.com)
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "mcc_generated_files/adc1.h"

#define ANALOG_INPUT channel_AN10 //analog channel custom name
#define AVDD_REF 3.3 //AVDD referance voltage
#define ADC_12BIT_ENABLED _MODE12 //12bit  or 10bit resolution


uint16_t ADC_Channel_Value_Get (ADC1_CHANNEL adcChannel);

double ADC_Channel_Voltage_Get(void) {
    uint16_t conversionValue;
    float adcVoltage;
    conversionValue = ADC_Channel_Value_Get(ANALOG_INPUT);
    if(ADC_12BIT_ENABLED == 1)
    {
        adcVoltage = ((double)conversionValue/(double)4096)*3.3;
    }
    else
    {
        adcVoltage = ((double)conversionValue/(double)1024)*3.3;
    }
    return adcVoltage;
}

uint16_t ADC_Channel_Value_Get(ADC1_CHANNEL adcChannel) {
    uint16_t conversionValue;
    uint8_t i;
    ADC1_Initialize();
    ADC1_Enable();
    ADC1_ChannelSelect(adcChannel);
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    for(i=0;i <100;i++)
    {
    }
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(adcChannel));
    conversionValue = ADC1_ConversionResultGet(adcChannel);
    ADC1_Disable(); 
    return conversionValue;
}