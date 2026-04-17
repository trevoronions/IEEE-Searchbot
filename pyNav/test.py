# Importing Libraries 
import serial 
import time 
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1) 
def read(): 
    time.sleep(0.05) 
    data = arduino.readline().strip().decode('utf-8')
    return data 
while True: 
    value = read() 
    print(value) # printing the value 

