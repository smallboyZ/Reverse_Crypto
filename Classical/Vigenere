class vigenere:
    """
    using math achieve.
    """
    def __init__(self):
        self.r='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    def encrypy(self,m:str,k:str)->str:
        out=''
        m=m.upper()
        k=k.upper().replace(' ','')
        l=len(k)
        p=0
        for i in range(len(m)) :
            tk=ord(k[p%l])-65
            if m[i] in self.r:
                out+=chr((ord(m[i])-65 + tk)%26 + 65)
                p+=1
            else:
                out+=m[i]

        return out

    def decrypt(self,enc:str,k:str)->str:
        out=''
        enc,k=enc.upper(),k.upper().replace(' ','')
        l=len(k)
        p=0
        for i in range(len(m)):
            tk=ord(k[p%l])-65
            if enc[i] in self.r:
                out+=chr(((ord(enc[i])-65 - tk)%26+26)%26 + 65)
                p+=1
            else:
                out+=m[i]
        return out

if __name__=="__main__":
    key='lulu'
    m='hello world'
    v=vigenere()
    ans=v.encrypy(m,key)
    print(ans)
    res=v.decrypt(ans,key)
    print(res)
