#Skeleton file for HW3 - Fall 2017 - extended intro to CS

#Add your implementation to this file

#You may add other utility functions to this file,
#but you may NOT change the signature of the existing ones.

#Change the name of the file to include your ID number (hw3_ID.py).

############
# QUESTION 2
############

# a
def find_first_positive1(f):
    n = 1
    while(f(n) <= 0):
        n += 1
    return n

# b
def find_first_positive_range(f, a, b):
    result=None
    while (a <= b):
        mid = (b+a)//2
        if f(mid) > 0:
            result = (b+a)//2
            b = mid-1
        else:
            a = mid+1
    return result

# c
def find_first_positive2(f):
    n=1
    while f(n) <= 0:
        n *= 2
    return find_first_positive_range(f, n//2, n)


############
# QUESTION 3
############

# a
def find_maximum(blst):
    left = 0
    right = len(blst)-1
    mid = (left+right)//2
    while left < right:
        if blst[mid] > blst[mid-1]:
            if (blst[mid] > blst[mid+1]): #Check if we found the pivot
                return mid
            left = mid + 1
            mid = (left+right)//2
        else:
            right = mid - 1
            mid = (left+right)//2
    return mid

# b

def merge(A, B):
    ''' Merge list A of size n and list B of size m
        A and B must be sorted! '''
    n = len(A)
    m = len(B)
    C = [0 for i in range(n + m)]

    a=0; b=0; c=0
    while a<n and b<m: #more element in both A and B
        if A[a] < B[b]:
            C[c] = A[a]
            a+=1
        else:
            C[c] = B[b]
            b+=1
        c+=1

    if a==n: #A was completed
        while b<m:
            C[c] = B[b]
            b+=1
            c+=1
    else: #B was completed
        while a<n:
            C[c] = A[a]
            a+=1
            c+=1
    return C

def sort_bitonic_list(blst):
    mid = find_maximum(blst)+1
    return merge(blst[mid:],blst[:mid])



############
# QUESTION 5
############

def sort_pairs(lst):
    new_lst = []
    count = 0
    for i in range(100):
        tmp_lst = []
        for tup in lst:
            if i == tup[0]:
                tmp_lst.append(tup)
                count += 1
        if count>1: #Take care of all tuples with a1=a2
            for j in range(100):
                for tmp_tup in tmp_lst:
                    if j == tmp_tup[1]:
                        new_lst.append(tmp_tup)
            count=0
        else:
            new_lst.extend(tmp_lst)
    return new_lst
                


############
# QUESTION 6
############

from random import *
 
def diff_param(f,h=0.001):
    return (lambda x: (f(x+h)-f(x))/h)
 
 
def NR(func, deriv, epsilon=10**(-8), n=100, x0=None):
    if x0 is None:
        x0 = uniform(-100.,100.)
    x=x0; y=func(x)
    for i in range(n):
        if abs(y)<epsilon:
            #print (x,y,"convergence in",i, "iterations")
            return x
        elif abs(deriv(x))<epsilon:
            #print ("zero derivative, x0=",x0," i=",i, " xi=", x)
            return None
        else:
            #print(x,y)
            x = x- func(x)/deriv(x)
            y = func(x)
    #print("no convergence, x0=",x0," i=",i, " xi=", x)
    return None
 
# a
def equal(f1, f2):
    f3 = lambda x:f1(x)-f2(x)
    return (NR(f3,diff_param(f3)))

# c1
def source(f,y):
    func = lambda x: f(x)-y
    return NR(func, diff_param(func))
 
# c2
def inverse(f):
    return lambda x: source(f,x)


   
    
########
# Tester
########

def test():
    
    f1, f2 = lambda x : x - 8, lambda y : y - 5
    res1, res2 = find_first_positive1(f1), find_first_positive1(f2)
    if res1 == None or res2 == None or res1 != 9  or \
       res2 != 6:
        print("error in find_first_positive1")

    res1, res2 = find_first_positive_range(f1, 1, 9), find_first_positive_range(f1, 1, 3)
    if res1 == None or res1 != 9 or res2 != None:
        print("error in find_first_positive_range")

    res1, res2 = find_first_positive2(f1), find_first_positive2(f2)
    if res1 == None or res2 == None or res1 != 9  or \
       res2 != 6:
        print("error in find_first_positive2")

    if find_maximum([-3, 1, 2, 3, 80, 100, 6]) != 5 :
        print("error in find_maximum")

    if sort_bitonic_list([-3, 1, 2, 3, 80, 100, 6]) != [-3, 1, 2, 3, 6, 80, 100] :
        print("error in sort_bitonic_list")

    if sort_pairs([(9, 7), (78, 24), (9, 74), (53, 81), (40, 43), (79, 82), (84, 46), (68, 53), (92, 95), (60, 38), (20, 62), (72, 57)]) \
       != [(9, 7), (9, 74), (20, 62), (40, 43), (53, 81), (60, 38), (68, 53), (72, 57), (78, 24), (79, 82), (84, 46), (92, 95)]:
        print("error in sort_pairs")

    f1, f2 = lambda x:4*x+1, lambda x:-x+6
    if equal(f1,f2) == None or abs(equal(f1, f2) - 1) > 10**-7:
        print("error in equal")
    
    lin = lambda x: x+3
    if source(lin,5) == None or abs(source(lin,5) - 2.0000000003798846) > 10**-7:
        print("error in source")
 
    if inverse(lin) == None or abs(inverse(lin)(5) - 1.9999999998674198) > 10**-7:
        print("error in inverse")
   
