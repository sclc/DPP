#include <stdio.h>

extern "C" {
    unsigned char reverseByte(unsigned char src);
    unsigned short reverseShort(unsigned short src);
    unsigned int reverseInt(unsigned int src);
}

int
main(void)
{
    unsigned char srcChar = 0xD5;
    unsigned short srcShort = 0xD53C;
    unsigned int srcInt = 0xD55B33CC;

    unsigned char rC = reverseByte(srcChar);
    printf("in=0x%02X, out=0x%02X\n", srcChar, rC);

    unsigned short rS = reverseShort(srcShort);
    printf("in=0x%04X, out=0x%04X\n", srcShort, rS);

    unsigned int rI = reverseInt(srcInt);
    printf("in=0x%08X, out=0x%08X\n", srcInt, rI);

    return 0;
}
