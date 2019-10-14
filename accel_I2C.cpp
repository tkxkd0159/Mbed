#include "mbed.h"
#define PWR_CTR 0x2D
#define Measurement 0x08


unsigned char read_single(unsigned char address);
void write_single(unsigned char address, unsigned char data);
int read_double(unsigned char address);
void ADXL_init(void);


Serial pc(USBTX,USBRX);
I2C I2C_port( p9, p10);        // mosi, miso, sclk 

int ADXL_I2C_address=0x53<<1;

int main() {

    //unsigned char read_val;      
    int accel_x, y, z;  // no convert data
    double newaccel_x, newy, newz; // g convert data

    ADXL_init();
   
   
 
    while(1) {

        
      
        
    /*  read_val=read_single(0x00); // read device ID

        pc.printf("Device ID =  %X  \n\r",read_val);  // %Xh는 16 진수 형식지정자(즉 printf에서 표현되는 형)
        wait(1);
*/
        accel_x=read_double(0x32);
        newaccel_x = accel_x*0.004;
        y = read_double(0x34);
        newy = y*0.004;
        z=read_double(0x36);
        newz = z*0.004;
       pc.printf("test_x =  %d \t test_y = %d \t test_z = %d \n\r ",accel_x, y, z);
       pc.printf("accel_x =  %.2lf  \t y = %.2lf \t z = %.2lf \n\r ",newaccel_x, newy, newz);
          wait(1);
          

       }
}



unsigned char read_single(unsigned char address)
{
    char received[1], t_addr[1];
   
    t_addr[0]=address; //register address
    I2C_port.write(ADXL_I2C_address, t_addr,1,1);
    I2C_port.read(ADXL_I2C_address, received,1,0);
   

    return received[0];
    
    }
int read_double(unsigned char address)
{    
        
    char received[2], t_addr[1];
    int i_received;
    short *short_rp;
    short_rp = (short*)received;
    t_addr[0]=address; //register address
    I2C_port.write(ADXL_I2C_address, t_addr,1,1);
    I2C_port.read(ADXL_I2C_address, received,2,0);
    i_received = *short_rp;  
    wait_us(1);

    return i_received;
    
    }
    
    
void write_single(unsigned char address, unsigned char data)
{
    char data_w[2];
    
    data_w[0]=address;
    data_w[1]= data;
    I2C_port.write(ADXL_I2C_address, data_w,2,0);
       
    }

void ADXL_init(void){
    
   
    I2C_port.frequency(100000);

    wait(0.1);
    write_single(PWR_CTR, Measurement);  // Measurement mode
    
    wait_us(10);    
   
    }
