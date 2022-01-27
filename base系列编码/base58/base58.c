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
	int  i = 0,j,tmp;
	int len = 138 * strlen(src) / 100 + 1;                // 8 / log2(58)

	uint8_t* enc = (uint8_t*)malloc(len * sizeof(uint8_t));   //以unsigned int8 来运算 char的范围 -128~127
	memset(enc, 0, len * sizeof(uint8_t));

	while (i<strlen(src) ){
		tmp = src[i];
		for (j = len - 1; ; j--) {         //大端序 从低位修改进位改变enc的状态，做到大数进制转换。
			tmp += 256 * enc[j];
			enc[j] = tmp % 58;
			tmp = tmp / 58;
			if (tmp == 0)
				break;
		}
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

void b58decode(char* enc) {
	int  i = 0, j, tmp;
	int len = 100 * strlen(enc) / 138 + 1;           

	for (int i = 0; i < strlen(enc); i++)
		enc[i] = find(b58table, enc[i]);

	uint8_t* m = (uint8_t*)malloc(len * sizeof(uint8_t));   //以unsigned int8 来运算 char的范围 -128~127
	memset(m, 0, len * sizeof(uint8_t));

	i = 0;
	while (i<strlen(enc)){
		int tmp = enc[i];
		for (j = len - 1; ; j-=1) {
			tmp += 58 * m[j];
			m[j] = tmp % 256;
			tmp = tmp / 256;
			if (tmp == 0)
				break;
		}
		i += 1;

/*		int index = 0;                          检测运算状态的代码
		while (!m[index])
			index+=1;
		for (; index < len; index++) {
			printf("%u  ", m[index]);
		}
		printf("\n");*/
	}

	i = 0;
	while (!m[i])
		i++;
	for (; i < len; i++) {
		printf("%c", m[i]);
	}

}

int main() {
	char m[] = "flag";  //flag{welcom_to_play_with_Lu1u}
	char enc[] = "3cr9Ae";
	b58encode(m);
	b58decode(enc);
	return 0;
}

