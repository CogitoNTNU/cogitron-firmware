from time import sleep
import serial

ser = serial.Serial('/dev/tty.usbmodem14101', 9600) # Establish the connection on a specific port

byteReceived = 0
messageReceived = ""


while True:
    byteReceived = ord(ser.read())
    letter = chr(byteReceived)
    messageReceived += letter
    print(letter) # Read the newest output from the Arduino
    
    if byteReceived == 0:
        break

print(messageReceived)

