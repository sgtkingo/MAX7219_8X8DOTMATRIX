#ifndef MAX7219_CHARSET_H
#define	MAX7219_CHARSET_H

#define MAX7219_MAX_DISPLAYs 8

unsigned char* getNumber(unsigned char number);

const unsigned char NUMBERS[][MAX7219_MAX_DISPLAYs] = {
{
  0B00110000,
  0B01001000,
  0B01001000,
  0B01001000,
  0B01001000,
  0B01001000,
  0B01001000,
  0B00110000
},{
  0B00010000,
  0B00110000,
  0B01010000,
  0B00010000,
  0B00010000,
  0B00010000,
  0B00010000,
  0B00111000
},{
  0B00110000,
  0B01001000,
  0B01001000,
  0B00010000,
  0B00100000,
  0B01000000,
  0B01000000,
  0B01111000
},{
  0B00110000,
  0B01001000,
  0B00001000,
  0B00010000,
  0B00110000,
  0B00001000,
  0B00001000,
  0B01110000
},{
  0B00010000,
  0B00100000,
  0B01010000,
  0B01010000,
  0B01110000,
  0B00010000,
  0B00010000,
  0B00111000
},{
  0B01111000,
  0B01000000,
  0B01000000,
  0B01111000,
  0B00001000,
  0B00001000,
  0B01001000,
  0B01110000
},{
  0B00010000,
  0B00100000,
  0B01000000,
  0B01000000,
  0B01111000,
  0B01001000,
  0B01001000,
  0B00110000
},{
  0B01111000,
  0B00001000,
  0B00010000,
  0B00100000,
  0B01000000,
  0B01000000,
  0B01000000,
  0B01000000
},{
  0B00110000,
  0B01001000,
  0B01001000,
  0B00110000,
  0B01001000,
  0B01001000,
  0B01001000,
  0B00110000
},{
  0B00110000,
  0B01001000,
  0B01001000,
  0B01111000,
  0B00001000,
  0B00001000,
  0B01001000,
  0B00110000
}};
//unsigned char *NUMBERS[9]={N_0,N_1,N_2,N_3,N_4,N_4,N_4,N_4,N_4};

unsigned char* getNumber(unsigned char number){
    if(number>-1 && number < 10){
        return NUMBERS[number];
    }
    else return NUMBERS[0];
}

#endif	/* MAX7219_CHARSET_H */

