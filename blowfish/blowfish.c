#include<iostream>
#include"blowfish.h"

uint32_t f(uint32_t x) {
	uint32_t tmp;
	tmp = S[0][x >> 24] + S[1][(x >> 16) & 0xff];
	tmp ^= S[2][(x >> 8) & 0xff];
	return tmp + S[3][x & 0xff];
}
void swap(uint32_t* L, uint32_t* R) {
	uint32_t tmp;
	tmp = *L;
	*L = *R;
	*R = tmp;
}

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

void blowfish_init(uint8_t* key, uint32_t key_len) {
	//修改Pbox
	/*uint32_t k;
	for (short i = 0, p = 0; i < 18; i++)
	{
		k = key[i % key_len];       // 对于key是uint32 数组
		P[i] ^= k;
	}*/
	
	int d = 0;
	for (int i = 0; i < 18; i++) {
		uint32_t k = 0;
		for (int j = 0; j < 4; j++) {
			k = (k << 8) | key[d];
			d += 1;
			if (d >= key_len)
				d = 0;
		}
		P[i] ^= k;
	}


	uint32_t l = 0, r = 0;
	for (int i = 0; i < 18; i += 2)
	{
		blowfish_encrypt(&l, &r);
		P[i] = l;
		P[i + 1] = r;
	}



	for (int i = 0; i < 4; i++)  //修改Sbox
	{
		for (int j = 0; j < 256; j += 2)
		{
			blowfish_encrypt(&l, &r); S[i][j] = l;
			S[i][j + 1] = r;
		}
	}
}

int main() {
	uint32_t L = 0x12345678, R = 0x87654321;
	char key[8] = "Lu1ukey";
	blowfish_init((uint8_t*)key, 7);
	blowfish_encrypt(&L, &R);
	printf("enc res: 0x%x  0x%x\n", L, R);
	blowfish_decrypt(&L, &R);
	printf("dec res: 0x%x  0x%x\n", L, R);
	return 0;
}