#!/usr/bin/python
import threading
import thread
import socket
import time
f=open("routelist.txt", "r")
thisIndex = 4 #which host
UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ] #matrix for referencing connections



if f.mode == 'r': #reading routelist
    content =f.read()
    f.close()
    route = list(content.split(" "))
    for i in range(len(route)):
        route[i] = int(route[i])
    print route




    if route[thisIndex] != -2:


        if route[thisIndex] == -1: #for s host , calculations made here
            N=50
            sendHost = route.index(thisIndex)
            #send messages to UDP_ID[thisIndex][sendHost]

            sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
            sock.settimeout(10)
            sock.bind((UDP_IP[sendHost][thisIndex],5000+sendHost))
            for i in range(N):
                try:
                    time.sleep(10 / 1000)
                    data =  str(float(round(time.time() * 1000)))
                    sock.sendto( data , (UDP_IP[thisIndex][sendHost],5000+thisIndex))
                    data, addr = sock.recvfrom(1024)
                    data = float(round(time.time() * 1000)) - float(data) #rtt calculated
                    if data > 0:
                        print data

                except socket.timeout:
                    break
            sock.sendto( "end", (UDP_IP[thisIndex][sendHost],5000+thisIndex))




        elif thisIndex == 4:# for d host
            recieveHost = route[thisIndex]
            sockd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
            sockd.settimeout(10)
            sockd.bind((UDP_IP[recieveHost][thisIndex],5000+recieveHost))
            while True:
            #get message from UDP_ID[recieveHost][thisIndex]
                try:
                    data, addr = sockd.recvfrom(1024)
                    print "rec: " + data
                    if data== "end":
                        break
                    sockd.sendto( data , (UDP_IP[thisIndex][recieveHost],5000 + thisIndex)) #forward data
                except socket.timeout:
                    break






        else:
            sendHost = route.index(thisIndex)
            recieveHost = route[thisIndex]
            sockr = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
            socks = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
            sockr.settimeout(10)
            socks.settimeout(10)
            sockr.bind((UDP_IP[recieveHost][thisIndex],5000+recieveHost))
            socks.bind((UDP_IP[sendHost][thisIndex],5000+sendHost))
            while True:
            #first get message from UDP_ID[recieveHost][thisIndex]
                try:
                    data, addr = sockr.recvfrom(1024)
                    print "rec: " + data

                    #then send messages to UDP_ID[thisIndex][sendHost]
                    socks.sendto(data,(UDP_IP[thisIndex][sendHost],5000 + thisIndex))
                    if data=="end":
                        break
                    data, addr = socks.recvfrom(1024)
                    sockr.sendto(data,(UDP_IP[thisIndex][recieveHost],5000+thisIndex)) #forward data


                except socket.timeout:
                    break
