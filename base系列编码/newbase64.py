"""
a=0x666c61677b7765636f6d655f746f5f706c61795f776974685f4c7531757d
table='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
m=[]
while a!=0:
    m.append(a%64)
    a=a//64
m=m[::-1]
print(''.join([table[i] for i in m]))
# 64进制转换得来的密文  在无需补位时一致   怎么做到和base64加密统一呢？
# 一个16进制是4个bit 那么只需6个即可
"""

table='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
from Crypto.Util.number import *
def check(a):
    a=hex(a).replace('0x','')
    pad=0
    while len(a)%6!=0:
        a+='00'
        pad+=1
    return pad,int(a,16)

def newb64encode(src):
    a=bytes_to_long(src)
    m=[]
    padd,a=check(a)
    #print(hex(a))
    while a!=0:
        m.append(a%64)
        a=a//64
    m=m[::-1]
    s=''.join([table[i] for i in m])
    if padd!=0:
        print(s[:-padd]+'='*padd)
    else:
        print(s)

if __name__ == '__main__':
    a=b'flag{wecome_to_play_with_Lu1u}'
    b=b'a'
    c=b'lovey'
    newb64encode(a)
    newb64encode(b)
    newb64encode(c)
