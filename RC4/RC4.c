#include<iostream>
uint8_t s[256];
uint8_t t[256];

void swap(uint8_t* a, uint8_t* b) {
	uint8_t tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Rc4_Init(uint8_t* key,uint32_t klen) {
	int i, j;
	for (i = 0; i < 256; i++) {
		s[i] = i;
		t[i] = key[i % klen];
	}
	j = 0;
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + t[i]) % 256;
		swap(&s[i], &s[j]);
	}
}

void Rc4_Encrypt(uint8_t* m, uint32_t mlen) {
	uint32_t k,i = 0, j = 0,p=0;
	while (p < mlen) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		swap(&s[i], &s[j]);
		k = s[(s[i] + s[j]) % 256];
		m[p] ^= k;
		p++;
	}
}

int main() {
	char key[7] = "123456";
	//char m[11] = "helloworld";
	uint8_t m[10] = { 104, 157, 18, 11, 75, 68, 122, 238, 19, 83 };
	Rc4_Init((uint8_t*)key, 6);
	Rc4_Encrypt((uint8_t*)m, 10);
	
	return  0;
}
