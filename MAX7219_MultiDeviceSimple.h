/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * Author: Jiri Konecny 
 * Comments: Liblary for MAX7219 MULTI DEVICE
 * Revision history: 1.0 / 070320
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX_7219_MDS_PIC_H
#define	MAX_7219_MDS_PIC_H

#include "SPI_PICLIB.h"
#include "MAX7219_Charset.h"
#include "PIC16F18323_DEMUXER.h"


#define REG_DECODE_MAX7219 0x09
#define REG_INTENSITY_MAX7219 0x0A
#define REG_SCANLIMIT_MAX7219 0x0B
#define REG_SHUTDOWN_MAX7219 0x0C
#define REG_TEST_MAX7219 0x0F

#define CMD_TEST 0x01
#define CMD_NORMAL_MODE 0x01
#define CMD_SHUTDOWN_MODE 0x00

#define CMD_NO_DECODE_MODE 0x00
#define CMD_ALL_DECODE_MODE 0xFF

#define CMD_INTENSITY_100P 0x0F
#define CMD_INTENSITY_50P 0x08
#define CMD_INTENSITY_25P 0x04
#define CMD_INTENSITY_1P 0x00

#define CMD_SCAN_ALL 0x07
#define CMD_NO_OP 0x00

#define N_MATRIX 4
#define NON_MATRIX 0xFF

unsigned char ACTUAL_MATRIX=0;

void Inits_MAX7219_MDS();
void selectMatrix(unsigned char matrix);

void Write_Data_MAX7219_MD(unsigned char cmd,unsigned char data);
void Send_Data_MAX7219_MD(unsigned char cmd,unsigned char data, unsigned char device);
void Shine_LEDs_MAX7219_MD(unsigned char display, unsigned char data, unsigned char device);

void Test_MAX7219_MD(unsigned char device);
void Test_ALL_MAX7219_MD();
void Clear_ALL_MD();
void ClearDisplay_MAX7219_MD(unsigned char display, unsigned char device);
void Clear_Matrix_MAX7219_MD(unsigned char device);

void Shutdown_MAX7219_MD(unsigned char mode, unsigned char device);

void Print_Matrix_MAX7219_MD(unsigned char *data, unsigned char device);

void Inits_MAX7219_MDS(){
    ACTUAL_MATRIX=0;
    Init_DEMUXER();

    SPI_INIT();
    
    for(unsigned char i=0;i<N_MATRIX;i++){
        Test_MAX7219_MD(i);
        Send_Data_MAX7219_MD(REG_INTENSITY_MAX7219,CMD_INTENSITY_50P,i);
        Send_Data_MAX7219_MD(REG_SCANLIMIT_MAX7219,CMD_SCAN_ALL,i);
        Send_Data_MAX7219_MD(REG_DECODE_MAX7219,CMD_NO_DECODE_MODE,i);
        Send_Data_MAX7219_MD(REG_SHUTDOWN_MAX7219,CMD_NORMAL_MODE,i);
        SPI_PAUSE(5000);
    }
}

void selectMatrix(unsigned char matrix){
    if( matrix < 0 || matrix >= N_MATRIX )return;
    ACTUAL_MATRIX=matrix;
}

void Send_Data_MAX7219_MD(unsigned char cmd,unsigned char data, unsigned char device){
    selectMatrix(device);
    Write_Data_MAX7219_MD(cmd,data);
}

void Write_Data_MAX7219_MD(unsigned char cmd,unsigned char data){
    Set_DEMUX(ACTUAL_MATRIX);
    SPI_WRITE(cmd);
    SPI_WRITE(data);
    Set_DEMUX(NON_MATRIX);
    
    SPI_PAUSE(500);    
}

//Set DATA to display 1-7, 0 == NO_OP
void Shine_LEDs_MAX7219_MD(unsigned char display, unsigned char data, unsigned char device){
    if( display > MAX7219_MAX_DISPLAYs ) display=0x08; 
    Send_Data_MAX7219_MD(display,data,device);  
}

void Print_Matrix_MAX7219_MD(unsigned char *data, unsigned char device){
    for(unsigned char i=0;i<MAX7219_MAX_DISPLAYs;i++){
        Shine_LEDs_MAX7219_MD(i+1, data[i],device);
    }
}

void Test_ALL_MAX7219_MD(){
    for(unsigned char i=0;i<N_MATRIX;i++){
        Test_MAX7219_MD(i);
    }    
}

void Test_MAX7219_MD(unsigned char device){
    Send_Data_MAX7219_MD(REG_TEST_MAX7219,CMD_TEST,device);
    __delay_ms(500);
    Send_Data_MAX7219_MD(REG_TEST_MAX7219,0,device);
}

void Shutdown_MAX7219_MD(unsigned char mode, unsigned char device){
    Send_Data_MAX7219_MD(REG_SHUTDOWN_MAX7219,mode,device);
}

void ClearDisplay_MAX7219_MD(unsigned char display, unsigned char device){
    Shine_LEDs_MAX7219_MD(display,0x00,device);
}
void Clear_Matrix_MAX7219_MD(unsigned char device){
    for(unsigned char i=0;i<MAX7219_MAX_DISPLAYs;i++){
        ClearDisplay_MAX7219_MD(i+1,device);
    }
}
void Clear_ALL_MD(){
    for(unsigned char i=0;i<N_MATRIX;i++){
        Clear_Matrix_MAX7219_MD(i);
    }
}
#endif	/* MAX_7219_MDS_PIC_H */

