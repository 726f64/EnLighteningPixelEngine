/* 
 * File:   System.h
 * Author: General
 *
 * Created on October 27, 2017, 9:38 AM
 */



#ifndef SYSTEM_H
#define	SYSTEM_H

#define xxxx=32000000

// States for FSR
enum States {
    Init,
    WaitingToIgnite,
    Ignite,
    RunUp,
    MaxHold,
    SlowDown,
    Stopped,
    Off    
} ;

//#define NumSpiral 50
#define NumArms 8
#define NumArmPixels 10
#define RunInPixels 8
#define RAMsize 88              // RunIn + (Number of Arms x Pixels Per Arm )



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

