#include "Hostinit.h"

Serial pc(USBTX, USBRX);


        void HostInit(void){
            pc.printf("\n\r Type two  digit numbers to be displayed\n\r");
            
            }
            
        char Getkeyinput(void){
                char c = pc.getc();
                pc.printf("%c",c);
                return (c&0x0F);  // Convert ASCII Code to case number
                }