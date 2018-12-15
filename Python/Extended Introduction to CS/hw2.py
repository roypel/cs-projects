#Skeleton file for HW2 - Winter 2016-2017 - extended intro to CS

#Add your implementation to this file

#You may add other utility functions to this file,
#but you may NOT change the signature of the existing ones.

#Change the name of the file to hw2_<your ID number> (extension .py).

import time

############
# QUESTION 1
############

# 1c
def reverse_sublist(lst,start,end):
    end -= 1
    while (start < end):
        temp = lst[start]
        lst[start] = lst[end]
        lst[end] = temp
        start += 1
        end -= 1
    return None

# 1d
def divide_list(lst):
    pivot = lst[0]
    smaller = [small for small in lst if small < pivot]
    greater = [great for great in lst if great > pivot]
    return smaller + [pivot] + greater

# 1e
def divide_list_inplace(lst):
    pivot = lst[0]
    small_pos = 0
    great_pos = 0
    for i in range(len(lst)):#"Bubble down" all numbers smaller than pivot
        if lst[i] < pivot:
            temp = lst[small_pos]
            lst[small_pos] = lst[i]
            lst[i] = temp
            small_pos += 1
    reverse_sublist(lst, 0, len(lst))#Reverse list to bubble pivot to the middle
    for i in range(len(lst)):#"Bubble down" all numbers greater than pivot
        if lst[i] > pivot:
            temp = lst[great_pos]
            lst[great_pos] = lst[i]
            lst[i] = temp
            great_pos += 1
    reverse_sublist(lst, 0, len(lst))#Reverse back list
    return None


############
# QUESTION 2b
############

def power_new(a,b):
    """ computes a**b using iterated squaring """
    result = 1
    b_bin = bin(b)[2:]
    reverse_b_bin = b_bin[: :-1]
    for bit in reverse_b_bin: 
        if int(bit) % 2 == 1:
            result *= a        
        a *= a
    return result


############
# QUESTION 3b
############

def inc(binary):
    carry = "1"
    res = ""
    for dig in binary[::-1]: #Read the binary RtL
        if carry == "0":
            res += dig
        elif dig == "0":
            res += carry
            carry = "0"
        else:
            res += "0"
    if carry == "1":
        res += "1"
    return res[::-1]

############
# QUESTION 4b
############

# 4a
def sum_divisors(n):
    res = 0
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0 and i != n:
            res += i
            multi = n // i #Check multiplication of multi * i as another divisor of n
            if multi < n and multi != i:
                res += n // i
    return res

# 4b
def is_perfect(n):
    pass #replace this with your code

# 4c
def count_perfect_numbers(limit):
    pass #replace this with your code

#4d
def is_finite(n):
    new_sum = n
    sum_lst = []
    while True:
        sum_lst.append(new_sum)#Add sum to list to check later if inside a loop of sums
        new_sum = sum_divisors(new_sum)
        if new_sum == 0:#Check if found it's finite
             return True
        if new_sum in sum_lst:#Check if inside a loop of sums
            return False

#4e
def cnt_finite(limit):
    count=0
    for i in range(1,limit+1):
        count += is_finite(i)
    return count


############
# QUESTION 5
############

# 5a
def has_common(s1,s2,k):
    if len(s1)<k or len(s2)<k:
       return False
    something = []
    for i in range(len(s1)-k+1):
        something.append(s1[i:i+k])
    for i in range(len(something)):
        if something[i] in s2:	
            return True
    return False

def lcs_length_1(s1, s2):
    k=1
    while has_common(s1,s2,k) == True:
        k+=1
    return k-1

#5b
def lcs_length_2(s1, s2):
    if len(s1) == 0 or len(s2) == 0:
        return 0
    m = [[0]*len(s2) for i in range(len(s1))]
    for i in range(len(s1)):
        for j in range(len(s2)):
            if s1[i] != s2[j]:
                m[i][j] = 0
            else:
                if i > 0 and j > 0:
                    m[i][j] = m[i-1][j-1]+1
                else:
                    m[i][j] = 1
    
    return max([max(l) for l in m])

