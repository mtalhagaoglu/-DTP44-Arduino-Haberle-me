import serial
import time
import serial.tools.list_ports

baudrate = 9600

def find_port():
    ports = list(serial.tools.list_ports.comports())
    if(not len(ports)):
        print("CONNECT AN ARDUINO!")
        return False
    return ports[0].device

def send_command(command):
    port = find_port()
    if(not port):
        return False
    print("SENDING DATA TO PORT: {}".format(port))
    arduino = serial.Serial(port=port, baudrate=baudrate, timeout=.1)
    is_received = False
    while(not is_received):
        arduino.write(bytes(command).encode("utf-8"))
        time.sleep(0.1)
        is_ok = arduino.readline().strip()
        time.sleep(0.1)
        if(is_ok == "4444"):
            is_received = True
    arduino.close()
    return True

while True:
    x = input("command to give: ")
    send_command(int(x))