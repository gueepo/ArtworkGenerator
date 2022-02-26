#include "image.h"
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

image_t* Image_CreateImage(const char* path) {
    int image_width;
    int image_height;
    int components_per_pixel;

    image_t* newImage = (image_t*)malloc(sizeof(image_t));

    unsigned char* data = stbi_load(path, &image_width, &image_height, &components_per_pixel, 0);

    if(data == NULL) {
        printf("ERROR LOADING IMAGE! %s\n", path);
    }
    printf("loaded image %s, width: %d, height: %d, cpp: %d\n", path, image_width, image_height, components_per_pixel);

    newImage->image_width = image_width;
    newImage->image_height = image_height;
    newImage->components_per_pixel = components_per_pixel;
    newImage->data = data;

    return newImage;
}

void Image_FreeImage(image_t* image) {
    stbi_image_free(image->data);
    free(image);
}
