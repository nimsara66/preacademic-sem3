// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    delete_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
	node *newNode,*cur;
    FILE *fp = fopen("input.txt", "r");
    if (fp==NULL) {
        perror("Cannot open file\n");
        exit(1);
    }

    int fline=1;
    char line[256];
    int function, index;

    while (fgets(line, sizeof(line)-1, fp)!=NULL) {
        if (fline) {
            fline=0;
            char * pch;
            pch = strtok(line, ",");
            while (pch != NULL) {
                //creating and initializing node
                newNode=(node*)malloc(sizeof(node));
                char *word=(char*)malloc((MAX_WORD_LENGTH+1)*sizeof(char));
                strcpy(word, pch);
                word[strcspn(word, "\n")] = 0;
                newNode->word=word;

                //if no linked list exist
                if (lst->head==NULL) {
                lst->head=cur=newNode;
                cur->next=cur->prev=cur;
                } else {
                    while (cur->next!=lst->head) {
                        cur=cur->next;
                    }
                    newNode->prev=cur;
                    newNode->next=lst->head;
                    cur->next=newNode;
                    lst->head->prev=newNode;
                }
                pch = strtok (NULL, ",");
            }
        }
        else if (strcmp(line, "0")) {
            char *word=(char*)malloc((MAX_WORD_LENGTH+1)*sizeof(char));
            word[strcspn(word, "\n")] = 0;
            sscanf(line, "%d %d %s", &function, &index, word);
            if (function==INSERT_BEFORE) {
                insert_node_before(lst, index, word);
            } else if (function==INSERT_AFTER) {
                insert_node_after(lst, index, word);
            } else if (function==DELETE_NODE) {
                free(word);
                delete_node(lst, index);
            } else if (function==DELETE_LIST) {
                delete_list(lst);
            }
            // printf("%d %d %s, %p\n", function, index, word, word);
        }
    }

    fclose(fp);
}

//Print the list contents
void print_list(list * lst)
{
    char *sentence=list_to_sentence(lst);
    printf("%s\n", sentence);
    free(sentence);
}

