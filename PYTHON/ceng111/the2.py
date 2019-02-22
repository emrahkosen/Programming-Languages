idnum = raw_input()
def iswhat(x):
    if idnum[x] == '?':
        return '?'
    if idnum[x] == '-':
        return '-'
    return int(idnum[x])
 
student_id = []
 
student_id.append(iswhat(0))
student_id.append(iswhat(1))
student_id.append(iswhat(2))
student_id.append(iswhat(3))
student_id.append(iswhat(4))
student_id.append(iswhat(5))
 
student_id.append(iswhat(7))
 
 
 
location = 10
lastvalue = 0
length = len(student_id)
 
for i in range(0,length):
    if student_id[i] == '?':
        location = i
 
if location == 10:
        sum1 = student_id[0] + student_id[2] + student_id[4]
 
        e2 = 2*student_id[1]
        if e2 >= 10:
            temp = e2%10
            temp2 = (e2-temp)/10
            e2 = temp + temp2
 
        e4 = 2*student_id[3]
        if e4 >= 10:
            temp = e4%10
            temp2 = (e4-temp)/10       
            e4 = temp + temp2
         
        e6 = 2*student_id[5]    
        if e6 >= 10:
            temp = e6%10
            temp2 = (e6-temp)/10
            e6 = temp + temp2
 
        sum1 += e2 + e4 + e6
         
        sum2 = sum1 -(sum1/10)*10
 
        if sum2 == 0:
            lastvalue = 0
 
        elif sum2 != 0:
            lastvalue = 10 - sum2
 
         
 
        if student_id[6] == lastvalue:
            print ("VALID")
        if student_id[6] != lastvalue:
            print ("INVALID")
 
 
if location != 10:
    if location == 6:
        sum1 = student_id[0] + student_id[2] + student_id[4]
 
        e2 = 2*student_id[1]
        if e2 >= 10:
            temp = e2%10
            temp2 = (e2-temp)/10
            e2 = temp + temp2
 
        e4 = 2*student_id[3]
        if e4 >= 10:
            temp = e4%10
            temp2 = (e4-temp)/10       
            e4 = temp + temp2
         
        e6 = 2*student_id[5]    
        if e6 >= 10:
            temp = e6%10
            temp2 = (e6-temp)/10
            e6 = temp + temp2
 
        sum1 += e2 + e4 + e6
         
        sum2 = sum1 -(sum1/10)*10
 
        if sum2 == 0:
            lastvalue = 0
 
        elif sum2 != 0:
            lastvalue = 10 - sum2
 
        print str(student_id[0])+str(student_id[1])+str(student_id[2])+str(student_id[3])+str(student_id[4])+str(student_id[5])+ '-'+str(lastvalue) 
 
 
 
 
 
    odeven = location%2
    if odeven == 1: #  mean it is even number
        sum1 = student_id[0] + student_id[2] + student_id[4] + student_id[6]
        if location == 1: ###########
            e4 = 2*student_id[3]
            if e4 >= 10:
                temp = e4%10
                temp2 = (e4-temp)/10       
                e4 = temp + temp2
         
            e6 = 2*student_id[5]    
            if e6 >= 10:
                temp = e6%10
                temp2 = (e6-temp)/10
                e6 = temp + temp2
            sum1 += e4 + e6
             
            sum2 = sum1%10
            if sum2 == 0:
                e2 = 0
            if sum2 != 0:
                etemp = (10-sum2)
                eod = etemp%2
                if eod == 0:
                    e2 = etemp/2
                if eod ==1:
                    e2 = (10 + etemp -1)/2
 
            print str(student_id[0])+str(e2)+str(student_id[2])+str(student_id[3])+str(student_id[4])+str(student_id[5])+ '-'+str(student_id[6])
 
        if location == 3: ###########
            e2 = 2*student_id[1]
            if e2 >= 10:
                temp = e2%10
                temp2 = (e2-temp)/10       
                e2 = temp + temp2
         
            e6 = 2*student_id[5]    
            if e6 >= 10:
                temp = e6%10
                temp2 = (e6-temp)/10
                e6 = temp + temp2
            sum1 += e2 + e6
             
            sum2 = sum1%10
            if sum2 == 0:
                e4 = 0
            if sum2 != 0:
                etemp = (10-sum2)
                eod = etemp%2
                if eod == 0:
                    e4 = etemp/2
                if eod ==1:
                    e4 = (10 + etemp -1)/2 
            print str(student_id[0])+str(student_id[1])+str(student_id[2])+str(e4)+str(student_id[4])+str(student_id[5])+ '-'+str(student_id[6])    
 
        if location == 5:############
            e2 = 2*student_id[1]
            if e2 >= 10:
                temp = e2%10
                temp2 = (e2-temp)/10       
                e2 = temp + temp2
         
            e4 = 2*student_id[3]    
            if e4 >= 10:
                temp = e4%10
                temp2 = (e4-temp)/10
                e4 = temp + temp2
            sum1 += e2 + e4
             
            sum2 = sum1%10
            if sum2 == 0:
                e6 = 0
            if sum2 != 0:
                etemp = (10-sum2)
                eod = etemp%2
                if eod == 0:
                    e6 = etemp/2
                if eod ==1:
                    e6 = (10 + etemp -1)/2 
            print str(student_id[0])+str(student_id[1])+str(student_id[2])+str(student_id[3])+str(student_id[4])+str(e6)+ '-'+str(student_id[6])        
 
 
    if odeven == 0:
        e2 = 2*student_id[1]
        if e2 >= 10:
            temp = e2%10
            temp2 = (e2-temp)/10
            e2 = temp + temp2
 
        e4 = 2*student_id[3]
        if e4 >= 10:
            temp = e4%10
            temp2 = (e4-temp)/10       
            e4 = temp + temp2
         
        e6 = 2*student_id[5]    
        if e6 >= 10:
            temp = e6%10
            temp2 = (e6-temp)/10
            e6 = temp + temp2
 
        sum1 = e2 + e4 + e6 
 
        if location == 0:#######    
            sum1 += student_id[2] + student_id[4] + student_id[6]
            sum2 = sum1%10
            if sum2 == 0:
                e1 = 0
            if sum2 != 0:
                e1 = 10 - sum2
            print str(e1)+str(student_id[1])+str(student_id[2])+str(student_id[3])+str(student_id[4])+str(student_id[5])+ '-'+str(student_id[6])    
 
        if location == 2:######
            sum1 += student_id[0] + student_id[4] + student_id[6]
            sum2 = sum1%10
            if sum2 == 0:
                e3 = 0
            if sum2 != 0:
                e3 = 10 - sum2
            print str(student_id[0])+str(student_id[1])+str(e3)+str(student_id[3])+str(student_id[4])+str(student_id[5])+ '-'+str(student_id[6])    
        if location == 4:
            sum1 += student_id[0] + student_id[2] + student_id[6]
            sum2 = sum1%10
            if sum2 == 0:
                e5 = 0
            if sum2 != 0:
                e5 = 10 - sum2
            print str(student_id[0])+str(student_id[1])+str(student_id[2])+str(student_id[3])+str(e5)+str(student_id[5])+ '-'+str(student_id[6])    
 
