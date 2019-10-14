#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
void measure();
Serial pc(USBTX,USBRX);
DigitalOut led1(LED1);
DigitalOut led4(LED4);
DigitalIn responseinput(p5,PullDown); // p5로 PullDown Signal(initial value)
Timer t;
Timeout action;


int main() {
    pc.printf("reaction time test\n\r");
    pc.printf("------------------------\n\r");
    
    while(1) {
        int r_delay;
        pc.printf("new test\n\r");
        led4=1;
        wait(2);
        led4=0;
        r_delay=rand()%5+5;
        pc.printf("The random number is   %i\n\r", r_delay);
        action.attach(&measure,r_delay); // timeout
        wait(10);
        }
        }
void measure() {
        if(responseinput==1){
            pc.printf("don't hold the button!!!\n\r");
            }
        else {
   
        led1=1;
        t.start();
        wait(0.05);
        led1=0;
        
        while(responseinput==0); // 0일 떄 이 line 계속 루프
        t.stop();
        pc.printf("Your response time was %f  seconds\n\r", t.read());
        t.reset();
              
        }
}
