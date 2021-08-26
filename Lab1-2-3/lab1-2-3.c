// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);
matrix *copy_matrix(matrix *mat);

// output result
int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    //open input file
	FILE *fp = fopen("input.txt", "r");
    if (fp==NULL) {
        perror("Cannot open file\n");
        exit(1);
    }

    node *newNode,*cur;
    matrix *mat;
    int **data;
    int num_rows=0, num_cols=0;
    int lineNum=1;
    char line[256];
    int function;

    while (fgets(line, sizeof(line)-1, fp)!=NULL) {
        if (!strcmp(line, "0")) {
            //lastline --> "0"
            return;
        } else if (lineNum==1){
            //firstline --> num_rows
            sscanf(line, "%d", &num_rows);
        } else if (lineNum<=num_rows+1) {
            //initial matrix from line 2 to (1+num_rows)
            if (lineNum==2) {
                char temp[256];
                strcpy(temp, line);
                char *pch;
                pch = strtok(temp, " ");
                while (pch!=NULL) {
                    num_cols++; //calculate num_cols
                    pch = strtok (NULL, " ");
                }
                // create initial matrix
                mat=create_matrix(num_rows, num_cols);
                data=mat->data;
            }
            int val,j=0;
            char *pch;
            pch = strtok(line, " ");
            while (pch!=NULL) {
                sscanf(pch, "%d", &val);
                data[lineNum-2][j]=val;
                j++;
                pch = strtok (NULL, " ");
            }

            if (lineNum==num_rows+1) {
                //head node
                newNode=(node*)malloc(sizeof(node));
	            newNode->prev=newNode->next=NULL;
                newNode->mat=mat;
                chn->head=cur=newNode;
            }
        } else {
            char *pch;
            pch = strtok(line, " ");
            if (pch!=NULL) {
                sscanf(pch, "%d", &function);
            }

            //create newNode and link it to cur 
            mat=copy_matrix(cur->mat);
            newNode=(node*)malloc(sizeof(node));
	        newNode->next=NULL;
            newNode->mat=mat;
    	    newNode->prev=cur;
    	    cur->next=newNode;
    	    cur=cur->next;

            // various function
            pch = strtok (NULL, " ");
            if (function==2) { //add a row
                int num_cols=mat->num_cols;
                int *newRow=(int*)malloc(num_cols*sizeof(int));
                for (int k = 0; k < num_cols; k++) {
                    sscanf(pch, "%d", newRow+k);
                    // printf("%d\n", newRow[k]);
                    pch = strtok (NULL, " ");
                }
                add_row(mat, newRow);

            } else if (function==3) { //add a column
                int num_rows=mat->num_rows;
                int *newCol=(int*)malloc(num_rows*sizeof(int));
                for (int k = 0; k < num_rows; k++) {
                    sscanf(pch, "%d", newCol+k);
                    pch = strtok (NULL, " ");
                }
                add_col(mat, newCol);
                free(newCol); //col is seperately copied

            } else if (function==4) { //increment by value
                int val;
                sscanf(pch, "%d", &val);
                increment(mat, val);

            } else if (function==5) { //multiply by value
                int val;
                sscanf(pch, "%d", &val);
                scalar_multiply(mat, val);

            } else if (function==6) { //divide by value
                int val;
                sscanf(pch, "%d", &val);
                scalar_divide(mat, val);

            } else if (function==7) { //raise to value
                int val;
                sscanf(pch, "%d", &val);
                scalar_power(mat, val);

            }
            // printf("%d\n", function);
        }
        lineNum++;
    }
}

//Print the chain
void print_chain(chain * chn)
{
   node *cur=chn->head;
   while (cur!=NULL) {
       print_matrix(cur->mat);
       printf("\n");
       cur=cur->next;
   }

   delete_list(chn);
}

//Copy a matrix
matrix *copy_matrix(matrix *mat)
{
    matrix *newMat=create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            newMat->data[i][j]=mat->data[i][j];
        }
    }
    
    return newMat;
}

//Delete and free chain
void delete_list(chain *chn) {
    node *cur=chn->head,*temp;
    while (cur!=NULL) {
        temp=cur;
        cur=cur->next;
        delete_matrix(temp->mat);
        free(temp);
    }
}