#include <xc.h>
#include "Processor.h"
#include "System.h"
#include <stdlib.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "System.h"

extern volatile  uint8_t DisplayRAM[NumPixels*3] DisplayRAMStart

// Function will copy across the pixel into DisplayRAM - NB ASM uses absolute linear data RAM

void SetDisplayRAM(uint16_t PixelPosition, struct Pixel *PixelColour){
    DisplayRAM[(PixelPosition*3)]=PixelColour->Red;
    DisplayRAM[((PixelPosition*3)+1)]=PixelColour->Green;
    DisplayRAM[((PixelPosition*3)+2)]=PixelColour->Blue; 
    return;
}

//Set a specific Display RAM pixel at PixelPosition to the colours in ThisPixel
void SetPixel(uint16_t PixelPosition,struct Pixel *ThisPixel){
    DisplayRAM[(PixelPosition*3)]=ThisPixel->Red;
    DisplayRAM[((PixelPosition*3)+1)]=ThisPixel->Green;   
    DisplayRAM[((PixelPosition*3)+2)]=ThisPixel->Blue;     
    return;
}


struct Pixel GetPixel(uint16_t PixelPosition){
struct Pixel RetPixel;
    RetPixel.Red=DisplayRAM[(PixelPosition*3)];
    RetPixel.Green=DisplayRAM[((PixelPosition*3)+1)];    
    RetPixel.Blue=DisplayRAM[((PixelPosition*3)+2)]; 
    return RetPixel;
}

// Set every pixel in the display RAM to the same colour - typically used for testing or setting to off
void SetAllSameColour(struct Pixel *ThisColour){
    // Set all the Display RAM to zero values
    for (uint16_t ThisPixel=0; ThisPixel<NumPixels;ThisPixel++){
        SetDisplayRAM(ThisPixel,ThisColour);
    }
    return;
}

// Shift all Pixels along by N
//ShiftPixels(0,1,0,&InjectPixel);
void ShiftPixels(uint8_t Direction, uint8_t StepSizeN, uint8_t LoopAround, struct Pixel *FeedIn){
struct Pixel TempPixel;
struct Pixel TempArray[20];
//void SetPixel(uint16_t PixelPosition,struct Pixel *ThisPixel){
//Set a specific Display RAM pixel at PixelPosition to the colours in ThisPixel


    //Limits
    if (StepSizeN>10)StepSizeN=10;
    if (StepSizeN<1)StepSizeN=1;
    
    if (Direction==0){
        
        if (LoopAround==1){
            //Save end of string into TempArray
            for (uint8_t i=0;i<StepSizeN;i++){
                TempArray[i]=GetPixel(NumPixels-1-StepSizeN+i);   
            }
        }
        
        //Shuffle the rest along
        for (uint8_t i=(NumPixels-1-StepSizeN);i>0; i--){
            TempPixel = GetPixel(i);
            //SetPixel((i+StepSizeN),&TempPixel);
            SetPixel((i+StepSizeN),&TempPixel);            
        }
        TempPixel = GetPixel(0);
        //SetPixel((i+StepSizeN),&TempPixel);
        SetPixel(1,&TempPixel);        
        
        //Add back in the TempArray
        if (LoopAround==1){

            for (uint8_t i=0;i<StepSizeN;i++){
                SetPixel(i,&TempArray[i]);   
            }   
        }
        else {
            //Add in the FeedIn pixel
            SetPixel(0,FeedIn);
        }
    }

    else{
        if (LoopAround==1){
            //Save start of Array
            for (uint8_t i=0;i<StepSizeN;i++){
                TempPixel=GetPixel(i);   
            } 
        }
        for (uint8_t i=StepSizeN;i>0; i--){         //????????? WRONG
            TempPixel = GetPixel(i);
            SetPixel((i+StepSizeN),&TempPixel);
        }
        if (LoopAround==1){
            //Set end of string from TempArray
            for (uint8_t i=0;i<StepSizeN;i++){
                SetPixel((NumPixels-1-StepSizeN+i),&TempArray[i]);   
            } 
        }
    }
    return;
}


void Write_Pixels(void){
    INTERRUPT_GlobalInterruptDisable();
    PIE4bits.TMR1IE = 0;
    RAMCounter=RAMsize;         //No actual bytes (=pixels x 3) to output
    LATAbits.LATA4=1;
    asm("clrf BSR");
    asm("movlw 0x20");
    asm("movwf FSR0H");
    asm("movlw 0x50");
    asm("movwf FSR0L");    
    
asm("loop:");
    asm("movf INDF0,w");                //gets the contents of address pointed to into W
    //asm("moviw FSR0++");              //actually takes longer ?? even though only 1x clock cycle in spec
    asm("bsf BSR,0");                   // diff to 16f1509 ! this in BANK 3
    asm("bsf BSR,1");
    asm("movwf SSP1BUF");

    asm("movlw 0x0e"); 
    asm("movwf BSR");
 
asm("notclear:");
    asm("btfss PIR3,0");                // was PIR1,3 for PIC16F1509
    asm("goto notclear");   
    asm("bcf PIR3,0");
    
    asm("clrf BSR");
    asm("ADDFSR FSR0,1");               //should auto increment the FSR0H

    asm("movlw 0x01");
    asm("subwf 0x70,f");                        //Subtracting 1 will set Carry
    asm("btfsc STATUS,0");
    asm("goto loop");

    asm("movlw 0x01");
    asm("subwf 0x71,f");                        //Subtracting 1 will set Carry
    asm("btfsc STATUS,0");
    asm("goto loop");    
      
    PIE4bits.TMR1IE = 1;
    LATAbits.LATA4=0; 
    INTERRUPT_GlobalInterruptEnable();
    return;
}

