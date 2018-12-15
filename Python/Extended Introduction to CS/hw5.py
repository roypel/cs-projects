#Skeleton file for HW5 - Fall 2017 - extended intro to CS

#Add your implementation to this file

#You may add other utility functions to this file,
#but you may NOT change the signature of the existing ones.

#Change the name of the file to your ID number (extension .py).


############
# QUESTION 1
############
class Binary():
    def __init__(self, s):
        """ represent a binary number as a string """
        assert type(s)==str
        assert s.count("0") + s.count("1") == len(s)
        self.s = s

    def __repr__(self):
        return "0b" + self.s

    def length(self):
        return len(self.s)

    def __eq__(self, other):
        return self.s == other.s

    def __lt__(self, other):
        """ operator < """
        assert isinstance(other, Binary)
        if self.length() < other.length():
            return True
        elif self.length() > other.length():
            return False
        b1 = str(self)
        b2 = str(other)
        for dig in range(2,len(b1)):
                if b1[dig] > b2[dig]:
                    return False
                if b1[dig] < b2[dig]:
                    return True
        return False
            

    def __add__(self, other):
        """ operator + """
        assert isinstance(other, Binary)
        if self.length() >= other.length():
            b1 = self.s[::-1]
            b2 = other.s[::-1]
        else:
            b1 = other.s[::-1]
            b2 = self.s[::-1]
        carry = "0"
        ans = ""
        for dig in range(len(b2)):
            if b1[dig] == "0" and b2[dig] == "0":
                ans += carry
                carry = "0"
            elif b1[dig] == "1" and b2[dig] == "1":
                ans += carry
                if carry == "0":
                    carry = "1"
            else:
                if carry == "0":
                    ans += "1"
                else:
                    ans += "0"
        for dig in range(len(b2), len(b1)):
            if b1[dig] == "1" and carry == "1":
                ans += "0"
            elif b1[dig] == "1" or carry == "1":
                ans += "1"
                carry = "0"
            else:
                ans += carry
        if carry == "1":
            ans += carry
        return Binary(ans[::-1])
                
        

    def is_power_of_two(self):
        """ True if self is a power of 2, else - False """
        for dig in self.s[1:]:
            if dig == "1":
                return False
        return True

    def largest_power_of_two(self):
        """ return the largest power of 2 which is <= self """
        return 2**(self.length()-1)

    def div3(self):
        """ Returns remainder of self divided by 3 """
        cnt = Binary("0")
        while cnt < self:
            cnt = cnt + Binary("11")
        div = 0
        if self + Binary("1") == cnt:
            div = 2
        if self + Binary("10") == cnt:
            div = 1
        return div

    def div3_new(self):
        """ Returns remainder of self divided by 3 """
        if self.s[0] == "1":
            div = 1
        else:
            div = 0
        for dig in self.s[1:]:
            if dig == "0":
                if div == 1:
                    div += 1
                elif div == 2:
                    div -= 1
            else:
                if div == 1:
                    div -= 1
                elif div == 0:
                    div += 1
            if div == -1:
                div = 2
            if div == 3:
                div = 0
        return div
    



############
# QUESTION 2
############

### Tree node class - code from lecture ###

class Tree_node():
    def __init__(self,key,val):
        self.key=key
        self.val=val
        self.left=None
        self.right=None
      
    def __repr__(self):
        return "[" + str(self.left) + \
               " (" + str(self.key) + "," + str(self.val) + ") " \
               + str(self.right) + "]"

### Binary search tree  ###
class BSearch_tree():
    def __init__(self):
        self.root = None

    def insert(self, key, val):
        def insert_Tree_Node(node, key, val):
            if node == None:
                return Tree_node(key,val)
            if node.key == key:
                node.val = val
            elif node.key > key:
                node.left = insert_Tree_Node(node.left, key, val)
            elif node.key < key:
                node.right = insert_Tree_Node(node.right, key, val)
            return node
            
        self.root = insert_Tree_Node(self.root, key, val)
            

    def lookup(self,key):
        def lookup_Tree_Node(node, key):
            if node == None:
                return None
            if node.key == key:
                return node.val
            if node.key > key:
                return lookup_Tree_Node(node.left, key)
            return lookup_Tree_Node(node.right, key)
        
        return lookup_Tree_Node(self.root, key)

    def sum(self):
        def sum_Tree_Node(node):
            if node == None:
                return 0
            return node.key + sum_Tree_Node(node.left) + sum_Tree_Node(node.right)

        return sum_Tree_Node(self.root)

    def find_closest_key(self, search_key):
        def find_closest_key_node(node, search_key, prev_key):
            if node == None:
                return prev_key
            if search_key == node.key:
                return node.key
            if search_key > node.key:
                right = find_closest_key_node(node.right, search_key, node.key)
                if abs(search_key-node.key) < abs(search_key-right):
                    return node.key
                return right
            left = find_closest_key_node(node.left, search_key, node.key)
            if abs(search_key-node.key) < abs(search_key-left):
                return node.key
            return left

        return find_closest_key_node(self.root, search_key, None)

    def is_balanced(self):
        def is_node_balanced(node):
            if node == None:
                return 0
            left = is_node_balanced(node.left)
            if left == -1:
                return left
            right = is_node_balanced(node.right)
            if right == -1:
                return right
            if abs(left-right) > 1:
                return -1
            return 1 + max(left,right)
        
        ans = is_node_balanced(self.root)
        if ans == -1:
            return False
        return True
        




