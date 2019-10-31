#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define SIZE 256
#include "huffman.h"


//Node *node_constructor(const void *ptr)
//{
//    Node *node = malloc(sizeof(Node));
//    if(node == NULL)
//    {
//        return NULL;
//    }
//    node->ptr = (void*)ptr;
//    node->next = NULL;
//    
//    return node;
//}
//
//Node *pq_enqueue(Node **pq, const void *new_object,
//                 int (*cmp_fn)(const void *, const void *))
//{
//    Node *new_node = node_constructor((int*)new_object);
//    if(new_node == NULL)
//    {
//        return NULL;
//    }
//    Node dummy;
//    dummy.next = *pq;
//    
//    Node *prev = &dummy;
//    Node *curr = *pq;
//    
//    while(curr != NULL)
//    {
//        if(cmp_fn(curr->ptr, new_object) >= 0)
//        {
//            break;
//        }
//        prev = curr;
//        curr = curr->next;
//    }
//    
//    prev->next = new_node;
//    new_node->next = curr;
//    
//    *pq = dummy.next;
//    
//    return new_node;
//}

void destroy_node(Node *list, void (*destroy_fn)(void *))
{
    Node* curr = list;
    while(curr != NULL)
    {
        Node* temp = curr->next;
        destroy_fn(curr->ptr);
        free(curr);
        curr = temp;
    }
    
    
    return;
}


void read_from_file(FILE* fptr, long int* value, FILE* output1)
{
    int ch = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        value[ch]++;
    }
    
    for(int index = 0; index < SIZE; index++)
    {
        fprintf(output1, "%ld\n", value[index]);
    }
}

int comp_fn(const void* arg1, const void* arg2)
{
    const TreeNode *var1 = (const TreeNode*) arg1;
    const TreeNode *var2 = (const TreeNode*) arg2;
    
    if(var1->freq > var2->freq)
    {
        
        return 1;
    }
    
    else if(var1->freq < var2->freq)
    {
        
        return -1;
    }
    
    if(var1->freq == var2->freq)
    {
        if((var1->ASCII == '\0') || (var2->ASCII == '\0'))
        {
            if((var1->right != NULL) && (var2->right == NULL))
            {
                return 1;
            }
            
            if((var1->right == NULL) && (var2->right != NULL))
            {
                return -1;
            }
            
            if((var1->right != NULL) && (var2->right != NULL))
            {
                return -1;
            }

        }
        if(var1->ASCII > var2->ASCII)
        {
            return 1;
        }
        
        else if(var1->ASCII < var2->ASCII)
        {
            return -1;
        }
    }
    return 1;
}

