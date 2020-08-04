import sys
import os
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import numpy as np
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib.animation import TimedAnimation
from matplotlib.lines import Line2D
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import time
import threading
import serial
import matplotlib.pyplot as plt

ComPort = serial.Serial('COM13') 
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
        # the main window
        self.setGeometry(300, 300, 800, 400)
        self.setWindowTitle("graph")

        self.FRAME_A = QFrame(self)
        self.FRAME_A.setStyleSheet("QWidget { background-color: %s }" % QColor(210,210,235,255).name())
        self.LAYOUT_A = QGridLayout()
        self.FRAME_A.setLayout(self.LAYOUT_A)
        self.setCentralWidget(self.FRAME_A)
        
        #zoom button
        self.zoomBtn = QPushButton(text = 'Scale')
        self.zoomBtn.setFixedSize(100, 50)                
        self.zoomBtn.clicked.connect(self.zoomBtnAction) #
                
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
        #self.FRAME_A = QFrame(self)
        self.myFig.zoomIn(voli)
        return

    def addData_callbackFunc(self, value):
        # print("Add data: " + str(value))
        self.myFig.addData(value)
        return

class CustomFigCanvas(FigureCanvas, TimedAnimation):
    def __init__(self):
        self.addedData = []
        print(matplotlib.__version__)
        # The data       
        self.xlim = 2000 

        
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
        self.ax1.set_xlim(0, self.xlim-1)
        
        FigureCanvas.__init__(self, self.fig)
        TimedAnimation.__init__(self, self.fig, interval = 1, blit = True)
        return

    def new_frame_seq(self):
        return iter(range(self.n.size))

    def addData(self, value):
        self.addedData.append(value)
        return
    def zoomIn(self, value):
        a=100
        self.ax1.set_ylim(value-10000,value+10000)
        #self.ax1.set_xlim(-a-100,a+100)
       # self.draw()  
       # return


    def _draw_frame(self, framedata):
        margin = 2
        while(len(self.addedData) > 0):
            self.y = np.roll(self.y, -1)
            self.y[-1] = self.addedData[0]
            del(self.addedData[0])

        self.line1.set_data(self.n[ 0 : self.n.size - margin ], self.y[ 0 : self.n.size - margin ])
        #self.line1_tail.set_data(np.append(self.n[-10:-1 - margin], self.n[-1 - margin]), np.append(self.y[-10:-1 - margin], self.y[-1 - margin]))
        #self.line1_head.set_data(self.n[-1 - margin], self.y[-1 - margin])
     #   self._drawn_artists = [self.line1, self.line1_tail, self.line1_head]
        return

class Communicate(QObject):
    data_signal = pyqtSignal(float)

def dataSendLoop(addData_callbackFunc):
    mySrc = Communicate()
    mySrc.data_signal.connect(addData_callbackFunc)
    while(True):
        voltage = ComPort.readline()
        try:
         voltage=int(voltage)
         print (voltage)        
        except ValueError:
         voltage=0 

        global voli
        voli = voltage
        ys.append(voli)        
        mySrc.data_signal.emit(voli) # 
        
       
if __name__== '__main__':
    app = QApplication(sys.argv)
    QApplication.setStyle(QStyleFactory.create('Plastique'))
    myGUI = CustomMainWindow()
   # sys.exit(app.exec_())
