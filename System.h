/* 
 * File:   System.h
 * Author: General
 *
 * Created on October 27, 2017, 9:38 AM
 */






#ifndef SYSTEM_H
#define	SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#define DisplayRAMStart __at(0x00A0);



//100 + 22 = eaves
//20 + 20 small potted trees
//= 162 Eaves set 2017
//78

//=178 Wooded area set 2017
//#define NumPixels   78
#define NumPixels   122
#define RGB 0                               //0=RGB, 1=GRB
#define RAMsize (NumPixels*3)              // Number of actual RGB Pixels *3

#define TimeOutLimit 2             //As timeout is 1ms ticks, this is in ms also
#define FireflyStart __at(0x00A0 + RAMsize);


bool Flag_FrameStart;
bool Flag_TimeOut;
uint16_t RAMCounter @0x0070;

uint16_t TimeOut_Counter;
bool EffectFSRRunning;
bool EffectFinished;
uint8_t EffectDuration;
    
// States for FSR
enum States {
    Init,
    WaitForFrameStart,
    ReadFrame,
    OutDisplayRAM,
    Off,
    TestFlash,
    TestTMR1,
    TestTMR2,
    TestSPI1,
    TestFlashRepeat,
    Automode,
    EffectsFSR
} ;

// States for EffectsFSR
enum Effects {
    None,
    Simple,
    CatherineWheel,
    NutCrackerSame,
    NutCrackerAlt,
    RainbowFade,
    Fade,
    CandleFlicker,
    Chase,
    Pulse,
    Spin,
    Twinkle,
    Wipe,
    Bars,
    Fire,
    Plasma,
    Life,
    Meteors,
    Curtain,
    Garlands,
    Snow,
    Fireflies
} ;

        
        
        

// States for Direction
enum Directions {
    Right,
    Left
} ;

// States for LoopAround
enum LoopOptions {
    NoLoop,
    Loop
} ;


struct Pixel {
    uint8_t Red;
    uint8_t Green;    
    uint8_t Blue;  
};

struct MovingPixel {
    uint8_t CurrentPosition;
    uint8_t Direction;
    uint8_t Red;
    uint8_t Green;    
    uint8_t Blue;  
};


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
const struct Pixel pFireflyGreen={128,255,0};


volatile  uint8_t DisplayRAM[NumPixels*3] DisplayRAMStart


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

