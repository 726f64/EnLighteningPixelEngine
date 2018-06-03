 #include <xc.h>


void UART_Initialize(void)
 {

     
 }
 

void UART_ISR(void)
{

    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;

    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
}


 Flag_FrameStart
        
        
        