############
# QUESTION 3
############

class Polynomial():
    def __init__(self, coeffs_lst):
        self.coeffs = coeffs_lst
        
    def __repr__(self):
        terms = [" + ("+str(self.coeffs[k])+"*x^" + \
                 str(k)+")" \
                 for k in range(len(self.coeffs)) \
                 if self.coeffs[k]!=0]
        terms = "".join(terms)
        if terms == "":
            return "0"
        else:
            return terms[3:] #discard leftmost '+'

    def degree(self):
        return len(self.coeffs)-1

    def evaluate(self, x):
        cnt = 1
        ans = 0
        for i in range(len(self.coeffs)):
            ans += self.coeffs[i] * cnt
            cnt *= x
        return ans

    def derivative(self):
        deriv = []
        for i in range(len(self.coeffs)-1):
            deriv.append(self.coeffs[i+1] * (i+1))
        return Polynomial(deriv)

    def __eq__(self, other):
        assert isinstance(other, Polynomial)  
        if len(self.coeffs) != len(other.coeffs):
            return False
        for i in range(len(self.coeffs)):
            if self.coeffs[i] != other.coeffs[i]:
                return False
        return True

    def __add__(self, other):
        assert isinstance(other, Polynomial)  
        len_self = len(self.coeffs)
        len_other = len(other.coeffs)
        add_pol = []
        cnt = 0
        for i in range(min(len_self, len_other)):
            add_pol.append(self.coeffs[i] + other.coeffs[i])
            cnt += 1
        if len_self > len_other:
            for i in range(cnt, len_self):
                add_pol.append(self.coeffs[i])
        else:
            for i in range(cnt, len_other):
                add_pol.append(other.coeffs[i])
        return Polynomial(add_pol)

    def __neg__(self):
        neg = []
        for i in range(len(self.coeffs)):
            neg.append(self.coeffs[i]*-1)
        return Polynomial(neg)

    def __sub__(self, other):
        assert isinstance(other, Polynomial)  
        return self + (-other)

    def __mul__(self, other):
        assert isinstance(other, Polynomial)  
        len_self = len(self.coeffs)
        len_other = len(other.coeffs)
        mul_pol = []#list(range(self.degree() * other.degree()))
        for i in range(len_self):
            for j in range(len_other):
                try:
                    mul_pol[i+j] += self.coeffs[i] * other.coeffs[j]
                except IndexError:
                    mul_pol.append(self.coeffs[i] * other.coeffs[j])
        return Polynomial(mul_pol)

    def find_root(self):
        return NR(lambda x: self.evaluate(x), lambda y: self.derivative().evaluate(y))


## code for Newton Raphson, needed in find_root ##
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




############
# QUESTION 4
############

# a

def suffix_prefix_overlap(lst, k):
    ans = []
    suff = ""
    for i in range(len(lst)):
        suff = lst[i][-k:]
        for j in range(len(lst)):
            if i != j:
                if lst[j][:k] == suff:
                    ans.append((i,j))
    return ans
        

# c
#########################################
### Dict class ###
#########################################

class Dict:
    def __init__(self, m, hash_func=hash):
        """ initial hash table, m empty entries """
        self.table = [ [] for i in range(m)]
        self.hash_mod = lambda x: hash_func(x) % m

    def __repr__(self):
        L = [self.table[i] for i in range(len(self.table))]
        return "".join([str(i) + " " + str(L[i]) + "\n" for i in range(len(self.table))])
              
    def insert(self, key, value):
        """ insert key,value into table
            Allow repetitions of keys """
        i = self.hash_mod(key) #hash on key only
        item = [key, value]    #pack into one item
        self.table[i].append(item) 

    def find(self, key):
        """ returns ALL values of key as a list, empty list if none """
        lst = []
        key_hash = self.hash_mod(key)
        [lst.append(item[1]) for item in self.table[key_hash]]
        return lst


#########################################
### End Dict class ###
#########################################    

# d
def suffix_prefix_overlap_hash1(lst, k):
    d = Dict(len(lst))
    ans = []
    for i in range(len(lst)):
        d.insert(lst[i][-k:], i)
    for j in range(len(lst)):
        pref = lst[j][:k]
        search = d.find(pref)
        for i in search:
            if i != j:
                if lst[i][-k:] == pref:
                    ans.append((i,j))
    return ans


