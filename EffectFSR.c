#include <xc.h>
#include "Processor.h"
#include "System.h"
#include <stdlib.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "System.h"
#include <stdbool.h>
#include <time.h>
#include "mcc_generated_files/mcc.h"

#include "EffectFSR.h"

extern volatile  uint8_t DisplayRAM[NumPixels*3] DisplayRAMStart;
extern struct Pixel PatternA[];
extern struct Pixel PatternB[];
extern struct Pixel PatternC[];
extern struct Pixel PatternD[];
extern struct Pixel PatternE[];
extern struct Pixel PatternF[];
extern struct Pixel PatternG[];
extern struct Pixel PatternH[];

//Fade out a single colour in brightness over the defined period by Duration
void EffectsFSR_FadeSingleColour(struct Pixel *Colour){
    struct Pixel SelectedColour;
    SelectedColour.Red=Colour->Red;
    SelectedColour.Green=Colour->Green;
    SelectedColour.Blue=Colour->Blue;
    
    for (uint8_t i=0; i<255;i++){
        SetAllSameColour(&SelectedColour);
        Write_Pixels();
        __delay_ms(10);
        if (SelectedColour.Red>0) SelectedColour.Red=SelectedColour.Red-1; 
        if (SelectedColour.Green>0) SelectedColour.Green=SelectedColour.Green-1;
        if (SelectedColour.Blue>0) SelectedColour.Blue=SelectedColour.Blue-1;
    }  
    return;
}

void EffectsFSR_TripleFade(uint8_t Duration){
    ResetDuration(Duration);
    while (!EffectFinished){
        EffectsFSR_FadeSingleColour(&pMagenta);
        EffectsFSR_FadeSingleColour(&pCyan);
        EffectsFSR_FadeSingleColour(&pYellow);
    }
    return;
}

//Nutcracker with all pixels the same
//Delay in 1/100th second (10ms) eg 100=1sec
void EffectsFSR_NutcrackerSame(struct Pixel *ColourA,struct Pixel *ColourB,uint8_t Delay,uint8_t Duration){

    struct Pixel SelectedColourA;
    SelectedColourA.Red=ColourA->Red;
    SelectedColourA.Green=ColourA->Green;
    SelectedColourA.Blue=ColourA->Blue;
    
    struct Pixel SelectedColourB;
    SelectedColourB.Red=ColourB->Red;
    SelectedColourB.Green=ColourB->Green;
    SelectedColourB.Blue=ColourB->Blue;
    
    ResetDuration(Duration);
    while(!EffectFinished){
            SetAllSameColour(&SelectedColourA);
            Write_Pixels();
            for(uint8_t i=0; i<Delay; i++){
                __delay_ms(10);
            }
            SetAllSameColour(&SelectedColourB);
            Write_Pixels();
            for(uint8_t i=0; i<Delay; i++){
                __delay_ms(10);
            }
    }
    SetAllSameColour(&pBlack);
    Write_Pixels();    
    return; 
}

//Complementing Nutcracker - pixels are alternated
//Delay in 1/100th second (10ms) eg 100=1sec
//Duration in seconds
void EffectsFSR_NutcrackerAlternate(struct Pixel *ColourA,struct Pixel *ColourB,uint8_t Delay,uint8_t Duration){
    ResetDuration(Duration);
    
    struct Pixel SelectedColourA;
    SelectedColourA.Red=ColourA->Red;
    SelectedColourA.Green=ColourA->Green;
    SelectedColourA.Blue=ColourA->Blue;
    
    struct Pixel SelectedColourB;
    SelectedColourB.Red=ColourB->Red;
    SelectedColourB.Green=ColourB->Green;
    SelectedColourB.Blue=ColourB->Blue;

    while(!EffectFinished){
                
                for (uint16_t ThisPixel=0; ThisPixel<NumPixels;ThisPixel=ThisPixel+2){
                    SetDisplayRAM(ThisPixel,ColourA);
                    if(ThisPixel<NumPixels) SetDisplayRAM(ThisPixel+1,ColourB); //in case odd number and steps one over end !
                }
                Write_Pixels();
                for(uint8_t i=0; i<Delay; i++){
                    __delay_ms(10);
                }
                
                for (uint16_t ThisPixel=0; ThisPixel<NumPixels;ThisPixel=ThisPixel+2){
                    SetDisplayRAM(ThisPixel,ColourB);
                    if(ThisPixel<NumPixels) SetDisplayRAM(ThisPixel+1,ColourA); //in case odd number and steps one over end !
                }
                Write_Pixels();
                for(uint8_t i=0; i<Delay; i++){
                    __delay_ms(10);
                }                

    } 
    SetAllSameColour(&pBlack);
    Write_Pixels();
    return; 
}


