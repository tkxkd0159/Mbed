#include "mbed.h"
#include "Segdisplay.h"
#include "Hostinit.h"


char data1;


int main(){
    SegInit();
    HostInit();
    while(1){
    data1 = Getkeyinput();
    
    seg1 = Segconvert(data1);
    pc.printf(" ");
    }
}