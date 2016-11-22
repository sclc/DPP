#include <stdio.h>

extern "C" void asmCode(char *destination, char *source, size_t length);

int
main(void)
{
    char src[256] = "ABCdefGhijkLMoPgrStuVWxyZ12345", dst[256];

    asmCode(dst, src, sizeof(src));

    printf("%s\n%s\n", src, dst);

    return 0;
}
