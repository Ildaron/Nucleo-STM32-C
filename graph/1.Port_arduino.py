# pip install pyserial

import serial                    # import pySerial module
ComPort = serial.Serial('COM7') # open the COM Port
ComPort.baudrate = 9600          # set Baud rate
ComPort.bytesize = 8             # Number of data bits = 8
ComPort.parity   = 'N'           # No parity
ComPort.stopbits = 1             # Number of Stop bits = 1
data = ComPort.readline()        # Wait and read data
print(data)                      # print the received data
ComPort.close()                  # Close the COM Port