#5c
import random
def gen_str(n, alphabet):
    return "".join([random.choice(alphabet) for i in range(n)])

###Amir's code:
##n=4000
##alphabet = "abcdefghijklmnopqrstuvwxyz"
##print("two random strings of length", n)
##s1 = gen_str(n, alphabet)
##s2 = gen_str(n, alphabet)
##
##t0 = time.clock()
##res1 = lcs_length_1(s1,s2)
##t1 = time.clock()
##print("lcs_length_1", res1, t1-t0)
##
##t0 = time.clock()
##res2 = lcs_length_2(s1,s2)
##t1 = time.clock()
##print("lcs_length_2", res2, t1-t0)

###Michal's code
##n=4000
##alphabet = "abcdefghijklmnopqrstuvwxyz"
##print("two identical random strings of length", n)
##s1 = gen_str(n, alphabet)
##s2 = s1
##
##t0 = time.clock()
##res1 = lcs_length_1(s1,s2)
##t1 = time.clock()
##print("lcs_length_1", res1, t1-t0)
##
##t0 = time.clock()
##res2 = lcs_length_2(s1,s2)
##t1 = time.clock()
##print("lcs_length_2", res2, t1-t0)


########
# Tester
########

def test():
    
    lst = [1,2,3,4,5]
    reverse_sublist (lst,0,4)
    if lst != [4, 3, 2, 1, 5]:
        print("error in reverse_sublist()")        
    lst = ["a","b"]
    reverse_sublist (lst,0,1)
    if lst != ["a","b"]:
        print("error in reverse_sublist()")        

    lst = [1,2,3,4,5]
    lst_div = divide_list(lst)
    if lst_div == None:
        print("error in divide_list()")
    if lst_div != None and len(lst_div) != 5:
        print("error in divide_list()")
    if lst_div != None and lst_div[0] != 1:
        print("error in divide_list()")
    lst = [3,2,1,4,5]
    lst_div = divide_list(lst)
    if lst_div == None:
        print("error in divide_list()")
    
    if lst_div != None and \
       (lst_div[0] >= 3 or \
       lst_div[1] >= 3 or \
       lst_div[2] != 3 or \
       lst_div[3] <= 3 or \
       lst_div[4] <= 3):
        print("error in divide_list()")
    #verify that the original list did not change
    if lst[0] != 3 or \
       lst[1] != 2 or \
       lst[2] != 1 or \
       lst[3] != 4 or \
       lst[4] != 5:
        print("error in divide_list()")
    

    lst = [1,2,3,4,5]
    divide_list_inplace(lst)
    if lst[0] != 1:
        print("error in divide_list_inplace()")
    lst = [3,2,1,4,5]
    divide_list_inplace(lst)
    if lst[0] >= 3 or \
       lst[1] >= 3 or \
       lst[2] != 3 or \
       lst[3] <= 3 or \
       lst[4] <= 3:
        print("error in divide_list_inplace()")
    

    if power_new(2,3) != 8:
        print("error in power_new()")

    if inc("0") != "1" or \
       inc("1") != "10" or \
       inc("101") != "110" or \
       inc("111") != "1000" or \
       inc(inc("111")) != "1001":
        print("error in inc()")
    
    if sum_divisors(6)!=6 or \
       sum_divisors(4)!=3:        
        print("error in sum_divisors()")

    if is_finite(6) or \
       not is_finite(4):
        print("error in is_finite()")

    if cnt_finite(6) != 5:
        print("error in cnt_finite()")
        
    if has_common("ababc", "dbabca", 5) != False or \
       has_common("ababc", "dbabca", 4) != True or \
       has_common("ababc", "dbabca", 3) != True or \
       has_common("", "dbabca", 2) != False or \
       lcs_length_1("ababc", "dbabca") != 4:
        print("error in has_common()")
    
    if lcs_length_2("ababc", "dbabca") != 4 or \
       lcs_length_2("dbabca", "ababc") != 4 or \
       lcs_length_2("xxx", "ababc") != 0 :
        print("error in lcs_length_2()")



