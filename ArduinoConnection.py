import serial
import time
import serial.tools.list_ports

baudrate = 9600

def find_port():
    ports = list(serial.tools.list_ports.comports())
    if(not len(ports)):
        print("CONNECT AN ARDUINO!")
        return False
    return ports[2].device

def send_command(command):
    port = find_port()
    if(not port):
        return False
    print("SENDING DATA TO PORT: {}".format(port))
    arduino = serial.Serial(port=port, baudrate=baudrate, timeout=.1)
    arduino.write(bytes(command).encode("utf-8"))
    while True:
        if (arduino.readline().strip() == "4444"):
            break
        else:
            arduino.write(bytes(command).encode("utf-8"))
        time.sleep(0.1)
    arduino.close()
    return True

while True:
    x = input("Command is ")
    send_command(x)