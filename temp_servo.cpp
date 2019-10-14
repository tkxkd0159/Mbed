#include "mbed.h"

AnalogIn TempIn(p20);
Serial pc(USBTX, USBRX);
PwmOut PWM1(p21);

int main() {
    PWM1.period(0.02);
    float Temp;
    
    while(1) {
      
      
      Temp = TempIn*3.3/0.01; //3.3은 Reference Volt 곱해준 거(mbed는 3.3V)
      
     if (Temp<=25){
       PWM1=1.1/20.0;
        pc.printf("%f \n\r", Temp);
         wait(0.5);
         }
        
        else if(25<Temp<=30)
        {
         PWM1=2.1/20.0;
         pc.printf("%f \n\r", Temp);
         wait(0.5);}
         
         else if(Temp>30)
         {
           PWM1=3.1/20.0;
          pc.printf("%f \n\r", Temp);
          wait(0.5);
         }
     
     
      
      
    }
}