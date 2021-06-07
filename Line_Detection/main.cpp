#include"mbed.h"
#include "bbcar.h"
#include "mbed_rpc.h"
#include "bbcar_rpc.h"
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
//DigitalInOut pin11(D11);
InterruptIn button(USER_BUTTON);

//BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);
//Thread thread;
//void reverse_park(Arguments *in, Reply *out);
//RPCFunction rpcreverse_park(&reverse_park, "reverse_park");
/*int a = 0;
void car_start()
{
   a = !a;
}*/
int main(){
   //parallax_ping  ping1(pin11);
   //button.rise(&car_start);
   uart.set_baud(9600);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            if (recv[0] == '1') {
                car.turn(50,0);
                ThisThread::sleep_for(200ms);
                car.stop();
                ThisThread::sleep_for(500ms);
            } else if (recv[0] == '2') {
                car.turn(-50,0);
                ThisThread::sleep_for(200ms);
                car.stop();
                ThisThread::sleep_for(500ms);
            } else if (recv[0] == '0') {
                car.goStraight(50);
                ThisThread::sleep_for(500ms);
                car.stop();
            } else {
                car.stop();
            } 
        pc.write(recv, sizeof(recv));
      }
   }
}