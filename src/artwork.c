#include <stdio.h>
#include "color.h"
#include "string.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

// default color => (215, 123, 186)
int main(void) {
    // loading the image
    int image_width;
    int image_height;
    int components_per_pixel;
    int total_size = 0;

    unsigned char* data = stbi_load("base/background.png", &image_width, &image_height, &components_per_pixel, 0);
    color_t colors[10];
    Color_FillColor(&colors[0], 255,   0,   0, 255);
    Color_FillColor(&colors[1],   0, 255,   0, 255);
    Color_FillColor(&colors[2], 255, 255,   0, 255);
    Color_FillColor(&colors[3], 255,   0, 255, 255);
    Color_FillColor(&colors[4],   0, 255, 255, 255);
    Color_FillColor(&colors[5], 255, 255, 255, 255);
    Color_FillColor(&colors[6], 100, 100, 100, 255);
    Color_FillColor(&colors[7],   0, 100, 100, 255);
    Color_FillColor(&colors[8], 100,   0, 100, 255);
    Color_FillColor(&colors[9], 100, 100,   0, 255);

    if(data == NULL) {
        printf("ERROR LOADING IMAGE!\n");
        return 1;
    }

    total_size = image_width * image_height * components_per_pixel;
    unsigned char* save_data = (unsigned char*)malloc(sizeof(unsigned char) * total_size);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < total_size; j += 4) {
            int r = (int)data[j];
            int g = (int)data[j+1];
            int b = (int)data[j+2];
            int a = (int)data[j+3];

            if(r == 215 && g == 123 && b == 186 && a == 255) {
                save_data[j] = colors[i].r;
                save_data[j+1] = colors[i].g;
                save_data[j+2] = colors[i].b;
                save_data[j+3] = colors[i].a;
            } else {
                save_data[j] = data[j];
                save_data[j+1] = data[j+1];
                save_data[j+2] = data[j+2];
                save_data[j+3] = data[j+3];
            }
        }

        char filename[50];
        char temp[5];
        memset(filename, 0, strlen(filename));
        memset(temp, 0, strlen(temp));
        sprintf(temp, "%d", i);
    
        strcat(filename, "output/variation_");
        strcat(filename, temp);
        strcat(filename,".png");
        stbi_write_png(filename, image_width, image_height, components_per_pixel, (void*)(save_data), 0);
    }

    free(save_data);
    stbi_image_free(data);
    return 0;
}