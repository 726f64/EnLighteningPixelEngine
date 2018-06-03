/* 
 * File:   Effects.h
 * Author: General
 *
 * Created on October 27, 2017, 9:42 AM
 */

#ifndef EFFECTS_H
#define	EFFECTS_H

#include <stdint.h>
#include "System.h"
#include "Effects.h"

struct Pixel {
    uint8_t Red;
    uint8_t Green;    
    uint8_t Blue;  
};

// Changing default values of enum
enum EffectsSpiral {
    NoChange = 0,
    Fade = 1,
    Brighten = 2,
};

void OutputDisplayRAM(void);
void RotateWheel(uint8_t , enum EffectsSpiral ,struct Pixel  );
//void RotateWheel(uint8_t  );
void Sparks(uint8_t , uint8_t );

void OutputDisplayRAM(void);





extern struct Pixel DisplayRAM[RAMsize];



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EFFECTS_H */


    
