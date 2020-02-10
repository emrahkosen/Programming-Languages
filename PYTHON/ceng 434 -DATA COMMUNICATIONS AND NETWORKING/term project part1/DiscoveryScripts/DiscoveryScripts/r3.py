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


def reciever(UDP_IP , UDP_IP2 , UDP_PORT , UDP_PORT2):
    totalTime = 0
    UDP_PORTr = UDP_PORT*10 + 5
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    sock.settimeout(10)
    data, addr = sock.recvfrom(1024)
    N = 0
    NN=0
    if data == "ready":
        data, addr = sock.recvfrom(1024)
        N = int(data)
        for i in range(N):
            try:
                data =  str(float(round(time.time() * 1000)))
                sock.sendto( data , (UDP_IP2, UDP_PORTr))
                data, addr = sock.recvfrom(1024)
                data = float(round(time.time() * 1000)) - float(data) #calculate time difference to find rtt
                if data  > 0:
                    totalTime += data
                    NN=NN+1
            except socket.timeout:
                break
        if NN:
            totalTime =  totalTime/(NN)  #taking avarage of rtts
        print totalTime
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    sock.sendto(str(totalTime) , ("10.10.7.1", UDP_PORT2))  #send rtt to d
    sock.sendto(str(totalTime) , ("10.10.7.1", UDP_PORT2))


UDP_IPs1 = "10.10.1.1"
UDP_IPs2 = "10.10.2.2"
UDP_IPs3 = "10.10.3.2"
UDP_IP12 = "10.10.8.2"
UDP_IP3 = "10.10.7.2"
UDP_IP23 = "10.10.6.2"
UDP_IP1d = "10.10.4.2"
UDP_IPd2 = "10.10.5.2"
UDP_IPd3 = "10.10.7.1"

UDP_PORT = 5005
UDP_PORT1 = 5001
UDP_PORT2 = 5002
UDP_PORTs3 = 5003
UDP_PORT23 = 50031

UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ]


#reciving rtt from s
s3 = threading.Thread(target= reciever, args=(UDP_IP[0][3], UDP_IP[3][0] ,UDP_PORT,UDP_PORTs3,))
s3.start()

#reciving rtt from r2
r23 = threading.Thread(target= reciever, args=(UDP_IP[2][3], UDP_IP[3][2], UDP_PORT,UDP_PORT23,))
r23.start()
#sending rtt to d
s3d = threading.Thread(target= sender, args=(100,"r3", UDP_IP[3][4], UDP_IP[4][3],UDP_PORT,))
s3d.start()


s3.join()
r23.join()
s3d.join()



sockd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sockd.bind(("10.10.7.2", 10000)) #getting routelist
data, addr = sockd.recvfrom(1024)


socks = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) #d den aldigi routelist s ye gonder
socks.sendto(data , ("10.10.3.1", 10001))

print data
f= open("routelist.txt","w+")
f.write(data)
f.close()
