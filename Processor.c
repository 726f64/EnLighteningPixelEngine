
#include "Processor.h"
#include "System.h"

void FSR_Init(void){
// Ensure all Pixels are off and variables are reset. 
// Set a random arm for ignition to start on.
// Select a random feed in pattern.    

    //return;    
}



void FSR_WaitToIgnite(void){
// a random delay of 3-8 seconds     

    return;    
}
                
 
void FSR_Ignite(void){
// Ignite the chosen arm only; delay 1-3 seconds

    return;    
}  


void FSR_RunUp(void){

    // Pattern is fed into Arm 1, each step increment after (for x8 steps) start feed into other arms.
    for (uint8_t Steps=0; Steps<8; Steps++){
    
        DisplayRAM[Steps+RunInPixels]=value from Pattern;
        if (Steps>1) DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>2) DisplayRAM[Steps+RunInPixels+(2*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>3) DisplayRAM[Steps+RunInPixels+(3*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>4) DisplayRAM[Steps+RunInPixels+(4*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>5) DisplayRAM[Steps+RunInPixels+(5*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>6) DisplayRAM[Steps+RunInPixels+(6*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        if (Steps>7) DisplayRAM[Steps+RunInPixels+(7*NumArmPixels)]=value from Pattern;
                else DisplayRAM[Steps+RunInPixels+(1*NumArmPixels)]=pBlack;
        
        
        //Rotate all arms
        #define NumArms 8
#define NumArmPixels 10
    }
    

    return;    
}

                            
void FSR_MaxHold(void){
// stuff...   

    return;    
}

void FSR_SlowDown(void){
    
    return;    
}

void FSR_Stopped(void){
    
    return;    
}

void FSR_Off(void){
    // Might not need this as WaitingToIgnite is the same thing
    return;
}

void  FSR_Radial_Init(void){
    return;
}
