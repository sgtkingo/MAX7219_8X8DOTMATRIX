#include "PICF18LF46K22_ConfigSFR.h"
#include "MAX7219_FunctionLib.h"
//declared init fce
void InitDevice(){
    OSCCON=0b01111100; //osc setting, 16 MHz, internal by FOSCH
    OSCTUNE=0x00; //PLLx4 OFF
    ANSELD=0x00;
    TRISD=0x00;
    
    //Config CS pin
    ANSELAbits.ANSA3=0;
    TRISAbits.RA3=0;
    PORTAbits.RA3=1;
    
    //For MCP41100
    ANSELAbits.ANSA5=0;
    TRISAbits.RA5=0;
    PORTAbits.RA5=1;
}
//declared clear fce
void ClearDevice(){
    PORTD=0;
    LATD=0;
}
//declared test fce
void TestDevice(){
    delay_ms(1000);
    LATD=0xFF;
    delay_ms(1000);
    LATD=0x00;
}

void main(void) {
    InitDevice();
    ClearDevice();
    TestDevice();
 
    Init_MAX7219(&PORTA,CS_PIN);
    ClearALL_MAX7219();
    delay_ms(1000);
    
    for(unsigned char disp=1;disp<=MAX7219_MAX_DISPLAYs;disp++){
        if(disp%2)Shine_LEDs_MAX7219(disp,0xAA);
        else      Shine_LEDs_MAX7219(disp,0x55);
        delay_ms(100);
    }
    //Shutdown_MAX7219(CMD_SHUTDOWN_MODE);
    
    LATD=0xFF;
    while(1){
        NOP();
    }
    return;
}
