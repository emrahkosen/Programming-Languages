from socket import *
import struct
import time
import hashlib
import pickle
import threading
'''
#r3
recieve_s=('10.10.3.2',1300)
send_s=('10.10.3.1',1301)
recieve_d=('10.10.7.2',1302)
send_d=('10.10.7.1',1303)

'''

'''r1
recieve_s=('10.10.1.2',1100)
send_s=('10.10.1.1',1101)
recieve_d=('10.10.4.1',1102)
send_d=('10.10.4.2',1103)
'''

#r2
recieve_s=('10.10.2.1',10002)
send_s=('10.10.2.2',10002)
recieve_d=('10.10.5.1',10002)
send_d=('10.10.5.2',10002)


socks=socket(AF_INET, SOCK_DGRAM)
socks_check=socket(AF_INET, SOCK_DGRAM)
socksender=socket(AF_INET, SOCK_DGRAM)
sockd=socket(AF_INET, SOCK_DGRAM)
sockd_check=socket(AF_INET, SOCK_DGRAM)

def redirector(dest1,dest2,s,s2):
    s.bind(dest1)
    s.settimeout(20)
    while True:
        data=0
        data,addr = s.recvfrom(1000) #recieve the data send to destination
        s2.sendto(data,dest2)
		print dest2



#threads for redirection s and d
s_director = threading.Thread(target= redirector, args=(recieve_s,send_d,socks,socksender))
d_director = threading.Thread(target= redirector, args=(recieve_d,send_s,sockd,socksender))


s_director.start()
d_director.start()


s_director.join()
d_director.join()
