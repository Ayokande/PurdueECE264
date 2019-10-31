#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <assert.h>
#include "bmp.h"
#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE 40

void _store_error_message(char* message, char** error);

void _store_error_message(char* message, char** error)
{
    if(*error == NULL)
    {
        *error = malloc((strlen(message) + 1) * sizeof(**error));
        strcpy(*error, message);
    }
    return;
    
}

BMPImage* read_bmp(FILE* fp, char** error)
{
    fseek(fp,0,SEEK_SET);
    if(fp == NULL)
    {
        _store_error_message("File does not exist!",error);
        return NULL;
    }
    BMPImage* image = malloc(sizeof(*image));
    image->data = NULL;
    
    if(image == NULL)
    {
        _store_error_message("Mallocing unsuccesful!",error);
        return NULL;
    }
    
    fseek(fp, 0L, SEEK_SET);
    int read1 = fread(&(image->header),sizeof(image->header),1,fp);
    if(read1 !=  1)
    {
        _store_error_message("Read unsuccesful!",error);
        free_bmp(image);
        return NULL;
    }
    
    bool validity = check_bmp_header(&(image->header),fp);
    if(validity == false)
    {
        _store_error_message("The files do not match!",error);
        free_bmp(image);
        return NULL;
    }
    
    image->data = malloc(sizeof(*(image->data)) * ((image->header).image_size_bytes));
    
    if((image->data) == NULL)
    {
        _store_error_message("Mallocing unsuccesful!",error);
        free(image);
        return NULL;
    }
    
    
    int read2 = fread((image->data),sizeof(*(image->data)),(image->header).image_size_bytes,fp);
    if (read2 != (image->header).image_size_bytes)
    {
        _store_error_message("Read unsuccesful!",error);
        free_bmp(image);
        return NULL;
        
    }
    return image;
}

bool check_bmp_header(BMPHeader* bmp_header, FILE* fp)
{
    fseek(fp,0L,SEEK_SET);
    if(bmp_header->type != 0x4d42)
    {
        return false;
    }
    
    if(bmp_header->offset != BMP_HEADER_SIZE)
    {
        return false;
    }
    
    if(bmp_header->dib_header_size != DIB_HEADER_SIZE)
    {
        return false;
    }
    
    if(bmp_header->num_planes != 1)
    {
        return false;
    }
    
    if(bmp_header->compression != 0)
    {
        return false;
    }
    
    if((bmp_header->num_colors != 0) || (bmp_header->important_colors != 0))
    {
        return false;
    }
    
    if(bmp_header->bits_per_pixel != 24)
    {
        return false;
    }
    
    int image_size = (bmp_header->height_px) * ((3 * (bmp_header->width_px)) + (bmp_header->width_px % 4));
    
    if((bmp_header->image_size_bytes != image_size) || (bmp_header->size != (image_size + BMP_HEADER_SIZE)))
    {
        return false;
    }
    
    fseek(fp,0,SEEK_END);
    int position = ftell(fp);
    
    if(position != bmp_header->size)
    {
        return false;
    }
    
    fseek(fp,54,SEEK_SET);
    
    return true;
}

bool write_bmp(FILE* fp, BMPImage* image, char** error)
{
    if(image == NULL)
    {
        _store_error_message("Mallocing unsuccesful!",error);
        return false;
    }
    
    if((fwrite(&(image->header),sizeof(image->header),1,fp)) != 1)
    {
        _store_error_message("Write unsuccesful!",error);
        return false;
    }
    
    if((fwrite((image->data),sizeof(*(image->data)),((image->header).image_size_bytes),fp)) != ((image->header).image_size_bytes))
    {
        _store_error_message("Write unsuccesful!",error);
        return false;
    }
    
    return true;
}

void free_bmp(BMPImage* image)
{
    if(image)
    {
        free(image->data);
        free(image);
    }
}


BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error)
{
    
    if(((x + w) > (image->header.width_px)) || ((y + h) > (image->header.height_px)))
    {
        _store_error_message("Invalid image dimensions!",error);
        return NULL;
    }
    
    
    if((x < 0) || (y < 0) || (w <= 0) || (h <= 0))
    {
        _store_error_message("Invalid image dimensions!",error);
        return NULL;
    }
    
    if(image == NULL)
    {
        _store_error_message("Invalid image!",error);
        return NULL;
    }
    
    BMPImage* cropped_image = malloc(sizeof(*cropped_image));
    if(cropped_image == NULL)
    {
        _store_error_message("Mallocing unsuccesful!",error);
        return NULL;
    }
    
    cropped_image->header = image->header;
    int cropped_image_size = h * ((3 * w) + (w % 4));
    
    (cropped_image->header).width_px = w;
    (cropped_image->header).height_px = h;
    (cropped_image->header).image_size_bytes = cropped_image_size;
    (cropped_image->header).size = cropped_image_size + BMP_HEADER_SIZE;
    
    //int new_w = (cropped_image->header).width_px;
    int new_h = (cropped_image->header).height_px;
    int new_image_size = (cropped_image->header).image_size_bytes;
    //int new_file_size = (cropped_image->header).size;
    int new_bytes_per_row = new_image_size / new_h;
    
    //int orig_w = (image->header).width_px;
    int orig_h = (image->header).height_px;
    int orig_image_size = (image->header).image_size_bytes;
    //int orig_file_size = (image->header).size;
    int orig_bytes_per_row =  orig_image_size / orig_h;
    
    cropped_image->data = calloc(((cropped_image->header).image_size_bytes), sizeof(*(cropped_image->data)));
    
    if((cropped_image->data) == NULL)
    {
        _store_error_message("Mallocing unsuccesful!",error);
        free(cropped_image);
        return NULL;
    }
    int crop_py = (h - 1) + y;
    int crop_dy = (orig_h - 1) - crop_py;
    int crop_dx = x;
    for(int i = 0; i < new_h; i++,crop_dy++)
    {
        int new_index = i * new_bytes_per_row;
        int old_index = crop_dy * orig_bytes_per_row + 3 * crop_dx;
        for(int j = 0; j < (3 * w);j++)
        {
            cropped_image->data[new_index + j] = image->data[old_index + j];
        }
    }
    
    return cropped_image;
}

