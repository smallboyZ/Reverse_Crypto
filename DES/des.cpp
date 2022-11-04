#include<stdio.h>
//下标从1开始计数
const unsigned char ip[64] = {
     58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};
const unsigned char ip_inv[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};
const unsigned char ebox[48] = {
     32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};
//sbox
const static unsigned char sbox[8][64] = { {
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
         0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    },{
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
         3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
         0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    },{
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
         1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    },{
         7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
         3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
    },{
         2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
         4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    },{
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
         9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
         4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    },{
         4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
         1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
         6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    },{
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
         1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
         7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
         2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    } };

const unsigned  char pbox[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

const unsigned char pc1[56] = {
   57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

const unsigned char pc2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

 
const unsigned char r_shift[16] = { 1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1 };

void ip_shift(unsigned char* m,int flag=1) {
    unsigned char mbit[64];
    unsigned char tmp[64];
    int i, j;
    for( i=0;i<8;i++)
        for ( j = 0; j < 8; j++) {
            mbit[8 * i + j] = (m[i] >>  (7 - j)) & 1;
        }
    if (flag) {
        for ( i = 0; i < 64; i++) 
            tmp[i] = mbit[ip[i] - 1];
    }
    else {
        for ( i = 0; i < 64; i++)
             tmp[i] = mbit[ip_inv[i] - 1];
    }
    unsigned char t;
    for ( i = 0; i < 8; i++) {
        t = 0;
        for ( j = 0; j < 8; j++)
            t |= tmp[8 * i + j] << (7 - j);
        m[i] = t;
    }

}
void shift(unsigned char* m, unsigned char n) {
    unsigned t = 0;
    for (int i = 0; i < 28; i++) {
        t |= (m[i] << 27 - i);
    }
    t = ((t << n) & 0xfffffff | t >> (28 - n))&0xfffffff;

    for (int i = 0; i < 28; i++) {
        m[i] =( t >> (27 - i))&1;
    }
}
void des_exkey(unsigned char *key,unsigned char rk[][6]) {
    unsigned char mbit[64];
    unsigned char tmp[56];
    int i, j, r;
    for ( i = 0; i < 8; i++)
        for ( j = 0; j < 8; j++) {
            mbit[8 * i + j] = (key[i] >> (7 - j)) & 1;
        }
    for ( i = 0; i < 56; i++) {
        tmp[i] = mbit[pc1[i] - 1];
    }


    unsigned char n;
    unsigned char t;
    for ( r = 0; r < 16; r++) {
        n = r_shift[r];
        shift(tmp, n);
        shift(tmp + 28, n);
        for ( i = 0; i < 6; i++) {
            t = 0;
            for ( j = 0; j < 8; j++)
                t |= (tmp[pc2[8 * i + j] - 1]) << (7 - j);

            rk[r][i] = t;
        }
    }
}

unsigned int des_f(unsigned int x, unsigned char* roundk) {
    unsigned char mbit[48];
    unsigned char kbit[48];
    unsigned char p;
    int i,j;
    for ( i = 0; i < 48; i++) {          //e 扩展
        p = ebox[i]-1;
        mbit[i] = (x >> (31 - p)) & 1;
    }

    for( i=0;i<6;i++)
        for ( j = 0; j < 8; j++) {
            kbit[8 * i + j] = (roundk[i] >> (7 - j)) & 1;
        }
    unsigned char tmp[8];            // 轮秘钥
    for ( i = 0; i < 8; i++) {
        p = 0;
        for ( j = 0; j < 6; j++) {
            mbit[6 * i + j] ^= kbit[6 * i + j];
            p |= (mbit[6 * i + j] << (5 - j));
        }
        tmp[i] = p;
    }

    unsigned char a, b;                  //sbox
    for ( i = 0; i < 8; i++) {
        a = ((tmp[i] >> 4) & 2) | (tmp[i] & 1);
        b = (tmp[i] >> 1) & 0xf;
        tmp[i] = sbox[i][16 * a + b];
    }

    for( i=0;i<8;i++)                       //复用了
        for (j = 0; j < 4; j++) {
            mbit[4 * i + j] = (tmp[i] >> (3 - j))&1;
        }
    unsigned int ans=0;

    for (i = 0; i < 32; i++) {
        ans|= (mbit[pbox[i] - 1]<<(31-i));
    }

    return ans;
}
void des_encry(unsigned char* m,unsigned char rk[][6]) {
    int i;
    unsigned int tmp, left = 0, right = 0;
    ip_shift(m,1);
    for ( i = 0; i < 4; i++) {
        left |= m[i] << ((3 - i) * 8);
        right |= m[i + 4] << ((3 - i) * 8);
    }
    for (i = 0; i < 16; i++) {
        tmp = right;
        right = left ^ des_f(right, rk[i]);
        left = tmp;
    }
    tmp = left;    //最后一轮取消交换
    left = right;
    right = tmp;
  
    for ( i = 0; i < 4; i++) {
        m[i] = (left >> 8 * (3 - i)) & 0xff;
        m[i+4] = (right >> 8 * (3 - i)) & 0xff;
    }
    ip_shift(m, 0);
}
void des_decry(unsigned char* m, unsigned char rk[][6]) {
    ip_shift(m, 1);
    int i;
    unsigned int tmp, left = 0, right = 0;

    for (i = 0; i < 4; i++) {
        left |= m[i] << ((3 - i) * 8);
        right |= m[i + 4] << ((3 - i) * 8);
    }

    tmp = left;   
    left = right;
    right = tmp;

    for (i = 0; i < 16; i++) {
        tmp = left;
        left = right ^ des_f(left, rk[15 - i]);
        right = tmp;
    }

    for ( i = 0; i < 4; i++) {
        m[i] = (left >> 8 * (3 - i)) & 0xff;
        m[i + 4] = (right >> 8 * (3 - i)) & 0xff;
    }
    ip_shift(m, 0);

}
int main() {
    unsigned char mstr[9]="Lu1u.xyz";
    unsigned char key[9]="12345678";
    unsigned char rk[16][6];
    
    des_exkey(key,rk);
    des_encry(mstr, rk);

    for (int i = 0; i < 8; i++) {
        printf("%02x", mstr[i]);
    }
    printf("\n");

    des_decry(mstr, rk);

    for (int i = 0; i < 8; i++) {
        printf("%c", mstr[i]);
    }
    return 0;
}
