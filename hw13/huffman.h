#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct _Node
{
    void * ptr;
    struct _Node * next;
    
}Node;

typedef struct _TreeNode {
    
    long int freq;
    unsigned char ASCII;
    struct _TreeNode * left;
    struct _TreeNode * right;
    
}TreeNode;

void read_from_file(FILE* fptr, long int* value, FILE* output1);

#endif
