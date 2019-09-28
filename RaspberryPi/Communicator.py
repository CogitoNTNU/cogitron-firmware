import fakeSerial as emu
import serial as real



class Communicator(object):
    def __init__(self, communicator):
        if communicator == "emu":
            self.com = emu.Serial(9600)
        elif communicator == "real":
            self.com = real.Serial("/dev/tty.usbmodem14101", 9600)

    def sendMessage(self, message):
        messageToBytes = bytes(message, 'utf-8')
        self.com.write(messageToBytes)


    def receiveMessage(self):
        bufferSize = 0
        messageReceived = ""
        while bufferSize<9: #needs another way to break the while loop, blocking read methods if no content.
            byteReceived = ord(self.com.read())
            letter = chr(byteReceived)
            messageReceived += letter
            bufferSize += 1
        return messageReceived


if __name__ == "__main__":
    bob = Communicator("real")
    print(bob.receiveMessage())
    bob.sendMessage("driveForward")
    print(bob.receiveMessage())
   
    

