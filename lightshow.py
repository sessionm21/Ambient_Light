#!/bin/python
import serial, math, time

ser = serial.Serial('/dev/ttyUSB0', 9600)

def send_color(r,g,b):
    ser.write(b'4')
    ser.write(str.encode(r))
    #ser.write(int(r).to_bytes(1,'little'))
    ser.write(b'^')
    ser.write(str.encode(g))
    #ser.write(int(g).to_bytes(1,'little'))
    ser.write(b'^')
    ser.write(str.encode(b))
    #ser.write(int(b).to_bytes(1,'little'))
    ser.write(b'^')
for i in range(255):
    #send_color(127*math.sin(i)+128, 127*math.sin(i+90)+128, 127*math.sin(i+180)+128)
    #send_color( str(i) , str(0), str(0))
    send_color( str(0) , str(i), str(0))
    time.sleep(.01)

ser.close()
