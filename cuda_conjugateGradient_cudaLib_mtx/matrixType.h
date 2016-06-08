// define matrix types

#include <stdlib.h>

//#ifdef __cplusplus
//extern "C" {
//#endif

#ifndef DATA_TYPE_H
#include "DataTypes.h"
#endif
	
void converter_coo2csr (cooType src, csrType * target, matInfo * mat_info);

void delete_csrType   (csrType mat);
void delete_cooType   (cooType mat);

//#ifdef __cplusples
//}
//#endif


