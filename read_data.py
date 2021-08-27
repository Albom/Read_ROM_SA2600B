
import time
import serial

size = 512*1024

with serial.Serial('/dev/ttyACM0', 115200) as ser:
    time.sleep(1)
    data = [ser.read() for x in range(size)]
    data = b''.join(data)

with open('rom.bin', 'wb') as file:
    file.write(bytes(data))
