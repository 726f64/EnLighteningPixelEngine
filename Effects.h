/* 
 * File:   Effects.h
 * Author: General
 *
 * Created on October 27, 2017, 9:42 AM
 */







#ifndef EFFECTS_H
#define	EFFECTS_H

#include <stdint.h>
#include "System.h"
#include "Effects.h"



// Changing default values of enum
enum EffectsSpiral {
    NoChange = 0,
    Fade = 1,
    Brighten = 2,
};

//Make RAM space for the current display values...this can be read out to WS2812.
//struct Pixel DisplayRAM[RAMsize]@0x2000;
//volatile unsigned char motor_buffer[160] __at(0x2320); // linear memory, starting in bank 10
//volatile unsigned char motor_buffer[160] __at(0x2320); // linear memory, starting in bank 10

volatile uint8_t DisplayRAM[NumPixels*3] DisplayRAMStart

void RotateWheel(uint8_t , enum EffectsSpiral ,struct Pixel  );
void SetAllSameColour(struct Pixel);

void Sparks(uint8_t , uint8_t );
void Ripple(struct Pixel , enum RippleDirections);
    

void OutputDisplayRAM(void);
void InitPatternA(void);
void InitPatternB(void);


//Red - Green - Blue
const struct Pixel pWhite={255,255,255};
const struct Pixel pBlack={0,0,0};
const struct Pixel pRed={255,0,0};
const struct Pixel pGreen={0,255,0};
const struct Pixel pBlue={0,0,255};
const struct Pixel pYellow={255,255,0};
const struct Pixel pOrange={255,100,0};
const struct Pixel pMagenta={255,0,255};
const struct Pixel pCyan={0,255,255};
const struct Pixel pLightYellow={100,100,0};



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EFFECTS_H */


    
