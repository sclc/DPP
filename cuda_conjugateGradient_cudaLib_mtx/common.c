#include "common.h"

// #ifndef ASSERTION_DEBUG
// #define ASSERTION_DEBUG
// #endif

char * concatStr(char * s1, char * s2) {
    char *resultStr = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(resultStr, s1);
    strcat(resultStr, s2);
    return resultStr;
}