void EffectsFSR_ColourWashTwo(struct Pixel *ColourA,struct Pixel *ColourB,uint8_t Duration){
    double RedDelta;
    double GreenDelta;
    double BlueDelta;
    double MaxDelta=0;
    double Delay;
    
    double RedInc;
    double GreenInc;
    double BlueInc;
    
    if ((ColourA->Red)>(ColourB->Red)) RedDelta=(ColourA->Red)-(ColourB->Red);
    else RedDelta=(ColourB->Red)-(ColourA->Red);
    RedInc=RedDelta/Duration;
    
    if ((ColourA->Green)>(ColourB->Green)) RedDelta=(ColourA->Green)-(ColourB->Green);
    else GreenDelta=(ColourB->Green)-(ColourA->Green);
    GreenInc=GreenDelta/Duration;
    
    if ((ColourA->Blue)>(ColourB->Blue)) RedDelta=(ColourA->Blue)-(ColourB->Blue);
    else BlueDelta=(ColourB->Blue)-(ColourA->Blue);
    BlueInc=BlueDelta/Duration;

    if (RedDelta>=MaxDelta) MaxDelta=RedDelta;
    if (GreenDelta>=MaxDelta) MaxDelta=GreenDelta;
    if (BlueDelta>=MaxDelta) MaxDelta=BlueDelta;
    
    Delay=Duration/MaxDelta;
    
    ResetDuration(Duration);
    while(!!EffectFinished){
        
    }
}

void EffectsFSR_ColourWashThree(struct Pixel ColourA,struct Pixel ColourB,uint8_t Delay,uint8_t Duration){
    ResetDuration(Duration);
    while(!EffectFinished){
        
    }
}

void EffectsFSR_Bars(struct Pixel ColourA,struct Pixel ColourB,uint8_t Delay,uint8_t Duration){
    ResetDuration(Duration);
    while(!EffectFinished){
        
    }
}
// uint8_t *seconds
void EffectsFSR_RainbowFade(uint8_t Duration){
    ResetDuration(Duration);
    while(!EffectFinished){
        EffectsFSR_FadeSingleColour(&pMagenta);        
        EffectsFSR_FadeSingleColour(&pYellow);
        EffectsFSR_FadeSingleColour(&pCyan);
    }
    SetAllSameColour(&pBlack);
    Write_Pixels();
    return;
}


 
void EffectsFSR_FireworkEffect(uint8_t Duration){
    ResetDuration(Duration);    
    while(!EffectFinished){
    
    }
}


