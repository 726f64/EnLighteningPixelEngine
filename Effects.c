/*
 * File:   Effects.c
 * Author: rodders
 *
 * Created on 27 October 2017, 08:46
 * 
 * New LED Firework design for Xmas 2017 - a catherine wheel
 */


#include <xc.h>
#include "stdint.h"
#include "Effects.h"
#include "System.h"



uint8_t SelectPattern(void) {

    uint8_t PatternChoice;
    
    return PatternChoice;
}

// Rotate the inner spiral by one pixel - requires direction and what pixel to feed in
//void RotateWheel(uint8_t Direction, EffectsSpiral AppliedEffect, Pixel FeedInPixel){
void RotateWheel(uint8_t Direction, enum EffectsSpiral AppliedEffect,struct Pixel FeedInPixel){
    
    struct Pixel PixelToMove;
    
    for (uint8_t Index=NumSpiral; Index>1;Index--){       //eg 50 to 2 e.g. all but 1st element !
        PixelToMove=DisplayRAM[Index-2];                 // -1 for array eg 49=last element, -1 for pixel before it
        //Change the Pixel according to the effect...
        if (AppliedEffect==0){
            PixelToMove=PixelToMove;
        }
        else if (AppliedEffect==1){
            
        }
        else {
            PixelToMove.Blue=0;
            PixelToMove.Red=0;
            PixelToMove.Green=0;
        }
        
        DisplayRAM[Index-1]=PixelToMove;
    }
    
    // Now feed in new Pixel to the 1st element
    // XXXX
    
    
}

//Make the selected arm spark outwards/inwards
void Sparks(uint8_t Direction, uint8_t SelectedArm){

    struct Pixel PixelToMove;
    uint8_t IndexOffset=NumSpiral+((SelectedArm-1)*NumArmPixels);

    for (uint8_t Index=NumArmPixels; Index>1; Index--){
        PixelToMove=DisplayRAM[Index-2+IndexOffset];                
        DisplayRAM[Index-1]=PixelToMove;   
    }

    //Now feed into 1st element of this arm

    
    
}

void OutputDisplayRAM(void){
    uint8_t RedLED;
    uint8_t GreenLED;    
    uint8_t BlueLED;       
    
    for (int i=0; i< RAMsize; i++){
        
        RedLED=DisplayRAM[i].Red;
        GreenLED=DisplayRAM[i].Green;
        BlueLED=DisplayRAM[i].Blue;
        
        //OUTPUT TO PWMs
        
    }    
}

