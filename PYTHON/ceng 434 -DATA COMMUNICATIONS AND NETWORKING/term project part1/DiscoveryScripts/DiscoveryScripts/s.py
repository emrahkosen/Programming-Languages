#!/usr/bin/python
import threading
import thread
import socket
from datetime import datetime
import time


def sender(N, id, UDP_IP , UDP_IP2 , UDP_PORT ):
    UDP_PORTr = UDP_PORT*10 + 5
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    sock.bind((UDP_IP2, UDP_PORTr))
    sock.settimeout(10)
    sock.sendto("ready", (UDP_IP, UDP_PORT))
    sock.sendto(str(N) , (UDP_IP, UDP_PORT))
    for data in range(N):
        try:
            data, addr = sock.recvfrom(1024)
            sock.sendto( data , (UDP_IP, UDP_PORT)) #sending back to reciever
        except socket.timeout:
            break



#no reciever donest calculate


UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ]


UDP_PORT = 5005
#sending rtt to r1-r2-r3
s3 = threading.Thread(target= sender, args=(100,"s",UDP_IP[0][3], UDP_IP[3][0] ,UDP_PORT,))
s2 = threading.Thread(target= sender, args=(100,"s",UDP_IP[0][2], UDP_IP[2][0] ,UDP_PORT,))
s1 = threading.Thread(target= sender, args=(100,"s",UDP_IP[0][1], UDP_IP[1][0] ,UDP_PORT,))

s1.start()
s2.start()
s3.start()



s1.join()
s2.join()
s3.join()

sockr3 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sockr3.bind(("10.10.3.1", 10001))
data, addr = sockr3.recvfrom(1024) #getting routelist from r3
print data
f= open("routelist.txt","w+")
f.write(data)
f.close()
