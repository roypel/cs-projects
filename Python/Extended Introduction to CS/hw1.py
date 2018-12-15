#Skeleton file for HW1 - Winter 2016 - extended intro to CS

#Add your implementation to this file

#you may NOT change the signature of the existing ones.

#Change the name of the file to include your ID number (hw1_ID.py).


#Question 3

in_file = "our_input.txt" #Text origin
out_file = "output.txt" #Output file

#Add the rest of your code here.
#Assume the file in_file exists in the same folder as the current file

origin=open(in_file)
des=open(out_file,'w')
last_line=origin.readline() #Using 1 line before the loop so we can catch the last line
for line in origin: #Goes through each line in the origin
    des.write(str(len(str.split(last_line)))+"\n") #Count the number of spaces in a line and write it in the new text file
    last_line=line
des.write(str(len(str.split(last_line)))) #Writing last line outside loop so there will be no '\n' in the end of file
des.close()
origin.close()







#**************************************************************
#Question 5
k = 9
n = 100
#Add the rest of your code here.

dig=str(k) #Store k as a string
for i in range(1,n+1): #Run from 1 to n inclusive
    if (i%k==0) and (dig in str(i)):
        print ("boom-boom!")
    elif (i%k==0) or (dig in str(i)):
        print("boom!")
    else:
        print(i)





#**************************************************************
#Question 6
num = int(input("Please enter a positive integer: "))
#Add the rest of your code here.
#It should handle any positive integer num
#at the end, the variables named 'length', 'start' and 'seq'
#should hold the answers and be printed below


length=0
start=-1
seq=None
m=0
s=""

for dig in str(num):#Check each digit in num
    if int(dig)%2==1:
        if m==0:
            m+=1
            s=dig
        else:
            m+=1
            s+=dig
    elif m!=0:
        if m>length:#If found a bigger sequence, save new data
            length=m
            seq=s
            start=str(num).find(seq)
        m=0
        s=""
if m>length:#If num has only odd numbers, data will be saved here
    length=m
    seq=s
    start=str(num).find(seq)

print("The maximal length is", length)
print("Sequence starts at", start)
print("Sequence is", seq)
