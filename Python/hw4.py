#Skeleton file for HW4 - Spring 2015-2016 - Extended Intro to CS

#Add your implementation to this file

#You may add other utility functions to this file,
#but you may NOT change the signature of the existing ones.

#Change the name of the file to hw4_IDnumber (extension .py).

import random


############
# QUESTION 1
############

def max22(L, left, right):
    if left == right:
        return L[left]
    mid = (left + right)//2
    max_left = max22(L , left , mid)
    max_right = max22(L , mid+1 , right)
    return max(max_left, max_right)


def max_list22(L):
    return max22(L, 0, len(L)-1)


############
# QUESTION 2
############

def profit(value, size):
    if size <= 0:
        return 0
    m=0
    for i in range(size):
        m = max(m, value[i] + profit(value,size-i-1))
    return m


def profit2(value, size):
    d = {0:0}
    return profit_mem(value,size,d)
        

def profit_mem(value, size, d):
    if size not in d:
        m=0
        for i in range(size):
            m = max(m, value[i] + profit_mem(value, size-i-1, d))
        d[size]=m
    return d[size]


############
# QUESTION 3
############

# replace each "replace string with code" string with appropriate code
# do not modify the code's structure or change any of the existing code

def comp(s1,s2):
    if len(s1) == 0 and len(s2) == 0:
        return True
    if len(s1) == 0 or len(s2) == 0:
        return False
    if s1[0] != s2[0]:
        return False
    return comp(s1[1:], s2[1:])

def comp_ext(s1,s2):
    if len(s1) == 0 and len(s2) == 0:
        return True
    if len(s1) == 0 or len(s2) == 0:
        return False
    if s1[0] == "+":
        return comp_ext(s1[1:], s2[1:])
    if s1[0] == "*":
        return comp_ext(s1[1:], s2[1:]) or comp_ext (s1, s2[1:])
    if s1[0] != s2[0]:
        return False
    return comp_ext(s1[1:], s2[1:])



############
# QUESTION 5
############

#The first five lines of code are given and should not be changed
def choose_sets(lst, k):
    if k <= 0:
        return [[]]
    elif lst == []:    # k is non negative int
        return []
    else:
        res = choose_sets(lst[1:], k-1)
        for e in res:
            e.append(lst[0])
    return res + choose_sets(lst[1:],k)
            


############
# QUESTION 6
############

def naive(num_of_coins):
    """
    naive strategy:
    uniformly pick a non-empty pile
    uniformly pick the number of coins to remove
    """
    pile = random.randrange(len(num_of_coins))
    while (num_of_coins[pile] == 0):
        pile = random.randrange(len(num_of_coins))
    if num_of_coins[pile] == 1:
        num_of_coins[pile] = 0
    else:
        num_of_coins[pile] -= random.randrange(1, num_of_coins[pile]+1)
    
def compete(num_of_piles, init_num_of_coins, s1, s2):
    """
    simulates a single game
    """
    piles = []
    for i in range(num_of_piles):
        piles.append(init_num_of_coins)
    turn = random.randrange(0,2)
    while (max(piles) > 0):
        if turn == 0:
            s1(piles)
        else:
            s2(piles)
        turn = 1 - turn
    return 1 - turn
    
def compare(num_of_piles, init_num_of_coins, s1, s2, num_of_games):
    """
    compares strategies over multiple games
    """
    count1 = 0
    count2 = 0
    for i in range(num_of_games):
        if compete(num_of_piles, init_num_of_coins, s1, s2) == 0:
            count1 += 1
        else:
            count2 += 1
    return (count1, count2)
        
def silly(num_of_coins):
    """
    a silly strategy
    """
    big_pile = 0
    small_pile = 0
    while num_of_coins[small_pile] == 0:
        small_pile += 1
    for pile in range(len(num_of_coins)):
        if num_of_coins[big_pile] < num_of_coins[pile]:
            big_pile = pile
        if num_of_coins[small_pile] > num_of_coins[pile] and num_of_coins[pile] > 0:
            small_pile = 0
    if num_of_coins[big_pile] == 1:
        num_of_coins[big_pile] = 0
    else:
        if small_pile == big_pile:
            num_of_coins[big_pile] = 1
        else:
            if num_of_coins[small_pile] == 1:
                num_of_coins[big_pile] = 2
            else:
                num_of_coins[big_pile] = 0
            

    
