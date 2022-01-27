def Rc4_Encrypt(m,key):
    s=[]
    t=[]
    out=[] #putput
    for i in range(256):
        s.append(i)
        t.append(ord(key[i%len(key)]))

    j=0
    for i in range(256):
        j=(j+s[i]+t[i])%256
        s[i],s[j]=s[j],s[i]

    i,j=0,0
    for p in range(len(m)):
        i=(i+1)%256
        j=(j+s[i])%256

        s[i],s[j]=s[j],s[i]

        index=(s[i]+s[j])%256
        out.append(s[index]^m[p])
    print(bytes(out))

if __name__ == '__main__':
    key='123456'
    #m=b'helloworld'
    #[104, 157, 18, 11, 75, 68, 122, 238, 19, 83]
    Rc4_Encrypt(bytearray([104, 157, 18, 11, 75, 68, 122, 238, 19, 83]),key)
    pass