# f
def suffix_prefix_overlap_hash2(lst, k):
    d = {}
    ans = []
    for i in range(len(lst)):
        suff = lst[i][-k:]
        if suff in d:
            d[suff].append(i)
        else:
            d[suff] = [i]
    for j in range(len(lst)):
        pref = lst[j][:k]
        if pref in d:
            tmp = d[pref]
            for i in range(len(tmp)):
                if tmp[i] != j:
                    ans.append((tmp[i],j))
    return ans





############
# QUESTION 6
############

# a
def next_row(row):
    tmp = 1
    for i in range(1, len(row)):
        row[i], tmp = tmp + row[i], row[i]
    row.append(1)
    return row

# b   
def generate_pascal():
    row = [1]
    while True:
        yield row
        row = next_row(row)

# c
def generate_bernoulli():
    row = [1]
    pascal = generate_pascal()
    next(pascal)
    while True:
        yield row
        row = [1]
        lst = next(pascal)
        add = 1
        for i in range(1, len(lst)):
            add += lst[i]
            row.append(add)
        



########
# Tester
########

def test():

    #Question 1
    
    a = Binary("101")
    b = Binary("10001")
    if (a < b) != True:
        print("error in Binary() class __lt__ function")
    if (a + b) != Binary("10110"):
        print("error in  Binary() class __add__ function") 
    c = Binary("10000")
    if a.is_power_of_two() != False or c.is_power_of_two() != True:
        print("error in Binary() class is_power_of_two function")
    if a.largest_power_of_two() != 4 or c.largest_power_of_two() != 16:
        print("error in Binary() class largest_power_of_two function")
    if a.div3() != 2 or b.div3() != 2:
        print("error in Binary() class div3 function")
    if a.div3_new() != 2 or b.div3_new() != 2:
        print("error in Binary() class div3_new function")

    #Question 2
    
    bin_tree = BSearch_tree() 
    bin_tree.insert(2,"hi")
    bin_tree.insert(4,"bye")
    bin_tree.insert(1,"hello")
    bin_tree.insert(3,"lovely")

    if (bin_tree.sum() != 10):
        print("error in BSearch_Tree")
    if (bin_tree.lookup(3) != "lovely"):
        print("error in BSearch_Tree")
    if (bin_tree.lookup(100) != None):
        print("error in BSearch_Tree")
    if (bin_tree.find_closest_key(5) != 4):
        print("error in BSearch_Tree")
    if (bin_tree.is_balanced() != True):
        print("error in BSearch_Tree 5")
    bin_tree.insert(5,"dear")
    if (bin_tree.is_balanced() != True):
        print("error in BSearch_Tree 6")
    bin_tree.insert(6,"tea")
    if (bin_tree.is_balanced() != False):
        print("error in BSearch_Tree 7")


    #Question 3
        
    q = Polynomial([0, 0, 0, 6])
    if str(q) != "(6*x^3)":
        print("error in Polynomial.__init__ or Polynomial.in __repr__")
    if q.degree() != 3:
        print("error in Polynomial.degree")
    p = Polynomial([3, -4, 1])
    if p.evaluate(10) != 63:
        print("error in Polynomial.evaluate")
    dp = p.derivative()
    ddp = p.derivative().derivative()
    if ddp.evaluate(100) != 2:
        print("error in Polynomial.derivative")
    if not p == Polynomial([3, -4, 1]) or p==q:
        print("error in Polynomial.__eq__")
    r = p+q
    if r.evaluate(1) != 6:
        print("error in Polynomial.__add__")
    if not (q == Polynomial([0, 0, 0, 5]) + Polynomial([0, 0, 0, 1])):
        print("error in Polynomial.__add__ or Polynomial.__eq__")
    if (-p).evaluate(-10) != -143:
        print("error in Polynomial.__neg__")
    if (p-q).evaluate(-1) != 14:
        print("error in Polynomial.__sub__")
    if (p*q).evaluate(2) != -48:
        print("error in Polynomial.__mult__")
    if (Polynomial([0])*p).evaluate(200) != 0:
        print("error in Polynomial class")
    root = p.find_root()
    if root-3 > 10**-7 and root-1 > 10**-7:
        print("error in Polynomial.find_root")

    #Question 4

    s0 = "a"*100
    s1 = "a"*60+"b"*40
    s2 = "a"*10+"b"*40+"c"*50
    lst = [s0,s1,s2]
    k=50
    if suffix_prefix_overlap(lst, k) != [(0, 1), (1, 2)]:
        print("error in suffix_prefix_overlap")
    if suffix_prefix_overlap_hash1(lst, k) != [(0, 1), (1, 2)]:
        print("error in suffix_prefix_overlap_hash1")
    if suffix_prefix_overlap_hash2(lst, k) != [(0, 1), (1, 2)]:
        print("error in suffix_prefix_overlap_hash2")

    #Question 6

    gp = generate_pascal()
    if gp == None:
        print("error in generate_pascal()")
    elif next(gp)!=[1] or next(gp)!=[1,1] or next(gp)!=[1,2,1]:
        print("error in generate_pascal()")
