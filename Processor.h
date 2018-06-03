/* 
 * File:   Processor.h
 * Author: General
 *
 * Created on 04 November 2017, 19:08
 */





#ifndef PROCESSOR_H
#define	PROCESSOR_H

void FSR_Init(void);
void FSR_WaitToIgnite(void);
void FSR_Ignite(void);
void FSR_RunUp(void);                            
void FSR_MaxHold(void);
void FSR_SlowDown(void);
void FSR_Stopped(void);
void FSR_Off(void);

void FSR_Radial_Init(void);



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PROCESSOR_H */

