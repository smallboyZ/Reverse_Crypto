import numpy as np
import sympy as sp

class hill:
    def __init__(self,size:int,key:str):
        self.n=size
        self.k=key.upper().replace(' ','')
        for i in range(size**2 - len(key)):
            self.k+=chr(i+65)
        self.mk=sp.Matrix([ [ord(j)-65 for j in self.k[size*i:size*i+size] ]for i in range(size)])
        self.Amk=self.mk.adjugate()
        self.A = self.mk.det()%26
        self.inv=0
        try:
            self.inv=(self.Amk*sp.invert(self.A,26))%26
        except:
            print('Key no inv')

    def encryt(self,mstr:str):
        n=self.n
        mstr=mstr.upper().replace(' ','')
        m=[]
        for i in range(len(mstr)//n):
            t=[]
            for j in range(n):
               t.append([ord(mstr[i*n+j])-65]) #列向量
            m.append(t)
        ans=[]
        for block in m:
           d=sp.Matrix(block)
           ans.extend(list((self.mk*d)%26))

        return ''.join([chr(i+65) for i in ans])

    def decrypt(self,menc:str):
        if self.inv==0:
            print("Key no inv")
            return None
        n = self.n
        menc=menc.upper().replace(' ','')
        c = []
        for i in range(len(menc) // n):
            t = []
            for j in range(n):
                t.append(ord(menc[i * n + j]) - 65)
            c.append(t)
        ans = []

        for block in c:
            d = sp.Matrix(block)
            ans.extend(list((self.inv * d) % 26))

        return ''.join([chr(i + 65) for i in ans])

def hill_boom_key(mstr:str,menc:str,n:int):
    """
    need m c and block_size
    """
    menc=menc.upper().replace(' ','')
    mstr=mstr.upper().replace(' ','')
    c=[]
    for i in menc:
       c.append([ord(i)-65])
    c=sp.Matrix(c)
    l=len(menc)
    if l<n**2:
        print("I need more m and c")
        return None
    tmp=[]
    for i in range(len(mstr)//n):
        t=[ord(j)-65 for j in mstr[n*i:n*i+n]]
        t.extend([0] * (n ** 2 - n))
        tmp.append(t)
    Am=[]
    for i in range(n*n):
        tm=tmp[i//n]
        Am.append(tm[(i%n)*n:]+tm[:(i%n)*n]) #通过数学推出左侧的系数矩阵 m * k = c
    Am=sp.Matrix(Am)
    A=Am.det() %26
    if A==0:
        print('No inv,I need other m and c')
        return None
    Aml=Am.adjugate()
    A_ = sp.invert(A,26)
    inv=(Aml*A_)%26
    ans = list((inv*c)%26)
    return ''.join([chr(i + 65) for i in ans])

h=hill(3,'GYBNQKURP')
enc=h.encryt('CAT')
print(enc)
ans=h.decrypt(enc)
print(ans)
ans=hill_boom_key('utfl','wznq',2)
print(ans)
h=hill(2,"BWLN")
a=h.decrypt("wznqca")
print(a)
