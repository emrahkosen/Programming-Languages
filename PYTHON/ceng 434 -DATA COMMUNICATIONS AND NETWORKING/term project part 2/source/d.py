import time
from socket import socket, AF_INET, SOCK_DGRAM, timeout
from sys import argv, stdout
from common import ip_checksum
import threading






lock = threading.Lock()
window = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
window_condition = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
# -1 means it is not get yet
# 1 means it is taken
update_Window_and_write_to_file_FLAG = False
numberofActive_Get_Packet = 2
half = 0


def send(content, to):
    checksum = ip_checksum(content)
    send_sock.sendto(checksum + content, to)


def Update_Window_and_write_to_file():
    global window
    global window_condition
    global update_Window_and_write_to_file_FLAG
    global numberofActive_Get_Packet
    global filename
    f = open(filename,'wb+')

    while True:

        #lock
        lock.acquire()
        if update_Window_and_write_to_file_FLAG == True:
            update_Window_and_write_to_file_FLAG = False
            window_condition = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
            for content in window:
                if content != -1:# normalde bu durum olmaz ama enson data gonderildi fakat windowdolmadi bu duruma karsi
                    f.write(content)
                else:
                    break
            window = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]


        if numberofActive_Get_Packet <= 0:
            lock.release()#unlock
            break
        lock.release()#unlock
    print "Update_Window_and_write_to_file is closing.."






#listen = (listen_addr, listen_port)
#dest = (dest_addr, dest_port)
def Get_Packet(dest, listen):
    global window
    global window_condition
    global update_Window_and_write_to_file_FLAG
    global numberofActive_Get_Packet
    global half

    send_sock = socket(AF_INET, SOCK_DGRAM)
    recv_sock = socket(AF_INET, SOCK_DGRAM)

    recv_sock.bind(listen)
    recv_sock.settimeout(20)
    while True:
        if sum(window_condition) != len(window_condition):
#            lock.acquire()#lock
            try:
                message, address = recv_sock.recvfrom(1000)
                message_list = message.split(' ', 2)

                checksum = message[:2]
                seq = int(message[2])
                content = message[3:]
                print "taken seq is " + str(seq)
                print "-----------------------"
                if ip_checksum(content) == checksum:
                    print window_condition

                    if window_condition[seq] == -1:  #implementing of window and pipelining taken packets displayed as 1 , waiting packets -1 on client
                        if ( half == 0 and seq < len(window)/2 ) or ( half == 1 and seq >= len(window)/2 ):
                            window_condition[seq] = 1 # seq th is taken
                            window[seq] = content
                            checksum = ip_checksum(str(seq))
                            print "sending seq is  " + str(seq)

                            send_sock.sendto(checksum + " " + str(seq), dest)
                            if half == 0 and sum(window_condition) == 0:
                                half = 1
                            if sum(window_condition) == len(window_condition):
                                update_Window_and_write_to_file_FLAG = True
                                half = 0
                        elif half == 0 and seq >= len(window)/2:
                            checksum = ip_checksum(str(seq))
                            send_sock.sendto(checksum + " " + str(seq), dest)
                            print "sending seq is " + str(seq)
                        else:
                            seq = -1
                            checksum = ip_checksum(str(seq))
                            send_sock.sendto(checksum + " " + str(seq), dest)
                            print "half error sending seq is  -1"
                    else:
                        checksum = ip_checksum(str(seq))
                        send_sock.sendto(checksum + " " + str(seq), dest)
                        print "sending seq is " + str(seq)



                else:
                    seq = -1
                    checksum = ip_checksum(str(seq))
                    send_sock.sendto(checksum + " " + str(seq), dest)
                    print "checksum error sending seq is  -1"
#                lock.release()#unlock

            except timeout:
                print "timeout"
#               lock.release()#unlock
                break


    numberofActive_Get_Packet -= 1
    if numberofActive_Get_Packet <= 0:
        update_Window_and_write_to_file_FLAG = True








UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ]


dest_port1 = 10001

listen1 = (UDP_IP[1][4],dest_port1)
dest1 = (UDP_IP[4][1],dest_port1)


dest_port3 = 10003

listen3 = (UDP_IP[3][4],dest_port3)
dest3 = (UDP_IP[4][3],dest_port3)


dest_port2 = 10002

listen2 = (UDP_IP[2][4],dest_port2)
dest2 = (UDP_IP[4][2],dest_port2)







if argv[1]=="2":
    numberofActive_Get_Packet = 2
    filename="output2.txt"
    r2write = threading.Thread(target = Update_Window_and_write_to_file  )
    r2write.start()

    r2recieve2 = threading.Thread(target = Get_Packet, args=(dest2, listen2, ))
    r2recieve2.start()
    r2recieve1 = threading.Thread(target = Get_Packet, args=(dest1, listen1, ))
    r2recieve1.start()
elif argv[1]=="1":
    numberofActive_Get_Packet = 1
    filename="output.txt"
    r2write = threading.Thread(target = Update_Window_and_write_to_file  )
    r2write.start()

    r2recieve3 = threading.Thread(target = Get_Packet, args=(dest3, listen3, ))
    r2recieve3.start()


r2write.join()
if argv[1]=="2":
    r2recieve2.join()
    r2recieve1.join()
elif argv[1]=="1":
    r2recieve3.join()

