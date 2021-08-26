#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int power(int x, int a);

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{   
    matrix *mat=(matrix*)malloc(sizeof(matrix));
    int **data=(int**)malloc(num_rows*sizeof(int*));
    
    for (int i=0; i < num_rows; i++) {
        data[i]=(int*)calloc(num_cols, sizeof(int));
    }
    
    mat->data=data;
    mat->num_cols=num_cols;
    mat->num_rows=num_rows;
    
    return mat;
}

void add_row(matrix *mat, int *row)
{
    mat->num_rows+=1;
    mat->data=(int**)realloc(mat->data,mat->num_rows*sizeof(int*));
    mat->data[mat->num_rows-1]=row;
}

void add_col(matrix *mat, int *col)
{
    mat->num_cols+=1;
    for (int i = 0; i < mat->num_rows; i++) {
        mat->data[i]=(int*)realloc(mat->data[i], mat->num_cols*sizeof(int));
        mat->data[i][mat->num_cols-1]=col[i];
    }
}

void increment(matrix *mat, int num)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx]+=num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx]*=num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx]/=num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx]=power(mat->data[row_idx][col_idx], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    for (int i = 0; i < mat->num_rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below

int power(int x, int a) {
    if (a==0) {
        return 1;
    } else if (a%2==0) {
        return power(x, a/2)*power(x, a/2);
    } else {
        return x*power(x, (a-1)/2)*power(x, (a-1)/2);
    }
}