// An initial double red flash to confirm start up
void FSR_Init(void){ 
        INTERRUPT_GlobalInterruptDisable();
        SetAllSameColour(&pBlack);
        Write_Pixels();
        __delay_ms(300);        
        SetAllSameColour(&pRed);
        Write_Pixels();
        __delay_ms(300);    
        SetAllSameColour(&pBlack);
        Write_Pixels();
        __delay_ms(300);
        SetAllSameColour(&pRed);
        Write_Pixels();
        __delay_ms(300);    
        SetAllSameColour(&pBlack);
        Write_Pixels();
        __delay_ms(300); 
        INTERRUPT_GlobalInterruptEnable();
    return;  
}

// Waits in this state until the Start-of-Frame indicator goes high (sent by RPi))
void FSR_WaitForFrameStart(void){

    uint8_t Byte2Dump;
    
    while (PORTCbits.RC2==1);           //wait for it to go low first
    
    if (PORTCbits.RC2==0){              //...and then wait for the high
        //just wait for it to go high
        while(PORTCbits.RC2==0);
    }
    
    
    Byte2Dump=SSP2BUF;          //clear out any old byte
    return;    
}
          


uint8_t FSR_ReadFrameBytes(void){
    
    uint8_t ByteVal;
    uint16_t ByteCount=0;
    bool finished=false;

    
    while((PORTCbits.RC2==1)&&(!finished)){
        //read bytes
        while(!SSP2STATbits.BF);
        ByteVal=SSP2BUF;
        DisplayRAM[ByteCount]=ByteVal;
        ByteCount++;
        if (ByteCount==RAMsize) finished=true;        
    }
    while(PORTCbits.RC2==1);            //wait for SS2 to become inactive
    
    return 0;   
}

// Output whatever has been accrued in the DisplayRAM buffer to the WS2812 string
void FSR_OutputDisplayRAM(void){
    Write_Pixels();
    return;
}

// A test pattern to flash when required - not same as startup flash pattern
void FSR_Test_Flash(void){

        SetAllSameColour(&pMagenta);
        Write_Pixels();
        __delay_ms(300);    
        SetAllSameColour(&pBlack);
        Write_Pixels();
        __delay_ms(500);
        SetAllSameColour(&pCyan);
        Write_Pixels();
        __delay_ms(300);    
        SetAllSameColour(&pBlack);
        Write_Pixels();
        __delay_ms(500);
        __delay_ms(500);
        return;
}

// Tests out how the TMR1 Works by flashing the lights
void FSR_Test_TMR1(void){

    SetTimeoutCounter(1000);

    while(1){
        if (Flag_TimeOut){
            FSR_Test_Flash();
            SetTimeoutCounter(2000);
        }
    }
    
    return;
}

// Tests out how the TMR2 Works by having asymetric output on LATB4
void FSR_Test_TMR2(void){
    __delay_ms(5); 
    while(1){
        LATBbits.LATB4=1;
        __delay_ms(1);
        LATBbits.LATB4=0; 
        __delay_ms(1);
        if (PIR4bits.TMR2IF==1){
            __delay_ms(3);
            PIR4bits.TMR2IF=0;
        }
        
    }
    return;
}    

void FSR_Test_SPI1(void){
    __delay_ms(5);
    while(1){
        SSP1BUF=0x55;
        while(!SSP1IF);        
        __delay_ms(20);
        SSP1BUF=0xF1;
        while(!SSP1IF);
        __delay_ms(20);        
        
    }
    
    return;
}

//Ensure that the flag is always reset when the TMR1 ticker is setup
void SetTimeoutCounter(uint16_t Value){
    
    Flag_TimeOut=false;
    TimeOut_Counter=Value;
    return;
}

void ResetDuration(uint8_t Duration){
    EffectFinished=0;
    EffectDuration=Duration;
    if (Duration==0) EffectFinished=1;          //Effectively won't run if user sets to 0 seconds.
    INTERRUPT_GlobalInterruptEnable();
    return;
}

 void delay_ms(uint16_t milliseconds)
 {
   while(milliseconds > 0)
   {
       __delay_ms(1);
      milliseconds--;
    }
   return;
 }