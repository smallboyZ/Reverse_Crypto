#include<iostream>
#define ut32 unsigned int
#define delta 0x9e3779b9
using namespace std;
void XXTea_Encrypt(ut32* src, ut32 n, ut32* key); //m是明文数组 n是块个数 key是秘钥
void XXTea_Decrypt(ut32* enc, ut32 n, ut32* key);
void output(ut32* m, ut32 len);					  //打印函数

void XXTea_Encrypt(ut32* src, ut32 n, ut32* key) { /*对当前块的计算需要*/
	ut32 y, z, sum = 0;
	ut32 e, rounds;
	int p; // 定义为无符号时 p-1>=0这个判断恒成立
	rounds = 6 + 52 / n;
	z = src[n - 1];
	do {
		sum += delta;
		e = (sum >> 2) & 3;
		for (p = 0; p < n; p++) {
			y = src[(p + 1)%n];
			src[p] += (((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z)));
			z = src[p];
		}
	} while (--rounds);

}

void XXTea_Decrypt(ut32* enc, ut32 n, ut32* key) {
	ut32 y, z, sum;
	ut32 e, rounds;
	int p;
	rounds = 6 + 52 / n;
	sum = delta * rounds;

	do {
		e = (sum >> 2) & 3;

		for (p = n - 1; p >= 0; p--) {
			y = enc[(p + 1)%n];
			z = enc[(p - 1) % n]; //注意如果p是ut32 p-1不可能为负数
			enc[p] -= (((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z)));
		}
		sum -= delta;
	} while (--rounds);

}

void output(ut32* m, ut32 len) {
	for (int i = 0; i < len; i++)
		printf("0x%08x ", m[i]);
	printf("\n");
}

int main() {
	ut32 m[2] = { 0x4c753175 ,0x686f6d65 };
	ut32 k[4] = { 1,2,3,4 };
	XXTea_Encrypt(m, 2, k);  
	output(m, 2);
	XXTea_Decrypt(m, 2, k);
	output(m, 2);
	return 0;
}