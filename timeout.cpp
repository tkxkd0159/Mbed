#include "mbed.h"
void blink_end(void);
void blink(void);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
Timeout Response;
Timeout Response_duration;
InterruptIn button(p5);

void blink(){
    led2=1;
  
    Response_duration.attach(&blink_end,1);
}

void blink_end(){    //여기까지 명령예약끝나는 순간 다시 Main code
    led2=0;          //실행시간:1초(LED3)+명령예약시간 
    }

void ISR1(){
    led3=1;         // interrupt start
  wait(1);
  
    Response.attach(&blink,2); // 2초후에 명령하는게 아니라 미리 명령 내려놈. 따라서 인터럽트 끝나므로 main 돈다.
                               // 즉, Timer관련 기능은 미리 명령예약
    }
    
DigitalOut myled(LED1);

int main() {
    button.mode(PullDown);
    button.rise(&ISR1);
    while(1) {
        led3=0;
        led1 = !led1;
        wait(1);
    }
}
