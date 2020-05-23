import serial
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

ComPort = serial.Serial('COM8') 
ComPort.baudrate = 9600          
ComPort.bytesize = 8            
ComPort.parity   = 'N'           
ComPort.stopbits = 1            

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

while 1:
 def animate(i, xs, ys): 
    voltage = ComPort.readline()
    try:
     voltage=int(voltage)
     print (voltage)
    except ValueError:
     voltage=0 
    xs.append(i)
    ys.append(voltage)

    xs = xs[-100:]
    ys = ys[-100:]
    ax.clear()
    ax.plot(xs, ys)

    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Voltage ADS1299')
    plt.ylabel('Voltage')
    return voltage,
  
 ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1)
 plt.show()
 ComPort.close()
            
