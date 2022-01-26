#include<stdio.h>
/*
关于base64: 本质上是64进制，明密文长度3:4，相比base58、base32和hex等编码更简短一点
可变:
	  base64编码表
	  base64的8变6的划分
	  base64中4字节的顺序  置换

*/
static char b64table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64encode(char* src);
void b64decode(char* enc);
int  find(char* table, char k);
char out[100];             //保存最后一次加密的结果

int  find(char* table, char k) {
	for (int i = 0; i < 64; i++) 
		if (table[i] == k)
			return i;
}
void b64encode(char* src) {

	int len=0,i=0;
	while (src[i]) {             //计算长度
		len += 1;
		i+=1;
	}

	int k = len % 3;
	int j = 0;
	for (i = 0; i < 3 * (len/3); i += 3) {
		out[j] = b64table[src[i] >> 2];
		out[j + 1] = b64table[((src[i] & 0x3) << 4) | (src[i + 1] >> 4)];
		out[j + 2] = b64table[((src[i + 1] & 0xf) << 2) | ((src[i + 2] & 0xc0) >> 6)];
		out[j + 3] = b64table[src[i + 2] & 0x3f];
		j += 4;
	}
	
	out[j]=b64table[src[i] >> 2];

	if (k == 1) {
		out[j + 1] = b64table[(src[i] & 0x3) << 4];
		out[j + 2] = '=';
		out[j + 3] = '=';
	}
	else if(k==2){
		out[j + 1] = b64table[((src[i] & 0x3) << 4) | (src[i + 1] >> 4)];
		out[j + 2] = b64table[((src[i + 1] & 0xf) << 2) ];
		out[j + 3] = '=';
	}
	else{
		out[j] = '\0';
	}
	out[j + 4] = '\0';
	printf("%s\n", out);
}
void b64decode(char* enc) {
	char out[100];                 
	int i = 0, len = 0;
	while (enc[i] != '=' && enc[i]!='\0' ) {
		len += 1;
		enc[i] = find(b64table, enc[i]);
		i += 1;
	}

	int j = 0;
	int k = len % 4;
	for (i = 0; i < 4*(len/4); i += 4) {                            //注意取位是在低六位
		out[j] = (enc[i]<<2) | ((enc[i+1]&0x30)>>4);
		out[j + 1] = ((enc[i + 1] & 0xf) << 4) | ((enc[i + 2] & 0x3c) >> 2);
		out[j + 2] = ((enc[i + 2] & 0x3) << 6) | enc[i + 3];
		j += 3;
	}
                                              //填充末尾,标识字符串结束 
	if (k == 3) {
		out[j] = (enc[i] << 2) | ((enc[i + 1] & 0x30) >> 4);
		out[j+1] = out[j + 1] = ((enc[i + 1] & 0xf) << 4) | ((enc[i + 2] & 0x3c) >> 2);
		out[j + 2] = '\0';
	}
	else if (k==2){
		out[j] = (enc[i] << 2) | ((enc[i + 1] & 0x30) >> 4);
		out[j + 1] = '\0';
	}
	else{
		out[j] = '\0';
	}
	printf("%s\n",out);
}
int main() {
	char m[] = "flag{wecome_to_play_with_Lu1u}";
	char enc[] = "ZmxhZ3t3ZWNvbWVfdG9fcGxheV93aXRoX0x1MXV9";
	b64encode(m);
	b64decode(enc);
	return 0;
}