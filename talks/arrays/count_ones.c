#include <stdio.h>
#include <stdlib.h>

// for i in {0..6}; do echo "===== TEST $i ====="; time ./count_ones $i; echo ""; done

const unsigned int m1  = 0x55555555;
const unsigned int m2  = 0x33333333;
const unsigned int m4  = 0x0f0f0f0f;
const unsigned int m8  = 0x00ff00ff;
const unsigned int m16 = 0x0000ffff;
const unsigned int h01 = 0x01010101;

unsigned char bset[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 
    2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 
    2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 
    4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 
    2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 
    3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 
    4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 
    3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 
    4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 
    3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 
    5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 
    4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 
    2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 
    3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 
    4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 
    4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 
    4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 
    6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 
    3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 
    4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 
    5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 
    5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 
    6, 7, 6, 7, 7, 8
};

int c_ones0(unsigned int x)
{
    x = (x & m1 ) + ((x >>  1) & m1 );
    x = (x & m2 ) + ((x >>  2) & m2 );
    x = (x & m4 ) + ((x >>  4) & m4 );
    x = (x & m8 ) + ((x >>  8) & m8 );
    x = (x & m16) + ((x >> 16) & m16);
    return x;
}

int c_ones1(unsigned int x)
{
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    x += x >>  8;
    x += x >> 16;
    return x & 0x7f;
}

int c_ones2(unsigned int x)
{
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return (x * h01) >> 24;
}

int c_ones3(unsigned int x)
{
    int result = 0;

    while (x != 0) {
        if (x & 0x01)
            ++result;
        x >>= 1;
    }

    return result;
}

int c_ones4(unsigned int x)
{
    int result = 0;

    while (x != 0) {
        ++result;
        x &= x - 1;
    }

    return result;
}

int c_ones5(unsigned int x)
{
    return __builtin_popcount(x);
}

int c_ones6(unsigned int x)
{
    return bset[ x        & 0xFF] + bset[(x >>  8) & 0xFF]
         + bset[(x >> 16) & 0xFF] + bset[(x >> 24) & 0xFF];
}

typedef int (*Handler)(unsigned int x);
Handler jump_table[] = {
    c_ones0, c_ones1, c_ones2, c_ones3, c_ones4, c_ones5, c_ones6
};

int main(int argc, char *argv[])
{
    int n = 0;
    int i = 0;
    int f = atoi(argv[1]);

    for (i = 0; i < 100000000; ++i) {
        n = jump_table[f](0xFFFFFFFF);
        
        /*switch (i) {
        case 0:
            n = c_ones0(0xFFFFFFFF);
            break;
        case 1:
            n = c_ones1(0xFFFFFFFF);
            break;
        case 2:
            n = c_ones2(0xFFFFFFFF);
            break;
        case 3:
            n = c_ones3(0xFFFFFFFF);
            break;
        case 4:
            n = c_ones4(0xFFFFFFFF);
            break;
        case 5:
            n = c_ones5(0xFFFFFFFF);
            break;
        case 6:
            n = c_ones6(0xFFFFFFFF);
            break;
        } */
    }

    printf("n = %d\n", n);
    return 0;
}
