#importing useful libraries
import serial
import numpy as np
import matplotlib.pyplot as plt
import time
from drawnow import *
import pandas as pd

#initializing lists for capturing data
xs_list = []
ys_list = []
#initializing arrays for making data useful

def makeFig():
    """This function creates a figure and plots our data on it"""
    plt.title("Live Local Mapping")
    plt.ylabel("Y cm")
    plt.xlabel("X cm")
    plt.plot(xs_array,ys_array,'r-')
    plt.xlim(-30,30)
    plt.ylim(0,30)

arduinoData = serial.Serial("/dev/ttyACM0",9600) #initializing serial communication

while (arduinoData.inWaiting()==0): #don't do anything until you recieve data
    pass

while True:
    """While running, read in the xs and ys from the arduino and plot them"""
    arduinoString = str(arduinoData.readline())[2:-6]
    try:
        xs_list = arduinoString.split(":")[0:5]
        xs_array = [float(x) for x in xs_list]
        ys_list = arduinoString.split(":")[5:10]
        ys_array = [ float(y) for y in ys_list]
        drawnow(makeFig)
    except:
        pass