void EffectsFSR_CatherineWheel(uint8_t Duration){

//struct Pixel ColourA=pMagenta;
//struct Pixel ColourB=pBlue;
struct Pixel InjectPixel=pMagenta;
//int8_t DirectionRed;
//int8_t DirectionGreen;
//int8_t DirectionBlue;
bool Finished=0;
#define SparkleCountMax 50
//uint8_t SparkleCount=SparkleCountMax;
uint8_t PatternCount = 0;
//#define PatternMax = 19+78
uint8_t PatID;
uint16_t PixelDelay=100;

ResetDuration(Duration);

// __delay_ms is a MACRO and can only take const values eg at compile time NOT variables !
// Using delay_ms function instead (also can go to 65536*ms)

    while(!EffectFinished){
        
        PatID=rand() % 10;
        while(!Finished){
            
            if (PatternCount<19) 
                switch(PatID){
                    /*case 1:
                        InjectPixel=PatternA[PatternCount];
                        break;
                    case 2:
                        InjectPixel=PatternB[PatternCount];
                        break;
                    case 3:
                        InjectPixel=PatternC[PatternCount];
                        break;                        
                    case 4:
                        InjectPixel=PatternD[PatternCount];
                        break; 
                    case 5:
                        InjectPixel=PatternE[PatternCount];
                        break;                         
                    case 6:
                        InjectPixel=PatternF[PatternCount];
                        break;   
                    case 7:
                        InjectPixel=PatternG[PatternCount];
                        break;                        
                    case 8:
                        InjectPixel=PatternH[PatternCount];
                        break;                         
                    default:
                        InjectPixel=PatternA[PatternCount];
                        break;*/
                }               
            else InjectPixel=pBlack;
            ShiftPixels(0,1,0,&InjectPixel);
            PatternCount++;
            if (PatternCount==60) {
                PatternCount=0;
                Finished=1;
            }
            //SetAllSameColour(&pGreen);
            
            
            //Output RAM
            Write_Pixels();
/*
            //Feed in next pixel e.g. adjust current value to fade between those two provided
            if (InjectPixel.Red!=ColourB.Red){
                if (DirectionRed==1) InjectPixel.Red++;
                else InjectPixel.Red--;
            }
            if (InjectPixel.Green!=ColourB.Green){
                if (DirectionGreen==1) InjectPixel.Green++;
                else InjectPixel.Green--;
            }
            if (InjectPixel.Blue!=ColourB.Blue){
                if (DirectionBlue==1) InjectPixel.Blue++;
                else InjectPixel.Blue--;
            }
            
            //Also fade in intensity
                    

            if ((InjectPixel.Red==ColourB.Red)&&(InjectPixel.Red==ColourB.Red)&&(InjectPixel.Red==ColourB.Red)) Finished=true;
            */

            //Wait
            delay_ms(PixelDelay);
        }
        
        PixelDelay=PixelDelay-5;
        if (PixelDelay<20)PixelDelay=100;
        
        //InjectPixel=ColourB;
        //ColourB=ColourA;
        //ColourA=InjectPixel;
        Finished=0;

    }
    return;
}


void EffectsFSR_Twinkle(struct Pixel *ColourA, uint8_t Duration, bool Rainbow){

uint16_t PatID;
uint8_t Decrement;
struct Pixel TestPixel;


ResetDuration(Duration);

// __delay_ms is a MACRO and can only take const values eg at compile time NOT variables !
// Using delay_ms function instead (also can go to 65536*ms)

    SetAllSameColour(&pBlack);
    Write_Pixels();
        
    while(!EffectFinished){
        //Light up pixels randomly - but only if fully out

        if ((GetPixel(PatID).Red==0)&&(GetPixel(PatID).Green==0)&&(GetPixel(PatID).Blue==0)) {
            //RGB are zero so light up again
            if (!Rainbow){
                TestPixel.Red=ColourA->Red;
                TestPixel.Green=ColourA->Green;
                TestPixel.Blue=ColourA->Blue;
            }
            else {
                PatID=0;
                PatID=rand() % 4;
                switch(PatID){
                    case 1:
                        TestPixel=pMagenta;
                        break;
                    case 2:
                        TestPixel=pCyan;
                        break;                    
                    case 3:
                        TestPixel=pYellow;
                        break;
                    case 4:
                        TestPixel=pWhite;
                        break; 
                    default:
                        TestPixel=pBlack;
                        break;
                }    
            }
            PatID=rand() % NumPixels;
            SetPixel(PatID,&TestPixel);  
        }
        Write_Pixels();

        
        //Fade out all pixels randomly
        for (uint16_t i=0; i<NumPixels;i++){
            PatID=0;
            PatID=rand() % 4;
            switch(PatID){
                case 1:
                    Decrement=0;
                    break;
                case 2:
                    Decrement=5;
                    break;                    
                case 3:
                    Decrement=20;
                    break;
                case 4:
                    Decrement=50;
                    break; 
                default:
                    Decrement=10;       //was 20 03.06.2018
                    break;
            }

            TestPixel.Red=GetPixel(i).Red;
            TestPixel.Green=GetPixel(i).Green;
            TestPixel.Blue=GetPixel(i).Blue;

            if ((TestPixel.Red)>Decrement){
                TestPixel.Red=((TestPixel.Red)-Decrement);
            }
            else TestPixel.Red=0;

            if ((TestPixel.Green)>Decrement){
                TestPixel.Green=((TestPixel.Green)-Decrement);
            }
            else TestPixel.Green=0;

            if ((TestPixel.Blue)>Decrement){
                TestPixel.Blue=((TestPixel.Blue)-Decrement);
            }
            else TestPixel.Blue=0;
            SetPixel(i,&TestPixel);    
        }
        
        //Output RAM
        Write_Pixels();

        //Wait
        delay_ms(1);    //was 10ms 03.06.2018
        }
        

        return;
}