def winning(num_of_coins):
    """
    winning strategy
    """
    
    assert sum(num_of_coins)!=0
    
    num_of_piles = len(num_of_coins)
    # get binary representations of bins heights
    binary_reps = [bin(e)[2:] for e in num_of_coins]
    # pad with zeros to achieve equal representation lengths
    maxlen = max([len(e) for e in binary_reps])
    binary_reps = ["0"*(maxlen-len(e))+e for e in binary_reps]
    # compute bitwise xor of pile heights
    xor_of_num_of_coins = "".join([str(sum([int(binary_reps[i][j]) for i in range(num_of_piles)])%2) 
                                    for j in range(maxlen)])
    
    # if bitwise XOR encodes for 0, resort to naive strategy
    if int(xor_of_num_of_coins, 2)==0:
        naive(num_of_coins)
        return
    
    # find index of most significant bit in xor_of_num_of_coins    
    mostsign = xor_of_num_of_coins.index("1")
    # find a pile whose binary representation includes "1" in this index
    pile = [i for i in range(num_of_piles) if binary_reps[i][mostsign]=="1"][0]
    # compute binary representation of the number of coins we should leave in this pile
    xor_of_coins_to_remain = [str((int(a)+int(b))%2) for a,b in zip(binary_reps[pile], xor_of_num_of_coins)]
    # convert to int, modify pile
    coins_to_remain = int("".join(xor_of_coins_to_remain), 2)
    num_of_coins[pile] = coins_to_remain

    assert all(e>=0 for e in num_of_coins), "number of coins turned negative"
    

########
# Tester
########

def test():

    # Q1 basic tests
    if max_list22([1,20,3]) != 20:
        print("error in max22()")
    if max_list22([1,20,300,400]) != 400:
        print("error in max22()")

    # Q2 basic tests
    if profit([1, 5, 8, 9], 4) != 10:
        print("error in profit()")
    if profit([2, 3, 7, 8, 9], 5) != 11:
        print("error in profit()")
    if profit2([1, 5, 8, 9], 4) != 10:
        print("error in profit2()")
    if profit2([2, 3, 7, 8, 9], 5) != 11:
        print("error in profit2()")
    
    
    # Q3 basic tests
    if comp("ab", "ab")!=True:
        print("error in comp()")
    if comp("", "")!=True:
        print("error in comp()")
    if comp("a", "ab")!=False:
        print("error in comp()")
    
    if comp_ext("ab", "ab")!=True:
        print("error in comp_ext()")
    if comp_ext("", "")!=True:
        print("error in comp_ext()")
    if comp_ext("a", "ab")!=False:
        print("error in comp_ext()")
    if comp_ext("+", "a")!=True:
        print("error in comp_ext()")
    if comp_ext("+", "")!=False:
        print("error in comp_ext()")
    if comp_ext("a+b", "axb")!=True:
        print("error in comp_ext()")
    if comp_ext("a+b", "axxb")!=False:
        print("error in comp_ext()")
    if comp_ext("a*xyz", "abcxyz")!=True:
        print("error in comp_ext()")
    if comp_ext("a*", "a")!=False:
        print("error in comp_ext()")
   
    # Q5 basic tests
    if choose_sets([1,2,3,4], 0) != [[]]:
        print("error in choose_sets()")
    tmp = choose_sets(['a','b','c','d','e'], 4)
    if tmp == None:
        print("error in choose_sets()")
    else:
        tmp = sorted([sorted(e) for e in tmp])
        if tmp != [['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'e'], ['a', 'b', 'd', 'e'], ['a', 'c', 'd', 'e'], ['b', 'c', 'd', 'e']]:
            print("error in choose_sets()")

