#ifndef DATA_TYPE_H
#define DATA_TYPE_H

//#ifdef __cplusplus
//extern "C" {
//#endif
typedef struct
{
	long num_rows;
	long num_cols;
	long nnz;
} matInfo;

typedef struct
{
	long num_rows, num_cols, nnz;
	long *row_start;
	long *col_idx;
	double *csrdata;

} csrType;

typedef struct
{
	long *rowIdx;
	long *colIdx;
	double *coodata;
} cooType;

//#ifdef __cplusples
//}
//#endif

#endif /*DATA_TYPE_H*/
