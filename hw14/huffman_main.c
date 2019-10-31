#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 256
#include "huffman.h"


int main(int argc, char* argv[])
{
    FILE* fptr = fopen(argv[1],"r");
    int value[SIZE] = {0};
    int ch = 0;
    while ((ch = fgetc(fptr)) != EOF)
    {
        value[ch]++;
    }
    fclose(fptr);
    Node* list =NULL;
    for(int i = 0; i < SIZE; i++)
    {
        
        if(value[i] > 0)
        {
            TreeNode* node = malloc(sizeof(*node));
            
            node->ASCII = i;
            node->freq = value[i];
            node->left = NULL;
            node->right = NULL;
            pq_enqueue(&list,node,comparison_fn);

        }

    }
    list = huffman_tree(list);
    FILE* outfptr = fopen(argv[2],"w");
    int path = 0;
    char* array = malloc(sizeof(*array)* SIZE);
    print_output(list->ptr,outfptr,path,array);
    free(array);
    fclose(outfptr);
    
    
    FILE* outfptr2 = fopen(argv[3],"w");
    postorder_traverse_tree(list->ptr,outfptr2);
    fprintf(outfptr2,"0");
    fclose(outfptr2);
    
    FILE* infptr3 = fopen(argv[3],"r");
    FILE* outfptr3 = fopen(argv[4],"w");

    Bit trav = {
    .position = 0,
    .byte = 0,
    .rem = 0
    };
        
    while(true)
    {
        unsigned char charac = fgetc(infptr3);
        if(feof(infptr3))
        {
            if(trav.position != 0)
            {
                fwrite(&(trav.byte),sizeof(trav.byte),1,outfptr3);
            }
            break;
        }
        else
        {
            bit_traverse_tree(&trav ,charac, outfptr3);
        }
    }
    
    
    fprintf(outfptr3,"0");
    fclose(outfptr3);
    fclose(infptr3);
    

    destroy_node(list,destroy_tree_node);
    
    

    return EXIT_SUCCESS;
}
