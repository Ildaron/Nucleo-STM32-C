import serial
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import time
import threading

ComPort = serial.Serial('COM6') 
ComPort.baudrate = 115200       
ComPort.bytesize = 8            
ComPort.parity   = 'N'           
ComPort.stopbits = 1        

send_command="AT+CIPSEND=0,5".encode('utf-8')
print (send_command)
send_data="ilron".encode('utf-8')

import socket
s = socket.socket(
socket.AF_INET, socket.SOCK_STREAM)
s.connect(("ip", port))

def startCounting():
 thread = threading.Thread(target=something)
 thread.start()

def startCounting1():
 thread = threading.Thread(target=something1)
 thread.start()

def something():
 while 1:
  time.sleep(1) 
  print("ok1")
  ComPort.write(send_command)
  time.sleep(1)
  ComPort.write(send_data)
 # ComPort.writelines(send_command)
 # ComPort.writelines(send_data)
  time.sleep(1)
  print("ok1")

def something1():
 while 1:
  print ("ok")
  data = str(s.recv(1024),encoding='utf-8')
  print(data)

startCounting1()
startCounting()

#while True:


