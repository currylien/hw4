**Part1**  
main.cpp  
```c
#include "mbed.h"
#include "bbcar.h"
#include "mbed_rpc.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);
void reverse_park(Arguments *in, Reply *out);
RPCFunction rpcreverse_park(&reverse_park, "reverse_park");  // RPC function for XBee

int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {                                               // read RPC command
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
void reverse_park (Arguments *in, Reply *out) {             // RPC function for reverse parking
    double d1 = in->getArg<double>();                       // distance 1
    double d2 = in->getArg<double>();                       // distance 2
    int direction = in->getArg<double>();                   // direction for the front of car (E W S N)
    int D1_for, D2_for, D1_back, D2_back;
    int parking_lot1 = (int)((14 - 1.68) / 15.3*1000.0);    // transfer function for going distance
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
    if (direction == 1) {                                   // if car face east
      if (d1 > 0 && d2 >0) {                                // car is at first quadrant
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
      } else if (d1 > 0 && d2 < 0) {                        // car is at second quadrant
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
      } else if (d1 < 0 && d2 > 0) {                      // car is at forth quadrant
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
      } else if (d1 < 0 && d2 < 0) {                     // car is at third quadrant
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
    } else if (direction == 2) {                         // if car face west
      if (d1 > 0 && d2 >0) {                             // car is at first quadrant
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
      } else if (d1 > 0 && d2 < 0) {                     // car is at second quadrant
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
      } else if (d1 < 0 && d2 > 0) {                    // car is at forth quadrant
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
      } else if (d1 < 0 && d2 < 0) {                     // car is at third quadrant
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
    } else if (direction == 3) {                            // if car face south
      if (d1 > 0 && d2 >0) {                                // car is at first quadrant
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
      } else if (d1 > 0 && d2 < 0) {                     // car is at second quadrant
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
      } else if (d1 < 0 && d2 > 0) {                      // car is at forth quadrant
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
      } else if (d1 < 0 && d2 < 0) {                    // car is at third quadrant
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
    }else if (direction == 4) {                         // if car face north
      if (d1 > 0 && d2 >0) {                            // car is at first quadrant
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
      } else if (d1 > 0 && d2 < 0) {                    // car is at second quadrant
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
      } else if (d1 < 0 && d2 > 0) {                     // car is at forth quadrant
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
      } else if (d1 < 0 && d2 < 0) {                    // car is at third quadrant
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
```  
**Part2**  
main.cpp  
```c  
#include"mbed.h"
#include "bbcar.h"
#include "mbed_rpc.h"
#include "bbcar_rpc.h"
BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

int main(){
   uart.set_baud(9600);                             // buad rate for uart comunication
   while(1){
      if(uart.readable()){
            char recv[1];                           // reaad one char from open MV
            uart.read(recv, sizeof(recv));
            if (recv[0] == '1') {                   // command from open MV for turn right
                car.turn(50,0);
                ThisThread::sleep_for(200ms);
                car.stop();
                ThisThread::sleep_for(500ms);
            } else if (recv[0] == '2') {            // command from open MV for turn left
                car.turn(-50,0);
                ThisThread::sleep_for(200ms);
                car.stop();
                ThisThread::sleep_for(500ms);
            } else if (recv[0] == '0') {            // command from open MV for go straight
                car.goStraight(50);
                ThisThread::sleep_for(500ms);
                car.stop();
            } else {                                // if detect no lines, car stop
                car.stop();
            } 
        pc.write(recv, sizeof(recv));               // print out received command
      }
   }
}
```  
Line.py
```python
THRESHOLD = (32, 6, -94, 127, -55, 84) # Grayscale threshold for dark things...
import sensor, image, time,pyb

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
sensor.reset()
sensor.set_vflip(True)                # since open MV is oppisite,
sensor.set_hmirror(True)              # we turn on flipping and mirror image
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    l = img.get_regression([(100,100)], robust = True)     # use line regression to find line
    if (l):
        img.draw_line(l.line(), color = 127)        
        #print("%f,%f,%f,%f" % print_args)
        if (l.theta() < 165 and l.theta() > 90): 
           detection = 2                                   # if theta excceed some range, car needs to turn left
           s = 0.7
        elif (l.theta() > 15 and l.theta() < 90): 
           detection = 1                                   # if theta excceed some range, car needs to turn right
           s = 0.7

        else:
           detection = 0                                   # if angle is in some range, car go straight
           s = 0.5
        uart.write(("%d\r\n" % detection).encode())        # send data to mbed
        print("%d" % detection)
        print(l.theta())
        print(l.rho())
        time.sleep(1)
 ```
 **Part 3**
