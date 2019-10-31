#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

//Right
Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))
{
    Node *new_node = malloc(sizeof(Node));
   // if (new_object == NULL || new_node == NULL)
   // {
     //   return NULL;
    //}
    Node* temp = *pq;
    Node* curr = NULL;
    new_node->ptr = (void*)new_object;
    new_node->next = NULL;
    while((cmp_fn(new_object, temp->ptr) > 0) && (temp != NULL))
    {
        curr = temp;
        temp = temp->next;
    }
    if(temp == *pq)
    {
        new_node->next = *pq;
        *pq = new_node;
        return new_node;
    }
    curr->next = new_node;
    new_node->next = temp;
    return new_node;
}

//Right
Node *pq_dequeue(Node **pq)
{
    if (*pq == NULL)
    {
        return NULL;
    }
    Node *ret_node = *pq;
    *pq = ret_node->next;
    ret_node->next = NULL;;
    return ret_node;
}

//Right
Node *stack_push(Node **stack, const void *new_object)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_object == NULL)
    {
        return NULL;
    }
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->ptr = (void*)new_object;
    new_node->next = *stack;
    *stack = new_node;
    return new_node;
}

//Right
Node *stack_pop(Node **stack)
{
    if (*stack == NULL)
    {
        return NULL;
    }
    Node *ret_node = *stack;
    *stack = ret_node->next;
    ret_node->next = NULL;
    return ret_node;
}

//Right
Node *remove_last_node(Node **list)
{
    if(*list == NULL)
    {
        return NULL;
    }
    Node *last_node = NULL;
    Node *curr_node = *list;
    while((curr_node->next) != NULL)
    {
        last_node = curr_node;
        curr_node = curr_node->next;
    }
    last_node->next = NULL;
    return curr_node;
}

//Right
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

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL)
   {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}

