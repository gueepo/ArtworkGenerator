#ifndef __IMAGE_H__
#define __IMAGE_H__

struct Image {
    int image_width;
    int image_height;
    int components_per_pixel;

    unsigned char* data;
};

typedef struct Image image_t;

image_t* Image_CreateImage(const char* path);
void Image_FreeImage(image_t* image);

#endif