#include "mbed.h"

void Rx_interrupt();
Serial pc(USBTX, USBRX);
Serial mymbed(p9,p10);


DigitalOut myled(LED1);

int main() {
    char temp;
    pc.printf("Hello World!\n\r");
    
    mymbed.attach(&Rx_interrupt, Serial::RxIrq);   // Serial 아래 Rxirq
    while(1) {
        myled =1;
        
        temp=pc.getc();
      
        
        mymbed.putc(temp+2);  // rx가 data받는 순간 interrupt 발생, rx_interrupt의 일 수행, 1바이트씩 처리 
       
        mymbed.printf("test");
        
    }
}

 void Rx_interrupt()
 { 
 char temp;
 
 while (mymbed.readable()){
       temp=mymbed.getc(); 
           while(!pc.writeable());  //wait writeable 안되면 while 계속 돈다.
            pc.printf("\n\rThe received character in my mbed:"); 
            pc.putc(temp); 
             pc.putc('\n');
             pc.putc('\r');
          }

    }  
