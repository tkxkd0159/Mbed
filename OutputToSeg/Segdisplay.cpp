#include "Segdisplay.h"

BusOut seg1(p5,p6,p7,p8,p9,p10,p11,p12);




void SegInit(void){
            seg1=Segconvert(0);
           
            }
            
char Segconvert(char Segvalue){
            char Segbyte=0x00;
            switch (Segvalue){
                case 0 : Segbyte = 0xC0;break;
                case 1 : Segbyte = 0xF9;break;
                case 2 : Segbyte = 0xA4;break;
                case 3 : Segbyte = 0xB0;break;
                case 4 : Segbyte = 0x99;break;
                case 5 : Segbyte = 0x92;break;
                case 6 : Segbyte = 0x82;break;
                case 7 : Segbyte = 0xF8;break;
                case 8 : Segbyte = 0x80;break;
                case 9 : Segbyte = 0x90;break;
                }
                return Segbyte;
                }