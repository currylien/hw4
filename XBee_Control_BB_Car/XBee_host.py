import serial
import time

# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)
#while True:
    # send RPC to remote
s.write("/reverse_park/run -13 5 4\n".encode())
time.sleep(1)
s.close()