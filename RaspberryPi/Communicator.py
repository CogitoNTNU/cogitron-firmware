import fakeSerial as emu
import serial as real


class Communicator(object):
    def __init__(self, communicator):
        if communicator == "emu":
            self.com = emu.Serial(9600)
        elif communicator == "real":
            self.com = real.Serial("/dev/tty.usbmodem14101", 9600)

    def sendMessage(self, message):
        self.com.open()
        self.com.write(message)
        self.com.close()

    def receiveMessage(self):
        self.com.open()
        message = self.com.readline()
        self.com.close()
        return message


if __name__ == "__main__":
    bob = Communicator("real")
    bob.sendMessage("driveForward")
    print(bob.receiveMessage())
