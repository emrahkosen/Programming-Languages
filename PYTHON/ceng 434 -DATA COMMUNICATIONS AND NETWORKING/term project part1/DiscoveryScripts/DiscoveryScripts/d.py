#!/usr/bin/python
import threading
import thread
import socket
from datetime import datetime
import time

rtt = [0,0,0,0,0,0,0,0]




def reciever(UDP_IP ,UDP_IP2 , UDP_PORT):
    global rtt
    UDP_PORTr = UDP_PORT*10 + 5
    totalTime = 0
    sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    sock.settimeout(10)
    data, addr = sock.recvfrom(1024)
    N = 0
    NN= 0
    if data == "ready":
        data, addr = sock.recvfrom(1024)
        N = int(data)
        for i in range(N):
            try:
                data =  str(float(round(time.time() * 1000)))
                sock.sendto( data , (UDP_IP2, UDP_PORTr))
                data, addr = sock.recvfrom(1024)
                data = float(round(time.time() * 1000)) - float(data)
                if data  > 0:
                    totalTime += data
                    NN=NN+1
            except socket.timeout:
                break
        if NN:
            totalTime =  totalTime/(NN)
        print totalTime
        if (UDP_IP == "10.10.4.2"):   #look up interface to decide which link is saved
            rtt[0] = totalTime
        elif(UDP_IP == "10.10.5.2"):
            rtt[1] = totalTime
        elif(UDP_IP == "10.10.7.1"):
            rtt[2] = totalTime

    else:
        print data
        if (UDP_PORT == 50021):   #look up ports to decide which link is saved
            rtt[3] = float(data)  #more info about this can be found in graph matrix
        elif(UDP_PORT == 50031):
            rtt[4] = float(data)
        elif(UDP_PORT == 5001):
            rtt[5] = float(data)
        elif(UDP_PORT == 5002):
            rtt[6] = float(data)
        elif(UDP_PORT == 5003):
            rtt[7] = float(data)
        else:
            True






UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ]


UDP_PORT =  5005
UDP_PORTs1 = 5001
UDP_PORTs2 = 5002
UDP_PORT12 = 50021
UDP_PORTs3 = 5003
UDP_PORT23 = 50031 #recieve rtt of r2-r3

#calculate rtt with d-r1,d-r2,d-r3
r1d = threading.Thread(target= reciever, args=(UDP_IP[1][4], UDP_IP[4][1] , UDP_PORT,))
r2d = threading.Thread(target= reciever, args=(UDP_IP[2][4], UDP_IP[4][2] , UDP_PORT,))
r3d = threading.Thread(target= reciever, args=( UDP_IP[3][4], UDP_IP[4][3] , UDP_PORT,))


r1d.start()
r2d.start()
r3d.start()

#recieve rtt from r1-r2-r3
sr1 = threading.Thread(target= reciever, args=(UDP_IP[1][4], UDP_IP[4][1] ,UDP_PORTs1,))
sr2 = threading.Thread(target= reciever, args=(UDP_IP[2][4], UDP_IP[4][2] , UDP_PORTs2,))
r12 = threading.Thread(target= reciever, args=(UDP_IP[2][4], UDP_IP[4][2] , UDP_PORT12,))
sr3 = threading.Thread(target= reciever, args=(UDP_IP[3][4], UDP_IP[4][3] , UDP_PORTs3,))
r23 = threading.Thread(target= reciever, args=(UDP_IP[3][4], UDP_IP[4][3] , UDP_PORT23,))


sr1.start()
sr2.start()
r12.start()
sr3.start()
r23.start()

r1d.join()
r2d.join()
r3d.join()
sr1.join()
sr2.join()
r12.join()
sr3.join()
r23.join()

print rtt

#putting round-trip times to matrix to access in dijkstra algorithm ex:graph[0][2] gives S-R2 linkcost
graph = [
        [0      ,rtt[5] ,rtt[6] ,rtt[7] ,0],
        [rtt[5] ,0      ,rtt[3] ,0      ,rtt[0]],
        [rtt[6] ,rtt[3] ,0      ,rtt[4] ,rtt[1]],
        [rtt[7] ,0      ,rtt[4] ,0      ,rtt[2]],
        [0      ,rtt[0] ,rtt[1] ,rtt[2] ,0]
        ]


def minDistance(dist , sptSet):
    min = 9999999999
    min_index = 0
    for i in range(5):
        if sptSet[i] == False and dist[i] <= min:
            min = dist[i]
            min_index = i
    print min_index
    return min_index




def dijkstra():
    global graph
    max = 99999999999
    dist = [0,max,max,max,max] #max distance at first, first found distance will replace it
    sptSet = [False,False,False,False,False] #False= best route not found
    parent = [-1,-1,-1,-1,-1]
    for i in range(5):
        u = minDistance(dist,sptSet)
        sptSet[u] = True
        for j in range(5):
            if sptSet[j] == False and graph[u][j] and dist[u] + graph[u][j] < dist[j]: #check if there is a route between and best route found. Also checks if found route is smaller than already existing.
                parent[j] = u
                dist[j] = dist[u] + graph[u][j]

    print dist
    print parent
    return parent
parent=dijkstra() # returns a parent tree about reaching D node, parent[nodeIndex] shows which host the said host need to go through in the route
route=[-1,-2,-2,-2,parent[4]] #route starts with D's parent rest is added if they are in the route. -2 means they are not in route

current= parent[4]
while (current!=-1):
    route[current] = parent[current]
    current = parent[current]

print route


data = ' '.join([str(x) for x in route])

f= open("routelist.txt","w+")
f.write(data)
f.close()

#sending routelist to ther nodes
sockr3 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sockr3.sendto(data , ("10.10.7.2", 10000))
sockr3.sendto(data , ("10.10.7.2", 10000))

sockr2 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sockr2.sendto(data , ("10.10.5.1", 10002))
sockr2.sendto(data , ("10.10.5.1", 10002))

sockr1 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sockr1.sendto(data , ("10.10.4.1", 10003))
sockr1.sendto(data , ("10.10.4.1", 10003))

#store linkcosts
f= open("linkcosts.txt","w+")
f.write("R1-D: "+str(rtt[0])+" R1-R2: "+str(rtt[3])+ " R1-S: "+str(rtt[5])+" R2-D: "+str(rtt[1])+" R2-R3: "+str(rtt[4])+" R2-S: " +str(rtt[6])+" R3-D: "+str(rtt[2])+" R3-S: "+str(rtt[7])+"\n")
f.close()
