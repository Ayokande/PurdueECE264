#ifndef HUFFMAN_H
#define HUFFMAN_H



typedef struct _TreeNode {
    
    long int freq;
    int ASCII;
    struct _TreeNode * left;
    struct _TreeNode * right;
    
}TreeNode;

typedef struct _Node
{
    TreeNode * ptr;
    struct _Node * next;
    
}Node;

typedef struct _Bit
{
    int position;
    unsigned char byte;
    unsigned char rem;
    
}Bit;


Node *node_constructor(const void *ptr);
int comparison_fn(const void* arg1, const void* arg2);
Node* pq_enqueue(Node **pq, const void *new_object,
                 int (*cmp_fn)(const void *, const void *));
Node* pq_dequeue(Node **pq);
void destroy_node(Node *list, void (*destroy_fn)(void *));
void destroy_tree_node(void *root);
void read_from_file(FILE* fptr, long int* value, FILE* output1);
Node* huffman_tree(Node* pq);
void print_output(TreeNode* huffman, FILE* fp, int path, char* array);
void postorder_traverse_tree(TreeNode* node, FILE* fp);
void bit_traverse_tree(Bit* traverse ,unsigned char ch, FILE* fp);


#endif
