// 
#include "matrixType.h"


void converter_coo2csr (cooType src, csrType * target, matInfo * mat_info)
{
    long idx, cumsum, last;
    
    target->num_rows = mat_info->num_rows;
    target->num_cols = mat_info->num_cols;
    target->nnz      = mat_info->nnz;
    
    target->row_start = (long *) calloc (target->num_rows + 1, sizeof(long) );
    target->col_idx   = (long *) calloc (target->nnz, sizeof (long));
    target->csrdata   = (double *) calloc (target->nnz, sizeof(double));
    
    for (idx = 0; idx < mat_info->num_rows; idx++)
        target->row_start[idx] = 0;

    for (idx = 0; idx < mat_info->nnz; idx++)
        target->row_start[src.rowIdx[idx]]++;


    //cumsum the nnz per row to get Bp[]
    for(idx = 0, cumsum = 0; idx < mat_info->num_rows; idx++){     
        long temp = target->row_start[idx];
        target->row_start[idx] = cumsum;
        cumsum += temp;
    }
    target->row_start[mat_info->num_rows] = mat_info->nnz;

    // final csr, in row section unsorted by column or essentially sorted for 
    // coo sorted by col
    for(idx = 0; idx < mat_info->nnz; idx++){
        long row  = src.rowIdx[idx];
        long dest = target->row_start[row];

        target->col_idx[dest] = src.colIdx [idx];
        target->csrdata[dest] = src.coodata[idx];
        // printf ("%lf\n", target->csrdata[dest]);

        target->row_start[row]++;
    }
    
    last = 0;
    // set back row_start values
    for( idx = 0; idx <= mat_info->num_rows; idx++){
        long temp = target->row_start[idx];
        target->row_start[idx]  = last;
        last   = temp;
    }
    
}

void delete_csrType  (csrType mat)
{
	free(mat.row_start);
	free(mat.col_idx);
	free(mat.csrdata);
}

void delete_cooType (cooType mat)
{
	free(mat.rowIdx) ;
	free(mat.colIdx) ;
	free(mat.coodata);
}
