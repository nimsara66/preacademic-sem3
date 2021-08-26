// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	node *cur=lst->head,*newNode;
    
    //initializing new node
    newNode=(node*)malloc(sizeof(node));
    newNode->word=word;
    
    //handle lst->head==NULL
    if (cur==NULL) {
        cur=newNode;
        cur->next=cur->prev=cur;
        return;
    }
    
    int count=0;
    
    //traveling to index
    //case1) positive index
    if (index>=0) {
        while (count<index) {
            count++;
            cur=cur->next;
        }
    }
    //case2) negative index
    else { 
        while (count>index) {
            count--;
            cur=cur->prev;
        }
    }
    
    //changing links
    newNode->prev=cur->prev;
    cur->prev->next=newNode;
    cur->prev=newNode;
    newNode->next=cur;
    
    //if added before head
    if (cur==lst->head) {
        lst->head=newNode;
    }
}

void insert_node_after(list *lst, int index, char *word)
{
	node *cur=lst->head,*newNode;
    
    //initializing new node
    newNode=(node*)malloc(sizeof(node));
    newNode->word=word;
    
    //handle lst->head==NULL
    if (cur==NULL) {
        cur=newNode;
        cur->next=cur->prev=cur;
        return;
    }
    
    int count=0;
    
    //travel to index
    //case1) positive index
    if (index>=0) {
        while (count<index) {
            count++;
            cur=cur->next;
        }
    }
    //case2) negative index
    if (index<0) {
        while (count>index) {
            count--;
            cur=cur->prev;
        }
    }
    
    //changing links
    newNode->prev=cur;
    newNode->next=cur->next;
    cur->next->prev=newNode;
    cur->next=newNode;
}

char *list_to_sentence(list *lst)
{
	char *sentence=(char*)malloc(256*sizeof(char));
    node *cur=lst->head;
    do {
        strcat(sentence, cur->word);
        if (cur->next!=NULL) {
            strcat(sentence, " ");
        }
        cur=cur->next;
    } while (cur!=lst->head);
    return sentence;
}

void delete_node(list *lst, int index)
{
	node *cur=lst->head;
    
    // boundry case1) head is null
    if (cur==NULL) {
        printf("Head is null.\n");
        return;
    }
    // boundry case2) last element in the list
    if (cur->next==cur) {
        lst->head=NULL;
		free(cur->word);
        free(cur);
        return;
    }
    
    int count=0;
    
    if (index>=0) {
        while (count<index) {
            count++;
            cur=cur->next;
        }
    }
    else {
        while (count>index) {
            count--;
            cur=cur->prev;
        }
    }
    
    cur->prev->next=cur->next;
    cur->next->prev=cur->prev;
        
    //if head is deleted
    if (cur==lst->head) {
        lst->head=cur->next;
    }
    free(cur->word);
    free(cur);
}

void delete_list(list *lst)
{
	while (lst->head!=NULL) {
        delete_node(lst, 0);
    }
}
