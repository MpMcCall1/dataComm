#Referencing Beej's Guide to Network Programming Using Internal Sockets
#Referencing https://stackoverflow.com/questions/27893804/udp-client-server-socket-in-python
import sys
import socket
from threading import *

if(len(sys.argv) < 3):
    raise Exception("Not enough arguements")

host = sys.argv[1]
port = int(sys.argv[2])
print("Host: " + host)
print("Port: " + str(port))

try:
    while True:
        clientsocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        clientsocket.connect((host,port))
        message = input("Enter message pleb: (to quit enter \"T\"): ")
        if(message == "T"):
            break
        print("\nSent: " + message)
        clientsocket.send(message.encode())

        recieved = 0
        expected = len(message)


finally:
    print("Closed")
    clientsocket.close()
