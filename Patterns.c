#include "Patterns.h"
#include <stdbool.h>


struct ArmControl ArmData[NumArms];



void InitialiseArms(void){

    for (uint8_t Arm=0; Arm<(NumArms-1);Arm++){
        ArmData[Arm].FinishedMain=false;
        ArmData[Arm].FinishedRipple=false;
        ArmData[Arm].IndexPosition=0;        
        //ArmData[Arm].PatternPointer=&SparklePatternA;
        //ArmData[Arm].Length=SparklePatternA;
    }
    
}

void SetAllSameColour(struct Pixel ThisColour){
    // Set all the Display RAM to zero values
    for (uint8_t ThisPixel=0; ThisPixel<(RAMsize-1);ThisPixel++){
        DisplayRAM[ThisPixel].Blue=ThisColour.Blue;
        DisplayRAM[ThisPixel].Red=ThisColour.Red;
        DisplayRAM[ThisPixel].Green=ThisColour.Green;
    }
    
    //Output that pattern
    
}

