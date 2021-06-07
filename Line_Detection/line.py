THRESHOLD = (32, 6, -94, 127, -55, 84) # Grayscale threshold for dark things...
import sensor, image, time,pyb
from pyb import LED
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.001, i=0)

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    l = img.get_regression([(100,100)], robust = True)
    if (l):
        img.draw_line(l.line(), color = 127)
        print_args = (l.x1(),l.y1(),l.x2(),l.y2())
        #print("%f,%f,%f,%f" % print_args)
        if (l.theta() < 165 and l.theta() > 90): #or (l.x1() < 20) or (l.x2() < 20):
           detection = 2
           s = 0.7
        elif (l.theta() > 15 and l.theta() < 90): #or (l.x1() > 70) or (l.x2() >70):
           detection = 1
           s = 0.7

        else:
           detection = 0
           s = 0.5
        uart.write(("%d\r\n" % detection).encode())
        print("%d" % detection)
        print(l.theta())
        print(l.rho())
        time.sleep(1)
