import sys
import os
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import functools
import numpy as np
import random as rd
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib.animation import TimedAnimation
from matplotlib.lines import Line2D
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import time
import threading
import serial
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

from scipy.signal import butter, lfilter, freqz
import matplotlib.pyplot as plt
from scipy import signal

from scipy.signal import cheby1, freqz  # Чебышева 



ComPort = serial.Serial('COM7') 
ComPort.baudrate = 9600          
ComPort.bytesize = 8            
ComPort.parity   = 'N'           
ComPort.stopbits = 1            

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []


class CustomMainWindow(QMainWindow):
    def __init__(self):
        super(CustomMainWindow, self).__init__()
        # Define the geometry of the main window
        self.setGeometry(300, 300, 800, 400)
        self.setWindowTitle("my first window")
        # Create FRAME_A
        self.FRAME_A = QFrame(self)
        self.FRAME_A.setStyleSheet("QWidget { background-color: %s }" % QColor(210,210,235,255).name())
        self.LAYOUT_A = QGridLayout()
        self.FRAME_A.setLayout(self.LAYOUT_A)
        self.setCentralWidget(self.FRAME_A)
        # Place the zoom button
        self.zoomBtn = QPushButton(text = 'zoom')
        self.zoomBtn.setFixedSize(100, 50)
        self.zoomBtn.clicked.connect(self.zoomBtnAction)
        self.LAYOUT_A.addWidget(self.zoomBtn, *(0,0))
        # Place the matplotlib figure
        self.myFig = CustomFigCanvas()
        self.LAYOUT_A.addWidget(self.myFig, *(0,1))
        # Add the callbackfunc to ..
        myDataLoop = threading.Thread(name = 'myDataLoop', target = dataSendLoop, daemon = True, args = (self.addData_callbackFunc,))
        myDataLoop.start()
        self.show()
        return

    def zoomBtnAction(self):
        print("zoom in")
        self.myFig.zoomIn(5)
        return

    def addData_callbackFunc(self, value):
        # print("Add data: " + str(value))
        self.myFig.addData(value)
        return

''' End Class '''


class CustomFigCanvas(FigureCanvas, TimedAnimation):
    def __init__(self):
        self.addedData = []
        print(matplotlib.__version__)
        # The data
        self.xlim = 1000
        self.n = np.linspace(0, self.xlim - 1, self.xlim)
        a = []
        b = []
        a.append(2.0)
        a.append(4.0)
        a.append(2.0)
        b.append(4.0)
        b.append(3.0)
        b.append(4.0)
        self.y = (self.n * 0.0) + 50
        # The window
        self.fig = Figure(figsize=(5,5), dpi=100)
        self.ax1 = self.fig.add_subplot(111)
        # self.ax1 settings
        self.ax1.set_xlabel('time')
        self.ax1.set_ylabel('raw data')
        self.line1 = Line2D([], [], color='blue')
        self.line1_tail = Line2D([], [], color='red', linewidth=2)
        self.line1_head = Line2D([], [], color='red', marker='o', markeredgecolor='r')
        self.ax1.add_line(self.line1)
        self.ax1.add_line(self.line1_tail)
        self.ax1.add_line(self.line1_head)
        self.ax1.set_xlim(0, self.xlim - 1)
        self.ax1.set_ylim(-1000, 2000) # ildar
        FigureCanvas.__init__(self, self.fig)
        TimedAnimation.__init__(self, self.fig, interval = 50, blit = True)
        return

    def new_frame_seq(self):
        return iter(range(self.n.size))

    def _init_draw(self):
        lines = [self.line1, self.line1_tail, self.line1_head]
        for l in lines:
            l.set_data([], [])
        return

    def addData(self, value):
        self.addedData.append(value)
        return

    def zoomIn(self, value):
        bottom = self.ax1.get_ylim()[0]
        top = self.ax1.get_ylim()[1]
        bottom += value
        top -= value
        self.ax1.set_ylim(bottom,top)
        self.draw()
        return

    def _step(self, *args):
        # Extends the _step() method for the TimedAnimation class.
        try:
            TimedAnimation._step(self, *args)
        except Exception as e:
            self.abc += 1
            print(str(self.abc))
            TimedAnimation._stop(self)
            pass
        return

    def _draw_frame(self, framedata):
        margin = 2
        while(len(self.addedData) > 0):
            self.y = np.roll(self.y, -1)
            self.y[-1] = self.addedData[0]
            del(self.addedData[0])

        self.line1.set_data(self.n[ 0 : self.n.size - margin ], self.y[ 0 : self.n.size - margin ])
        self.line1_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y[-10:-1 - margin], self.y[-1 - margin]))
        self.line1_head.set_data(self.n[-1 - margin], self.y[-1 - margin])
        self._drawn_artists = [self.line1, self.line1_tail, self.line1_head]
        return

''' End Class '''


# You need to setup a signal slot mechanism, to
# send data to your GUI in a thread-safe way.
# Believe me, if you don't do this right, things
# go very very wrong..
class Communicate(QObject):
    data_signal = pyqtSignal(float)

''' End Class '''





def butter_lowpass_filter(data):    
    b, a = butter(3, 0.05)
    y = lfilter(b, a, data)
    return y

#b, a = cheby1(order, Apass, wn)  # Чебышева 
#w, h = freqz(b, a, worN=8000)

#b, a = signal.bessel(1, self.cutoff_freq / nyquist, btype="low", analog=0, output="ba")  # фильтр bessel 


#data=np.zeros((1, 150))
def dataSendLoop(addData_callbackFunc):
    # Setup the signal-slot mechanism.
    mySrc = Communicate()
    mySrc.data_signal.connect(addData_callbackFunc)

    ar=0
    data=np.array([])
    check=11
    while(True):
              

        voltage = ComPort.readline()
        
        try:
         voltage=int(voltage)
            
        except ValueError:
         print("voltage=0 ")         
         voltage=0 

        data=np.append(data, voltage, axis=None)
        #mySrc.data_signal.emit(data[a])
      #  print (len(data))
        if (len(data)==250):

         y = butter_lowpass_filter(data)
         ar=0
         data=np.array([])
         check=22
        #else:
      #   check=11
         
        #data=np.append(data, voltage, axis=None)
        if check==22: 
         mySrc.data_signal.emit(y[ar])

         ar=ar+1
         #print (ar)

if __name__== '__main__':
    app = QApplication(sys.argv)
    QApplication.setStyle(QStyleFactory.create('Plastique'))
    myGUI = CustomMainWindow()
    sys.exit(app.exec_())
