/* 
 * File:   Processor.h
 * Author: General
 *
 * Created on 04 November 2017, 19:08
 */
#include "System.h"

void SetDisplayRAM(uint16_t ,  struct Pixel* ); 
void SetAllSameColour(struct Pixel* );
    
void Write_Pixels(void);
void ResetDuration(uint8_t );
void FSR_Init(void);
void FSR_WaitForFrameStart(void);
uint8_t FSR_ReadFrameBytes(void);
void FSR_OutputDisplayRAM(void);

void FSR_Test_Flash(void);
void FSR_Test_TMR1(void);
void FSR_Test_TMR2(void);
void FSR_Test_SPI1(void);
void FSR_AutoMode(void);
void FSR_StartEffectsFSR(void);


void SetPixel(uint16_t ,struct Pixel* );
struct Pixel GetPixel(uint16_t );
void ShiftPixels(uint8_t , uint8_t , uint8_t, struct Pixel *FeedIn );

void EffectsFSR_RainbowFade(uint8_t );
void EffectsFSR_FireworkEffect(uint8_t);
void EffectsFSR_NutcrackerSame(struct Pixel* ,struct Pixel* ,uint8_t ,uint8_t);
void EffectsFSR_NutcrackerAlternate(struct Pixel* ,struct Pixel* ,uint8_t,uint8_t);
void FEffectsFSR_ColourWashTwo(struct Pixel* ,struct Pixel* ,uint8_t);
void EffectsFSR_ColourWashThree(struct Pixel ,struct Pixel ,uint8_t ,uint8_t);
void EffectsFSR_Bars(struct Pixel ,struct Pixel ,uint8_t ,uint8_t);
void EffectsFSR_FadeSingleColour(struct Pixel *Colour);
void EffectsFSR_Twinkle(struct Pixel *ColourA, uint8_t,bool Rainbow );
void EffectsFSR_Fireflies(struct Pixel *ColourA, uint8_t Duration);
    


void SetTimeoutCounter(uint16_t );
void EffectsFSR_TripleFade(uint8_t);
void EffectsFSR_CatherineWheel(uint8_t );
void delay_ms(uint16_t milliseconds);


#ifndef PROCESSOR_H
#define	PROCESSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PROCESSOR_H */

