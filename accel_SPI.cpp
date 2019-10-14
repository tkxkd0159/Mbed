#include "mbed.h"
#define PWR_CTR 0x2D
#define Measurement 0x08

unsigned char read_single(unsigned char address);
void write_single(unsigned char address, unsigned char data);
int read_double(unsigned char address);
void SPI_init(void);


Serial pc(USBTX,USBRX);
SPI SPI_port( p11, p12, p13);        // mosi, miso, sclk 
DigitalOut cs( p14);                // this acts as "Slave select“


                     
union word_byte {short word;
                 unsigned char byte[2];}; // union = data 묶어줌, measure 안에 short형의 word와 unsigned char형의 byte[2] 변수생성
                 
union word_byte measure; // measure라는 그룹으로 만듬



int main() {

    //unsigned char read_val;      
    float accel_x, y, z;
    

    SPI_init();
    
 
    while(1) {

        
       // read_val=0x00;
        
      //  read_val=read_single(0x00); // read device ID

      //  pc.printf("Device ID =  %X  \n\r",read_val);  // %Xh는 16 진수 형식지정자(즉 printf에서 표현되는 형)
      //  wait(1);

        accel_x=read_double(0x32);
        accel_x = accel_x*0.004;
        y = read_double(0x34);
        y = y*0.004;
        z=read_double(0x36);
        z = z*0.004;
        pc.printf("accel_x =  %.2f  \t y = %.2f \t z = %.2f \n\r ",accel_x, y, z);
          wait(0.5);

       }
}



unsigned char read_single(unsigned char address)
{
    unsigned char received;
    cs=0;
    SPI_port.write(address|0x80); // 1byte읽기(1000 0000) >> 원하는 데이터 주소로 감
    received=SPI_port.write(address|0x80); //데이터
    cs=1;
    wait_us(1);
    return received;
    
    }
int read_double(unsigned char address)
{    
        cs=0;
    SPI_port.write(address|0xc0); // 2byte읽기(1100 0000) >>mutiple byte bit가 두번째 1에 해당됨
    measure.byte[0]=SPI_port.write(address|0xc0);   // 첫번째 데이터(0x32에 해당하는)
    measure.byte[1]=SPI_port.write(address|0xc0);  // 두번째 데이터(0x33에 해당하는)  >> 숫자늘리면 세번째. 네번째 ~ 쭉 읽을 수 있음
        cs=1;
    wait_us(1);
   // pc.printf("received1=  %XH  \n\r",measure.byte[0]);
   // pc.printf("received2=  %XH  \n\r",measure.byte[1]);
   // pc.printf("combined=   %d    \n\r",measure.word); 
    return (int)measure.word;
    
    }
    
    
void write_single(unsigned char address, unsigned char data)
{
    cs=0;
    SPI_port.write(address|0x00);
    SPI_port.write(data);
    cs=1;
    wait_us(1);
       
    }

void SPI_init(void){
    
    SPI_port.format(8,3); // 8bit mode3
    SPI_port.frequency(400000);
//enter measurement mode
    wait(0.1);
    write_single(PWR_CTR, Measurement);  // Measurement mode
    wait_us(10);    
    }