void EffectsFSR_Fireflies(struct Pixel *ColourA, uint8_t Duration){

#define NumFireflys 5
#define FireflyOn 10                //num of 10ms   
#define FireflyOff 30              //Num 10ms
#define RegenPeriod 300;
    
uint16_t PatID;
uint8_t Decrement;
struct Pixel TestPixel;
uint8_t *Firefly_Delays;

struct tFirefly *myFireflies[NumFireflys];

    myFireflies[5] = malloc(sizeof(struct tFirefly));
    struct tFirefly *(*p)[] = &myFireflies;  // of pointers to structs 
    
    ResetDuration(Duration);

    SetAllSameColour(&pBlack);
    Write_Pixels();
    
    //Make an array of number of pixels so we can keep an eye on what each Firefly is doing
    struct tFirefly tempFirefly;
    tempFirefly.Flashes_Remaining=0;
     
    //Initialise
    /*
    for (uint8_t i=0; i<NumPixels; i++){
        myFireflies[i].Flashes_Remaining=0;
        myFireflies[i].MaxBrightness=0;
        myFireflies[i].Regenerate_Period=0;
        myFireflies[i].Time_Flash_Off=0;
        myFireflies[i].Time_Flash_On=0;
        myFireflies[i].FireflyLedID=0;
        myFireflies[i].Status=0;                //On or Off
        myFireflies[i].Regen=1;                 // 1=regenerating
    }*/
    
    while(!EffectFinished){
    
        //set a random counter for the next random firefly to start
        Firefly_Delays=20;
        ResetNextFirefly(&Firefly_Delays);
        
        //Wait for a 10ms delay tick...
        
        
        //service all existing fireflies - eg any with flashes still remaining
        for (uint8_t Firefly; Firefly < (NumFireflys-1); Firefly++){
            
            if ((*p)[Firefly]->Flashes_Remaining!=0){
                
                if ((*p)[Firefly]->Status==0){

                    if ((*p)[Firefly]->Time_Flash_Off==0){
                        //Change to FireflyON;
                        (*p)[Firefly]->Time_Flash_On=FireflyOn;
                        SetDisplayRAM((*p)[Firefly]->FireflyLedID,&pFireflyGreen);
                        (*p)[Firefly]->Status=1;
                    }
                    (*p)[Firefly]->Time_Flash_Off--;
                }
                else {

                    if ((*p)[Firefly]->Time_Flash_On==0){
                        //Change to FireflyOFF;
                        (*p)[Firefly]->Time_Flash_Off=FireflyOff;
                        SetDisplayRAM((*p)[Firefly]->FireflyLedID,&pBlack);
                        (*p)[Firefly]->Status=0;

                        (*p)[Firefly]->Flashes_Remaining--;
                        if ((*p)[Firefly]->Flashes_Remaining==0){
                            (*p)[Firefly]->Regenerate_Period=RegenPeriod;
                        }

                    }
                    (*p)[Firefly]->Time_Flash_On--;                

                }//service this Firefly's next flash
            }//service this Firefly
        }//service all fireflies
        
        
        
        //check if timeout for new firefly to flash
                
        
        //if so select one, set random values and continue
        
        
            

    }
    
    //Now just keep going until all are faded and finished 'chirping away'

}




