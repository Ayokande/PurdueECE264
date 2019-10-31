#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define SIZE 256
#include "huffman.h"


Node *node_constructor(const void *ptr)
{
    Node *node = malloc(sizeof(Node));
    if(node == NULL)
    {
        return NULL;
    }
    node->ptr = (void*)ptr;
    node->next = NULL;

    return node;
}

int comparison_fn(const void* arg1, const void* arg2)
{
    const TreeNode *var1 = (const TreeNode*) arg1;
    const TreeNode *var2 = (const TreeNode*) arg2;
    
    if(var1->freq > var2->freq)
    {
        
        return 1;
    }
    else return -1;
}


Node* pq_enqueue(Node **pq, const void *new_object,
                 int (*comp_fn )(const void *, const void *))
{
    Node *new_node = node_constructor((int*)new_object);
    if(new_node == NULL)
    {
        return NULL;
    }
    Node dummy;
    dummy.next = *pq;

    Node *prev = &dummy;
    Node *curr = *pq;

    while(curr != NULL)
    {
        if(comp_fn(curr->ptr, new_object) >= 0)
        {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    prev->next = new_node;
    new_node->next = curr;

    *pq = dummy.next;

    return new_node;
}


Node* pq_dequeue(Node **pq)
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

void destroy_tree_node(void *root)
{
    
    if (root == NULL)
    {
        return;

    }
    destroy_tree_node(((TreeNode *)root)->left);
    destroy_tree_node(((TreeNode *)root)->right);
    free(root);
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


Node* huffman_tree(Node* pq)
{
    if(pq == NULL)
    {
        return NULL;
    }
    
    while(pq->next != NULL)
    {
        Node* var1 = pq_dequeue(&pq);
        Node* var2 = pq_dequeue(&pq);
        TreeNode* huffman = malloc(sizeof(*huffman));
        huffman->freq = var1->ptr->freq + var2->ptr->freq;
        huffman->left = var1->ptr;
        huffman->right = var2->ptr;
        huffman->ASCII = -1;
        pq_enqueue(&pq,huffman,comparison_fn);
        
        free(var1);
        free(var2);
    }
    return pq;
}


void print_output(TreeNode* huffman, FILE* fp, int path, char* array)
{
    if(huffman->left == NULL)
    {
        fprintf(fp,"%c:",huffman->ASCII);
        for(int i = 0; i < path; i++)
        {
            fprintf(fp,"%c",array[i]);
        }
        
        fprintf(fp,"\n");
        return;
    }
    
    else
    {
        array[path] = '0';
        array[path + 1] = '\0';
        print_output(huffman->left,fp,path+1,array);
        array[path] = '1';
        array[path + 1] = '\0';
        print_output(huffman->right,fp,path+1,array);

    }
}

void postorder_traverse_tree(TreeNode* node, FILE* fp)
{
    
    if((node->left == NULL) || (node->right == NULL))
    {
        fprintf(fp,"1%c", node->ASCII);
    }
    else
    {
        postorder_traverse_tree(node->left, fp);
        postorder_traverse_tree(node->right, fp);
        fprintf(fp,"0");
    }
    
}


void bit_traverse_tree(Bit* traverse ,unsigned char ch, FILE* fp)
{
    if(ch == '1')
    {
        unsigned char size = 1;
        traverse->byte = traverse->byte | (size << (7 - traverse->position));
        traverse->position++;
        traverse->rem = 0;
    }
    else if(traverse->rem != 0)
    {
        traverse->byte = traverse->byte | traverse->rem;
        traverse->rem = 0;
    }
    else if(ch == '0')
    {
        traverse->position++;
        traverse->rem = 0;
    }
    else
    {
        for(int i = 0; i < 8; i++)
        {
            unsigned char size = ch >> (7 - i);
            traverse->byte = traverse->byte | (size << (7 - traverse->position));
            traverse->position++;
            if(traverse->position == 8)
            {
                fwrite(&(traverse->byte),sizeof(traverse->byte),1,fp);
                traverse->byte = 0;
                traverse->position = 0;
                for(int j = i + 1; j < 8; j++)
                {
                    size = ch >> (7 - j);
                    traverse->rem = traverse->rem | (size << (7 - (j - i -1)));
                    traverse->position++;
                }
                break;
            }
            traverse->rem = 0;
        }
    }
    
    if(traverse->position == 8)
    {
        fwrite(&(traverse->byte),sizeof(traverse->byte),1,fp);
        
    }
}

