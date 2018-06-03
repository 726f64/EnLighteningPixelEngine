/*
 * File:   CatherineWheel.c
 * Author: rodders
 *
 * Created on 27 October 2017, 08:46
 * 
 * Modified existing CatherineWheel to run WS2812 strands via Vixen3 + PI zero
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "System.h"
#include "Processor.h"

void RunFSM(void);  

enum States CurrentState;
enum Effects CurrentEffect;

extern bool EffectFinished;
extern uint8_t EffectDuration;

// This is it, the main source file that runs - keep it short here !
void main(void) {
    //INTERRUPT_GlobalInterruptDisable();
    SYSTEM_Initialize();
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
       
    //If using ISR for SS2 detect...or could use FSM
    //IOCCN=0x01;
    //PIE0.IOCIE;     //used to detect SS2 going low eg start tx from RPi
    

    //Set other variables / globals etc
    Flag_FrameStart=false;
    
    //Start up the Finite State Machine
    CurrentState=Init;

    EffectFSRRunning=0;
    EffectFinished=0;
    
    RunFSM();
    
    return;
}


void RunFSM(void){
    /*
     * This Finite State Machine is meant to be clear and simple.
     * It hands off to other functions to manage each stage - keep it uncluttered
     */
    
    uint8_t FunctionReturn;
    
    while(1){
        switch (CurrentState)
            {
                case Init:
                    FSR_Init();
                    CurrentState=EffectsFSR;
                    break;

                case WaitForFrameStart:
                    FSR_WaitForFrameStart();
                    CurrentState=ReadFrame;
                    break;

                case ReadFrame:
                    FunctionReturn=FSR_ReadFrameBytes(); 
                    if (FunctionReturn==0) {
                        CurrentState=OutDisplayRAM;
                    }
                    else {
                        CurrentState=OutDisplayRAM;
                    }
                    break;               

                case OutDisplayRAM:
                    FSR_OutputDisplayRAM();
                    CurrentState=WaitForFrameStart;
                    break; 

                case TestFlash:
                    FSR_Test_Flash();
                    CurrentState=WaitForFrameStart;
                    break; 
                    
                case TestFlashRepeat:                    
                    FSR_Test_Flash();
                    CurrentState=TestFlashRepeat;
                    break;

                case TestTMR1:
                    FSR_Test_TMR1();
                    CurrentState=WaitForFrameStart;
                    break; 
                    
                case TestTMR2:
                    FSR_Test_TMR2();
                    CurrentState=WaitForFrameStart;
                    break;  
                    
                case TestSPI1:
                    FSR_Test_SPI1();
                    CurrentState=WaitForFrameStart;
                    break; 
                    
                case EffectsFSR:
                    EffectFSRRunning=1;
                    CurrentEffect=Fireflies;
                    FSR_StartEffectsFSR();
                    CurrentState=EffectsFSR;
                    break;

                default:
                    CurrentState=Init;
            }
    }
}

//Start up the Effects Finite State Machine
void FSR_StartEffectsFSR(void){
    
    
    /*while(1){
        //Use the following construct to run repeatedly through the following patterns.
     * //Add a switch and could step onwards to a desired pattern
        //EffectsFSR_Twinkle(&pMagenta, 30, 1);
        
        EffectsFSR_NutcrackerAlternate(&pMagenta, &pBlue,100,30);

        EffectsFSR_CatherineWheel(45);
        
        EffectsFSR_NutcrackerAlternate(&pRed, &pGreen,100,30);
        
        EffectsFSR_CatherineWheel(45);
        
        //EffectsFSR_Twinkle(&pWhite, 30,0);
         
        //EffectsFSR_RainbowFade(30);
        
        //EffectsFSR_NutcrackerSame(&pRed, &pGreen,100,30);
   
        //EffectsFSR_CatherineWheel(45);
    }*/
    
    
    while(EffectFSRRunning==1){
        switch (CurrentEffect)
        {
            case CatherineWheel:
                EffectsFSR_CatherineWheel(30);               
                EffectFSRRunning=0;
                break;
                
            case Fireflies:
                //EffectsFSR_Fireflies(&pFireflyGreen,30);
                EffectsFSR_Twinkle(&pFireflyGreen, 30, 0);
                EffectFSRRunning=0;
                break;     
                
            case Simple:
                EffectsFSR_RainbowFade(30);               
                EffectFSRRunning=0;
                break;
                
            default:
                EffectFSRRunning=0;
                break;
        }
        INTERRUPT_GlobalInterruptDisable();
    }
    return;
}



