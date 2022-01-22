#include<iostream>
#define ut32 unsigned int
#define delta 0x9E3779B9
void XTea_Encrypt(ut32* src, ut32* k) {
	ut32 sum = 0;
	ut32 v0 = src[0];
	ut32 v1 = src[1];
	for (int i = 0; i < 0x20; i++) {
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
		sum += delta;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
	}
	src[0] = v0;
	src[1] = v1;
}
void XTea_Decrypt(ut32* enc, ut32* k) {
	ut32 sum = delta*0x20;
	ut32 v0 = enc[0];
	ut32 v1 = enc[1];
	for (int i = 0; i < 0x20; i++) {
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
	}
	enc[0] = v0;
	enc[1] = v1;
}

void output(ut32* m, ut32 n) {
	for (int i = 0; i < n; i++)
		printf("0x%08x ", m[i]);
	printf("\n");
}

int main() {
	ut32 m[2] = {0x4c753175,0x686f6d65};
	ut32 k[4] = {1,2,3,4 };
	XTea_Encrypt(m, k);
	output(m, 2);
	XTea_Decrypt(m, k);
	output(m, 2);
	return 0;
}
