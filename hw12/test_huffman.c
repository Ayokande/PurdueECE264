#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static int int_cmp(const void* p1, const void* p2) {
    return *(const int*)p1 - *(const int*)p2;
}

static void int_print(const void* ptr) {
    printf("%d", *(const int*)ptr);
}

void destroy_node_func(void* list )
{
    
    free(list);
    
}

int main (int argc, char * argv[])
{
    Node * list = NULL;
    
    //int array[]= {202, 368, 364, 264, 207, 201, 362};
    
    /*8
    for(int index = 0; index < (sizeof(array)/sizeof(array[0])); index++)
    {
        pq_enqueue(&list, &array[index],int_cmp);
        
    }
    */
    //int array1[]= {1, 3, 5, 7, 9, 11, 13};
    
    /*
    for(int i = 0; i <sizeof(array)/sizeof(array1[0]);i++)
    {
        pq_enqueue(&list, &array[i],int_cmp);
        
    }
    */
    
    int a = 10;
    int b = 12;
    int c = 13;
    
    pq_enqueue(&list, &a, &int_cmp);
    pq_enqueue(&list, &b, &int_cmp);
    pq_enqueue(&list, &c, &int_cmp);
    print_node(list,int_print);
    Node * dequeue = pq_dequeue(&list);
    destroy_node(dequeue,destroy_node_func);
    print_node(list,int_print);
    int stacks = 7;
    stack_push(&list, &stacks);
    print_node(list,int_print);
    Node * pop = stack_pop(&list);
    destroy_node(pop,destroy_node_func);
    print_node(list,int_print);
    Node * last_node = remove_last_node(&list);
    destroy_node(last_node,destroy_node_func);
    print_node(list,int_print);
    destroy_node(list, destroy_node_func);
}
