#include<iostream>
#include <cstring>
/*
关于base58: 相对于base64更加随和，58不是二的倍数，所以base58直接为58进制，无需考虑填充。
变换:    换表
*/
static char b58table[59] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

void b58encode(char* src);
void b58decode(char* enc);
int  find(char* table, char k) {
	for (int i = 0; i < 58; i++)
		if (table[i] == k)
			return i;
}

void b58encode(char* src) {
	int  i ,j,tmp;
	int len = 138 * strlen(src) / 100 + 1;                              

	uint8_t* enc = (uint8_t*)malloc(len * sizeof(uint8_t));  	 //以unsigned int8 来运算 char的范围 -128~127
	memset(enc, 0, len * sizeof(uint8_t));

	i = 0;
	while (i<strlen(src) ){
		tmp = src[i];
		for (j = len - 1; ; --j) {                                               //大端序 从低位修改进位改变enc的状态，做到大数进制转换。
			tmp +=enc[j]<<8;
			enc[j] = tmp % 58;
			tmp = tmp / 58;
			if (!j) break;                                               //见下面详解
		}

		int index = 0;                                                            //检测运算状态的代码
		while (!enc[index])
			index+=1;
		for (; index < len; index++) {
			printf("%u  ", enc[index]);
		}
		printf("\n");
		i += 1;
	}

	i = 0;
	while (!enc[i])
		i++;
	for (; i < len; i++) {
		printf("%c",b58table[enc[i]]);
	}
	printf("\n");
}

int main() {
	char m[] = "flag{welcom_to_play_with_Lu1u}";  //flag{welcom_to_play_with_Lu1u}
	char enc[] = "MXKxtLXrV7YyxXLQhKsLPC7o8HXv2ouwJuaXbabQx";
	b58encode(m);

	return 0;
}


/*          	              
while (i < strlen(src)) {
	tmp = src[i];
	for (j = len - 1; ; --j) {                                                               //不排除中间有tmp//0出现 但是整体没有算完的情况 故考虑不周
		tmp += enc[j] << 8;
		enc[j] = tmp % 58;
		tmp = tmp / 58;
		if (tmp == 0)                                                            // 要彻底更新状态
		break; 
	}
*/	


/*
print(ord('e'))
d=101
a=[51 ,0 ,12 ,53 ,41 ,21 ,34 ,23]
print((23*256+101)%58)
print((23*256+101)//58) # 103
print((34*256+103)%58)
print((34*256+103)//58) #151

print((21*256+151)%58)
print((21*256+151)//58) #95

print((41*256+95)%58)
print((41*256+95)//58) #182

print((53*256+182)%58)
print((53*256+182)//58) #237

print((12*256+237)%58)
print((12*256+237)//58) #57

print((0*256+57)%58)
print((0*256+57)//58)    #0            中间出现过tmp=0 但整体的状态并没有完全更新

print((51*256+0)%58)
print((51*256+0)//58) #225

print((0*256+225)%58)
print((0*256+225)//58) #225

*/