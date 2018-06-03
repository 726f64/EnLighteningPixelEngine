/*
 * File:   Effects.c
 * Author: rodders
 *
 * Created on 27 October 2017, 08:46
 * 
 * New LED Firework design for Xmas 2017 - a catherine wheel
 */






#include <xc.h>
#include "Effects.h"
#include "System.h"
#include <stdint.h>
#include "Processor.h"
#include <stdbool.h>

extern struct Pixel SparklePatternA[PatternSize];
extern struct Pixel SparklePatternB[PatternSize];

//extern struct Pixel DisplayRAM[RAMsize];
extern volatile uint8_t DisplayRAM[NumPixels*3] DisplayRAMStart

// Set every pixel in the display RAM to the same colour - typically used for testing or setting to off
void SetAllSameColour(struct Pixel ThisColour){
    // Set all the Display RAM to zero values
    for (uint8_t ThisPixel=0; (ThisPixel<NumPixels);ThisPixel++){
        SetDisplayRAM(ThisPixel,ThisColour);
    }
    return;
}

// Set every pixel in the display RAM to the same colour - typically used for testing or setting to off
void RotateRAM(){
    // Rotate RAM along and fade
    struct Pixel TempPixel;
    
    for (uint8_t ThisPixel=0; (ThisPixel<(RAMsize-1));ThisPixel=ThisPixel+3){
        TempPixel.Red=DisplayRAM[ThisPixel];
        TempPixel.Green=DisplayRAM[ThisPixel+1];
        TempPixel.Blue=DisplayRAM[ThisPixel+2];
    }
    return;
}


void InitPatternA(void){
    SparklePatternA[0]=pBlack;
    SparklePatternA[1]=pRed;
    SparklePatternA[2]=pBlack;
    SparklePatternA[3]=pOrange;
    SparklePatternA[4]=pBlack;
    SparklePatternA[5]=pRed;
    SparklePatternA[6]=pBlack;
    SparklePatternA[7]=pRed;
    SparklePatternA[8]=pOrange;    
    SparklePatternA[9]=pWhite;     
    SparklePatternA[10]=pLightYellow;    
    SparklePatternA[11]=pRed; 
    SparklePatternA[12]=pOrange; 
    SparklePatternA[13]=pOrange;    
    SparklePatternA[14]=pBlack;     
    SparklePatternA[15]=pLightYellow;    
    SparklePatternA[16]=pWhite; 
    SparklePatternA[17]=pOrange;     
    SparklePatternA[18]=pLightYellow;    
    SparklePatternA[19]=pRed;        
}

void InitPatternB(void){
    SparklePatternB[0]=pWhite;
    SparklePatternB[1]=pWhite;
    SparklePatternB[2]=pOrange;
    SparklePatternB[3]=pOrange;
    SparklePatternB[4]=pYellow;
    SparklePatternB[5]=pYellow;
    SparklePatternB[6]=pLightYellow;
    SparklePatternB[7]=pLightYellow;
    SparklePatternB[8]=pBlack;    
    SparklePatternB[9]=pBlack;     
    SparklePatternB[10]=pBlack;    
    SparklePatternB[11]=pBlack; 
    SparklePatternB[12]=pBlack; 
    SparklePatternB[13]=pBlack;    
    SparklePatternB[14]=pBlack;     
    SparklePatternB[15]=pBlack;    
    SparklePatternB[16]=pBlack; 
    SparklePatternB[17]=pBlack;     
    SparklePatternB[18]=pBlack;    
    SparklePatternB[19]=pBlack;        
}



//Ripple the whole chain of LEDS one way or the other
void Ripple(struct Pixel NextPixel, enum  RippleDirections Direction){
    struct Pixel TempPixel;
    
    bool Finished=false;
    uint8_t Index=48;
    while(!Finished){
        TempPixel.Red=DisplayRAM[(Index*3)];
        TempPixel.Green=DisplayRAM[((Index*3)+1)];        
        TempPixel.Blue=DisplayRAM[((Index*3)+2)];        
        
        DisplayRAM[((Index+1)*3)]=TempPixel.Red;
        DisplayRAM[(((Index+1)*3)+1)]=TempPixel.Green;        
        DisplayRAM[(((Index+1)*3)+2)]=TempPixel.Blue;  
        
        if (Index==0) Finished=true;
        else Index--;
    } 
    
    // And then the feed in
        DisplayRAM[0]=NextPixel.Red;
        DisplayRAM[1]=NextPixel.Green;        
        DisplayRAM[2]=NextPixel.Blue;
        
    return;
}

