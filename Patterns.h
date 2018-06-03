/* 
 * File:   Patterns.h
 * Author: General
 *
 * Created on 29 October 2017, 08:45
 */



#ifndef PATTERNS_H
#define	PATTERNS_H

#include "Effects.h"
#include "System.h"
#include <stdbool.h>

//Make RAM space for the current display values...this can be read out to WS2812.
struct Pixel DisplayRAM[RAMsize];


#ifdef	__cplusplus
extern "C" {
#endif

void SetAllSameColour(struct Pixel);

#ifdef	__cplusplus
}
#endif



const struct Pixel pWhite={255,255,255};
const struct Pixel pBlack={0,0,0};
const struct Pixel pRed={255,0,0};
const struct Pixel pGreen={0,255,0};
const struct Pixel pBlue={0,0,255};
const struct Pixel pYellow={255,255,0};
const struct Pixel pOrange={255,100,0};
const struct Pixel pMagenta={255,0,255};
const struct Pixel pCyan={0,255,255};

//const struct Pixel SparklePatternA[8];
//SparklePatternA[1].Red=pWhite.Red;
//SparklePatternA[2]=pWhite;        
//SparklePatternA[3]=pOrange;
//SparklePatternA[4]=pBlack;  



//const struct Pixel SparklePatternB[]={pWhite,pBlack,pRed,pYellow,pBlack,pMagenta,pBlack,pRed};

//A structure for the control of a single arm
struct ArmControl {
    const struct Pixel *PatternPointer;
    uint8_t Length;
    uint8_t IndexPosition;
    bool FinishedMain;              //all the pattern has been injected into the pixel arm
    bool FinishedRipple;            //the arm has rippled through another N times
}; 




//ArmContol ArmData[NumArms];
#endif	/* PATTERNS_H */