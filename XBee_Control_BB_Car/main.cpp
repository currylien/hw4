#include "mbed.h"
#include "bbcar.h"
#include "mbed_rpc.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);
void reverse_park(Arguments *in, Reply *out);
RPCFunction rpcreverse_park(&reverse_park, "reverse_park");

int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   }
}
void reverse_park (Arguments *in, Reply *out) {
    double d1 = in->getArg<double>();
    double d2 = in->getArg<double>();
    int direction = in->getArg<double>();
    int D1_for, D2_for, D1_back, D2_back;
    int parking_lot1 = (int)((14 - 1.68) / 15.3*1000.0);
    int parking_lot2 = (int)((12 - 0.98) / 14.6*1000.0);
    int width1 = (int)((8 - 1.68) / 15.3*1000.0);
    int width2 = (int)((8 - 0.98) / 14.6*1000.0);
    int buffer1 = (int)((5 - 1.68) / 15.3*1000.0);
    int buffer2 = (int)((5 - 0.98) / 14.6*1000.0);
    double d1t, d2t;
    if (d1 < 0) d1t = -d1;
    else d1t = d1;
    if (d2 < 0) d2t = -d2;
    else d2t = d2;
    D1_for = (int)((d1t - 1.68) / 15.3 *1000.0);
    D2_for = (int)((d2t - 1.68) / 15.3*1000.0);
    D1_back = (int)((d1t - 0.98) / 14.6*1000.0);
    D2_back = (int)((d2t - 0.98) / 14.6*1000.0);
    if (direction == 1) {
      if (d1 > 0 && d2 >0) {
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 > 0 && d2 < 0) {
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 > 0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 < 0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
        }
    } else if (direction == 2) {
      if (d1 > 0 && d2 >0) {
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 > 0 && d2 < 0) {
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         ThisThread::sleep_for(70ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 > 0) {
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 < 0) {
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         ThisThread::sleep_for(70ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
        }
    } else if (direction == 3) {
      if (d1 > 0 && d2 >0) {
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(400ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 > 0 && d2 < 0) {
         car.goStraight(100);
         ThisThread::sleep_for(400ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(320ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 > 0) {
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 < 0) {
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(700ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
        }
    }else if (direction == 4) {
      if (d1 > 0 && d2 >0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(400ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 > 0 && d2 < 0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D1_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 > 0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D2_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(width1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
      } else if (d1 < 0 && d2 < 0) {
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(100);
         ThisThread::sleep_for(D1_for * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(parking_lot1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(buffer1 * 1ms);
         car.goStraight(100);
         ThisThread::sleep_for(500ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(50,1);
         ThisThread::sleep_for(970ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(D2_back * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(width2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(700ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.turn(-50,1);
         ThisThread::sleep_for(940ms);
         car.stop();
         ThisThread::sleep_for(500ms);
         car.goStraight(-100);
         ThisThread::sleep_for(buffer2 * 1ms);
         car.goStraight(-100);
         ThisThread::sleep_for(parking_lot2 * 1ms);
         car.stop();
        }
    }
    return;
}