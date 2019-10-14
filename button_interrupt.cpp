#include "mbed.h"


InterruptIn button(p5);
DigitalOut led(LED1);
DigitalOut flash(LED4);
Serial pc(USBTX,USBRX);

int i=0;
void ISR1(){led=!led; 
for (i=0;i<100;i++){pc.printf("inthe service \n\r");}
}

int main() {
    pc.baud(9600);
    button.mode(PullDown);
    button.rise(&ISR1);
    
     
    while(1){
        flash=!flash;
        wait(10);
        
        }
    
}