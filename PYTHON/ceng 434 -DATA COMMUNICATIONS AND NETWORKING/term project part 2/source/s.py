import time
from socket import socket, AF_INET, SOCK_DGRAM, timeout
from sys import argv, stdout
from common import ip_checksum
import threading





window = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
window_condition = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
# -1 means it is sent
# 0 means it is sending but not acked yet
# 1 means ready to send
window_size = 10
SEGMENT_SIZE = 980
sent_number_of_segment = 0
ofset = 0
updateWindow = True
is_Update_Window_ACTIVE = True
half = 0 #firs send first half than second half
lock = threading.Lock()




def Update_Window():
    filename = "input.txt"
    with open(filename) as f:
        content = f.read()
    global window
    global window_size
    global window_condition
    global SEGMENT_SIZE
    global sent_number_of_segment
    global ofset
    global updateWindow
    global is_Update_Window_ACTIVE

    while ofset < len(content):

        if updateWindow == True:
            lock.acquire()#lock
            print "window acquiring..."
            print "ofset = " + str(ofset)
            print "len(content) = " + str(len(content))
            if updateWindow == True:
                window = []
                window_condition = []
                updateWindow = False
                seq = 0
                print "window updating..."
                while True:
                    if ofset + SEGMENT_SIZE > len(content):
                        segment = content[ofset:]
                        window.append(ip_checksum(segment) + str(seq) +  segment)
                        window_condition.append(1)
                        ofset = len(content)
                        break
                    else:
                        segment = content[ofset: ofset + SEGMENT_SIZE]
                        ofset += SEGMENT_SIZE
                        window.append(ip_checksum(segment) +  str(seq) +  segment)
                        window_condition.append(1)
                        seq += 1
                        #print window_condition
                    if len(window) == window_size:
                        break
            time.sleep(0.01)
            print "window releasing..."
            lock.release()#unlock
    print "Update_Window is finishing..."
    is_Update_Window_ACTIVE = False

#listen = (listen_addr, listen_port)
#dest = (dest_addr, dest_port)
def Send_Packet(dest, listen):
    print  "Send_Packet is starting..."
    global window
    global window_condition
    global window_size
    global SEGMENT_SIZE
    global sent_number_of_segment
    global ofset
    global updateWindow
    global is_Update_Window_ACTIVE
    global half

    send_sock = socket(AF_INET, SOCK_DGRAM)
    recv_sock = socket(AF_INET, SOCK_DGRAM)

    recv_sock.bind(listen)
    recv_sock.settimeout(0.1)


    while True:
        lock.acquire()#lock
        print "try to find available packet..."
        seq = -1
        number_of_sent_packet = 0
        for i in range(len(window_condition)):
            if (half == 0 and i < window_size/2) or (half == 1 and i >= window_size/2):
                if window_condition[i] == 1:
                    seq = i
                    window_condition[i] = 0
                    break
            if window_condition[i] == -1:
                number_of_sent_packet += 1
        lock.release()#unlock

        print "seq no is " + str(seq)
        print window_condition
        print dest

        if number_of_sent_packet == len(window_condition): # if means all packet sent
            if is_Update_Window_ACTIVE == False:
                print "Send_Packet function closing due to is_Update_Window_ACTIVE == False"
                break
            updateWindow = True
            half = 0                        #set updateWindow as True
            time.sleep(0.01)


        while seq >= 0: # it get a packet than try to send
            send_sock.sendto(window[seq], dest)
            try:
                message, address = recv_sock.recvfrom(1000)
            except timeout:# if timeout set window_condition[seq] as ready to send from sending
                lock.acquire()#lock
                window_condition[seq] = 1
                print "timeout"
                lock.release()#unlock
                time.sleep(0.01)
                break
            else:
                message_list = message.split(' ')
                checksum = message_list[0]
                ack_seq = int(message_list[1])
                print "ack message ack is " + str(ack_seq)
                print "expected ack is " + str(seq)
                if ack_seq == seq:#checksum condition
                    window_condition[seq] = -1
                    if half == 0 and sum(window_condition[:window_size/2]) == -1*window_size/2:
                        half = 1
                    break
    print  "Send_Packet is ending..."


UDP_IP = [  [0          ,"10.10.1.2","10.10.2.1" ,"10.10.3.2" ,0],
            ["10.10.1.1",0          ,"10.10.8.2" ,0           ,"10.10.4.2"],
            ["10.10.2.2","10.10.8.1",0           ,"10.10.6.2" ,"10.10.5.2"],
            ["10.10.3.1",0          ,"10.10.6.1" ,0           ,"10.10.7.1"],
            [0          ,"10.10.4.1","10.10.5.1" ,"10.10.7.2" ,0]
         ]


dest_port1 = 10001
dest_port2 = 10002
dest_port3 = 10003

dest1 = (UDP_IP[0][1],dest_port1)
listen1 = (UDP_IP[1][0],dest_port1)

dest2 = (UDP_IP[0][2],dest_port2)
listen2 = (UDP_IP[2][0],dest_port2)
dest3 = (UDP_IP[0][3],dest_port3)
listen3 = (UDP_IP[3][0],dest_port3)

timing=float(round(time.time() * 1000))

r1read = threading.Thread(target = Update_Window  )
r1read.start()

if argv[1]=="2": # depending on the argument given, run threads for experiment 1 or 2
    send2r2 = threading.Thread(target = Send_Packet, args=(dest2, listen2, ))
    send2r2.start()

    send2r1 = threading.Thread(target = Send_Packet, args=(dest1, listen1, ))
    send2r1.start()

elif argv[1]=="1":
    send2r3 = threading.Thread(target = Send_Packet, args=(dest3, listen3, ))
    send2r3.start()



if argv[1]=="2":
    send2r2.join()
    send2r1.join()


elif argv[1]=="1":
    send2r3.join()


r1read.join()
timing=float(round(time.time() * 1000))-timing
print "operation took "+str(timing/1000.0) +" seconds"
