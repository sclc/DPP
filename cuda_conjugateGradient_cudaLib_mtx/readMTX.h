#include <assert.h>


//#ifdef __cplusplus
//extern "C" {
//#endif

#ifndef DATA_TYPE_H
#include "DataTypes.h"
#endif

#include "common.h"
#include "mmio.h"

void readMtx_coo(char* path, char* name, cooType mtr, matInfo info);
void readMtx_info_and_coo(char* path, char* name, matInfo* info, cooType* mat);

//#ifdef __cplusples
//}
//#endif
