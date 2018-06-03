/*
 * File:   CatherineWheel.c
 * Author: rodders
 *
 * Created on 27 October 2017, 08:46
 * 
 * New LED Firework design for Xmas 2017 - a catherine wheel
 */


#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "System.h"
#include "Processor.h"

void RunRadialDesign(void);  

enum States CurrentState;

void main(void) {

    SYSTEM_Initialize();
    CurrentState=Init;
    
    //setup ticks and local timers for events
    
   RunRadialDesign(); 
    
    return;
}


void RunRadialDesign(void){

    switch (CurrentState)
        {
            case Init:
                FSR__Init();
                CurrentState=WaitingToIgnite;
                break;

            default:
                CurrentState=RadialInit;
        }    
}

enum States {
    Initddd,
    WaitingToIgnite,
    Ignite,
    RunUp,
    MaxHold,
    SlowDown,
    Stopped,
    Off    
} ;

