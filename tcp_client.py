#Referencing Beej's Guide to Network Programming Using Internal Sockets
#Referencing https://gist.github.com/seanmcgary/627768
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

        clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        clientsocket.connect((host,port))
        message = input("Enter message pleb: (to quit enter \"T\"): ")
        if(message == "T"):

            break
        print("\nSent: " + message)
        clientsocket.send(message.encode())

        recieved = 0
        expected = len(message)

        while recieved < expected:
            data = clientsocket.recv(1000)
            recieved += len(data)
            print("Got: " + data.decode() + "\n")
finally:
    print("Closed")
    clientsocket.close()
