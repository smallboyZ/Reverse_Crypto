## Blowfish加密

>Blowfish是一个对称加密的加密算法。两个int一组进行加密，即八个字节。
>
>加密流程分为: 秘钥扩展(Init)、加密算法

### 一、秘钥扩展

**秘钥扩展会借助秘钥对key修改Sbox和Pbox**

> PBOX记录的就是π后面的小数位。转换成16进制存储到pBox中

`Pbox`

```c
uint32_t P[18] = { 0x243F6A88L, 0x85A308D3L, 0x13198A2EL, 0x03707344L,
        0xA4093822L, 0x299F31D0L, 0x082EFA98L, 0xEC4E6C89L,
        0x452821E6L, 0x38D01377L, 0xBE5466CFL, 0x34E90C6CL,
        0xC0AC29B7L, 0xC97C50DDL, 0x3F84D5B5L, 0xB5470917L,
        0x9216D5D9L, 0x8979FB1BL };
```

`Sbox`

> Sbox由4组 256的int数组构成，字节数是4\*4\*256==4096(0x1000)

```c
uint32_t S[4][256]={{},{},{},{}} //数据过多 不方便展示
```

故也可以定义一个初始化的结构体

```c
struct blf_Init{
   uint32_t P[18];
   uint32_t S[4][256];
}
```

初始化的具体如下,两步变换P，之后变换Sbox

```c
void blowfish_init(const unsigned int* key, int key_len) {
	uint32_t k;
	for (short i = 0, p = 0; i < 18; i++)
	{
		k = key[i % key_len];
		P[i] ^= k;                         //pbox与key异或 这里只是key为int数组的情况，key也可以为任意字符串
	}


	uint32_t l = 0x00, r = 0x00;
	for (short i = 0; i < 18; i += 2)
	{
		blowfish_encrypt(&l, &r);
		P[i] = l;
		P[i + 1] = r;
	}

	for (short i = 0; i < 4; i++) 
	{
		for (short j = 0; j < 256; j += 2)
		{
			blowfish_encrypt(&l, &r); 
            S[i][j] = l;
			S[i][j + 1] = r;
		}
	}
}
```

如果key是一个字符串例如KEY="Lu1ukey";

> 采取一种循环的方式，当然也可以其他方法，是出题的魔改点之一。

```c
int d=0;
for(int i=0;i<18;i++){
    uint32_t k=0;
    for(int j=0;j<4;j++){
        k=(k<<8)|key[d];
        d+=1
        if(d>=keylen)
            d=0;
    }
    Pbox[i]^=k;
}
```

### 二、数据加密

> 加密是16轮循环的Feistel网络

加密的明文两个4字节一组进行加密,整体流程如下。

<img src="https://blog-1309321804.cos.ap-nanjing.myqcloud.com/blog/8lod0y2yzu.png" alt="8lod0y2yzu" style="zoom:50%;" />

`核心算法`

```c
void blowfish_encrypt(uint32_t* L, uint32_t* R) {
	for (int i = 0; i < 16; i++) {
		*L = *L ^ P[i];
		*R = f(*L) ^ *R;
		swap(L, R);
	}
	swap(L, R);  //取消最后一轮的交换
	*R = *R ^ P[16];
	*L = *L ^ P[17];
}
```

其中的`f函数`

```c
uint32_t f(uint32_t x){
    uint32_t tmp;
    tmp=S[0][x>>24] + S[1][(x>>16)&0xff];
    tmp^=S[2][(x>>8)&0xff];
    return tmp+S[3][x&0xff];
}
```

### 三、数据解密

可知加解密的数据初始化相同，且加密过程主要是异或和交换，解密即逆过程。

```c
void blowfish_decrypt(uint32_t* L, uint32_t* R) {
	*L ^= P[17];
	*R ^= P[16];
	swap(L, R);
	for (int i=15; i >= 0; i--) {
		swap(L, R);
		*R = f(*L) ^ *R;
		*L = *L ^ P[i];
	}
}
```

### 四、IDA分析

> 可以借助findcrypt插件辅助进行，如果blowfish中pbox和sbox值没有魔改，插件是可以快速识别的。

<img src="https://blog-1309321804.cos.ap-nanjing.myqcloud.com/blog/image-20220206215622368.png" alt="image-20220206215622368" style="zoom:80%;" />

`小插曲`

**pyd文件中函数的结构体，是函数名、函数地址、最后是结束标志。**

![image-20220206220919775](https://blog-1309321804.cos.ap-nanjing.myqcloud.com/blog/image-20220206220919775.png)

这里初步可以识别为用key修改pbox，aLetud指向的字符串是key，并且key的选取采用的上述实现的第二种方式。

```c
int d=0;
for(int i=0;i<18;i++){
    uint32_t k=0;
    for(int j=0;j<4;j++){
        k=(k<<8)|key[d];
        d+=1
        if(d>=keylen)
            d=0;
    }
    Pbox[i]^=k;
}
```

<img src="https://blog-1309321804.cos.ap-nanjing.myqcloud.com/blog/image-20220206221707393.png" alt="image-20220206221707393" style="zoom:80%;" />

接着就是用blowfish传入0,0来修改Pbox，循环16轮进行加密。

> 中间那一堆面目全非的是f函数,可以观察内存来识别。

```c
.data:0000000180005840 ; _DWORD Pk[18]
.data:0000000180005840 Pk              dd 12h dup(?)           ; DATA XREF: sub_180001DA0+43↑o
.data:0000000180005840                                         ; sub_180002230+16↑o ...
.data:0000000180005888 Sbox            db    ? ;               ; DATA XREF: sub_180001DA0+2B↑o
```

**pk+0x12即Pbox的全部内容，pk是一个_DWORD*,而pk+0x12即sbox\[0][0] ,pk + 0x112即 sbox\[1][0]依次类推，观察为f函数。**

```c
   v8[3] = Pk[17] ^ v25;
    v8[4] = result;
    v8 += 6;
  }
  while ( (__int64)v8 < (__int64)&unk_18000588C );
```

并且对Pbox的修改中一次循环 6个一组进行修改，退出条件是v8<18000588C ，而588C-5844(v8的地址是&pk[1])即0x48，故是处理PK。

> 综上，主要的特征都已经识别，其他部分也都类似，不过观察数据的结构可知，pk和sbox在一篇连续的空间，定义结构体会十会更加易读。

```c
struct blf_Init{
    _DWORD PK[18];
    _DWORD Sbox[4][256];
}
```

把原来定义pk处改为自己定义的结构体类型即可。

![image-20220206223145566](https://blog-1309321804.cos.ap-nanjing.myqcloud.com/blog/image-20220206223145566.png)

> 可见定义好后结构是多么明显

### 总结

blowfish的特点在于他依靠的Pbox和Sbox，并且加密流程类似festil,并且可能将Pbox和Sbox定义到一个结构体中，不过都需要占据大量的空间。

`魔改点`

Pbox、Sbox的内容、以及初始化key的用法、轮数等都有可能。

参考:

blowfish算法原理: https://cloud.tencent.com/developer/article/1836650

c实现代码: https://github.com/Rupan/blowfish/blob/master/blowfish.c