/*
//I
struct Pixel PatternA[]={
    {0xFF, 0xFF, 0xFF},
    {0x00, 0x0, 0x00}, 
    {0xFF, 0xFF, 0xFF}, 
    {0xCC, 0xCC, 0xCC}, 
    {0x0, 0x0, 0x0},
    {0xAA, 0x0, 0x55},
    {0x99, 0x0, 0x66},           
    {0x88, 0x0, 0x77},
    {0xFF, 0xFF, 0xFF},
    {0x66, 0x66, 0x66},
    {0x00, 0x00, 0x00},
    {0x44, 0x0, 0xBB},
    {0x33, 0x0, 0xCC},
    {0x22, 0x0, 0xDD}, 
    {0x11, 0x0, 0xEE}, 
    {0x0, 0x0, 0xFF},
    {0xE0, 0xE0, 0xE0},
    {0x0, 0x0, 0xC1},
    {0x0, 0x0, 0xA2},
    {0x0, 0x0, 0x83}
};
//J
struct Pixel PatternB[]={

    {0xFF, 0x0, 0x0},
    {0xCC, 0x33, 0x0},
    {0xFF, 0xFF, 0xFF}, 
    {0x66, 0x99, 0x0},
    {0x33, 0xCC, 0x0}, 
    {0x0, 0xFF, 0x0}, 
    {0xFF, 0xFF, 0xFF},
    {0x66, 0x99, 0x0}, 
    {0x99, 0x66, 0x0}, 
    {0xCC, 0x33, 0x0}, 
    {0xFF, 0xFF, 0xFF},
    {0xCC, 0x33, 0x0},
    {0x99, 0x66, 0x0},
    {0x66, 0x99, 0x0}, 
    {0x33, 0xCC, 0x0}, 
    {0xFF, 0xFF, 0xFF},
    {0x33, 0xCC, 0x0},
    {0x66, 0x99, 0x0},
    {0x99, 0x66, 0x0},
    {0xCC, 0x33, 0x0}
};

//E
struct Pixel PatternC[]={
	{0x0, 0xFF, 0x0}, 
    {0x0, 0xF6, 0x0},
    {0x0, 0x00, 0x0},
    {0xff, 0xff, 0xff},
    {0x0, 0x00, 0x0}, 
    {0x0, 0xD2, 0x0}, 
    {0x0, 0xC9, 0x0},
	{0xA0, 0xA0, 0xA0}, 
    {0x0, 0x00, 0x0},
    {0x0, 0xAE, 0x0}, 
    {0x0, 0xA5, 0x0}, 
    {0x0, 0x9C, 0x0},
	{0x0, 0x93, 0x0},
    {0x0, 0x8A, 0x0},
    {0x0, 0x81, 0x0},
    {0x0, 0x78, 0x0}, 
    {0x0, 0x6F, 0x0},
	{0x0, 0x66, 0x0},
    {0x0, 0x5D, 0x0},
    {0x0, 0x54, 0x0}
};

//D
struct Pixel PatternD[]={
	//PATTERN_D (Red - Green - Yellow)
	{0x0, 0xFF, 0x0},
    {0x11, 0xEE, 0x0},
    {0x22, 0xDD, 0x0},
    {0x33, 0xCC, 0x0},
    {0x44, 0xBB, 0x0},
    {0x55, 0xAA, 0x0},
    {0x66, 0x99, 0x0},
	{0x77, 0x88, 0x0},
    {0x88, 0x77, 0x0},
    {0x99, 0x66, 0x0},
    {0xAA, 0x55, 0x0},
    {0xBB, 0x44, 0x0},
	{0xCC, 0x33, 0x0},
    {0xDD, 0x22, 0x0},
    {0xEE, 0x11, 0x0}, 
	{0xFF, 0x0, 0x0}, 
    {0xE7, 0x11, 0x0},
    {0xCF, 0x22, 0x0},
    {0xB7, 0x33, 0x0}, 
    {0x9F, 0x44, 0x0},
    {0x87, 0x55, 0x0}, 
    {0x6F, 0x66, 0x0},
	{0x57, 0x77, 0x0}, 
    {0x3F, 0x88, 0x0}, 
    {0x27, 0x99, 0x0}
};


//D
struct Pixel PatternE[]={
	//PATTERN_D (Red - Green - Yellow)
	{0xFF, 0x00, 0x0},
    {0xF0, 0x00, 0x0},
    {0xE8, 0x00, 0x0},
    {0xE0, 0x00, 0x0},
    {0xD8, 0x00, 0x0},
    {0xD0, 0x00, 0x0},
    {0xFF, 0xFF, 0xFF},
	{0x80, 0x80, 0x80},
    {0xC8, 0x00, 0x0},
    {0xC0, 0x00, 0x0},
    {0xB8, 0x00, 0x0},
    {0xB0, 0x00, 0x0},
	{0xA8, 0x00, 0x0},
    {0xA0, 0x00, 0x0},
    {0xFF, 0xFF, 0xFF}, 
	{0x98, 0x0, 0x0}, 
    {0x90, 0x00, 0x0},
    {0x80, 0x80, 0x80},
    {0x88, 0x00, 0x0}, 
    {0x80, 0x00, 0x0},
    {0x70, 0x00, 0x0}, 
    {0x50, 0x00, 0x0},
	{0x40, 0x00, 0x0}, 
    {0x20, 0x00, 0x0}, 
    {0x10, 0x00, 0x0}
};

//D
struct Pixel PatternF[]={
	//PATTERN_D (Red - Green - Blue)
	{0xFF, 0xFF, 0x0},
    {0xE0, 0xE0, 0x0},
    {0xB0, 0xB0, 0x0},
    {0x70, 0x70, 0x0},
    
    {0xFF, 0x00, 0x0},
    {0xE0, 0x00, 0xE0},
	{0xB0, 0x00, 0xB0},
    {0x70, 0x00, 0x70},
    
    {0x00, 0xFF, 0xFF},
    {0x00, 0xE0, 0xE0},
    {0x00, 0xB0, 0xB0},
	{0x00, 0x70, 0x70},    
    {0x00, 0x40, 0x40},
    
    {0xFF, 0xFF, 0xFF}, 
	{0xE0, 0xE0, 0xE0}, 
    {0xB0, 0xB0, 0xB0},
    {0x90, 0x90, 0x90},
    {0x50, 0x60, 0x50}, 
    
    {0x20, 0x20, 0x20},
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
	{0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
    {0x00, 0x00, 0x0}
};

struct Pixel PatternG[]={
	{0xFF, 0xFF, 0x0},
    {0xE0, 0xE0, 0x0},
    {0xB0, 0xB0, 0x0},
    {0x70, 0x70, 0x0},
    
    {0xFF, 0x00, 0x0},
    {0xE0, 0x00, 0xE0},
	{0xB0, 0x00, 0xB0},
    {0x70, 0x00, 0x70},
    
    {0x00, 0xFF, 0xFF},
    {0x00, 0xE0, 0xE0},
    {0x00, 0xB0, 0xB0},
	{0x00, 0x70, 0x70},    
    {0x00, 0x40, 0x40},
    
    {0xFF, 0xFF, 0xFF}, 
	{0xE0, 0xE0, 0xE0}, 
    {0xB0, 0xB0, 0xB0},
    {0x90, 0x90, 0x90},
    {0x50, 0x60, 0x50}, 
    
    {0x20, 0x20, 0x20},
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
	{0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
    {0x00, 0x00, 0x0}
};

struct Pixel PatternH[]={

    {0x00, 0x00, 0x0},
    {0x00, 0x70, 0x70},
    {0x20, 0x20, 0x20},
    {0xE0, 0xE0, 0x0},
    {0x90, 0x90, 0x90},
    {0xFF, 0xFF, 0xFF},
    {0xB0, 0xB0, 0x0},
    {0xB0, 0x00, 0xB0},
    {0x70, 0x70, 0x0},
    {0x00, 0x00, 0x0},
    {0xFF, 0x00, 0x0},
    {0xE0, 0x00, 0xE0},
    {0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x0},

    {0x70, 0x00, 0x70},

    {0x00, 0xFF, 0xFF},
    {0x00, 0xE0, 0xE0}, 
    {0xFF, 0xFF, 0x0},
    {0x00, 0x00, 0x0},
    {0x00, 0xB0, 0xB0},

    {0x00, 0x00, 0x0},
    {0x00, 0x40, 0x40},


    {0x00, 0x00, 0x0},
    {0xE0, 0xE0, 0xE0}, 
    {0xB0, 0xB0, 0xB0},

    {0x50, 0x60, 0x50}, 


    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0}, 
    {0x00, 0x00, 0x0},
    {0x00, 0x00, 0x0}
};*/
