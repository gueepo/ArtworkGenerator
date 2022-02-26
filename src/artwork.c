#include <stdio.h>
#include <string.h>

#include "image.h"
#include "color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

color_t default_color = {255, 93, 204, 255};
color_t empty_color = {0, 0, 0, 0};
#define COLORS 19
color_t colors[COLORS];

color_t GetColorFromImage(image_t* image, int index) {
    color_t color = {
        image->data[index],
        image->data[index+1],
        image->data[index+2],
        image->data[index+3],
    };

    return color;
}

void PutColorOnDataRGB(unsigned char* data, int index, int r, int g, int b) {
    data[index] =   r;
    data[index+1] = g;
    data[index+2] = b;
    data[index+3] = 255;
}

void PutColorOnData(unsigned char* data, int index, color_t* color) {
    data[index] =   color->r;
    data[index+1] = color->g;
    data[index+2] = color->b;
    data[index+3] = color->a;
}

int main(void) {    
    int total_size = 0;
    image_t* background = Image_CreateImage("src/base/background.png");
    image_t* head = Image_CreateImage("src/base/head.png");
    image_t* torso = Image_CreateImage("src/base/torso.png");
    Color_FillColor(&colors[0], 133, 218, 235, 255);
    Color_FillColor(&colors[1], 95, 201, 231, 255);
    Color_FillColor(&colors[2],  95, 161, 231, 255);
    Color_FillColor(&colors[3],  95, 110, 231, 255);

    Color_FillColor(&colors[4],  76, 96, 170, 255);
    Color_FillColor(&colors[5],  68, 71, 116, 255);
    Color_FillColor(&colors[6],  70, 60, 95, 255);

    Color_FillColor(&colors[7],  93, 71, 118, 255);
    Color_FillColor(&colors[8],  133, 83, 149, 255);
    Color_FillColor(&colors[9],  171, 88, 168, 255);
    Color_FillColor(&colors[10],  202, 96, 174, 255);

    Color_FillColor(&colors[11],  243, 167, 135, 255);
    Color_FillColor(&colors[12],  245, 218, 167, 255);
    Color_FillColor(&colors[13],  141, 216, 148, 255);
    Color_FillColor(&colors[14],  93, 193, 144, 255);

    Color_FillColor(&colors[15],  74, 185, 163, 255);
    Color_FillColor(&colors[16],  69, 147, 165, 255);
    Color_FillColor(&colors[17],  94, 253, 247, 255);

    Color_FillColor(&colors[18],  253, 254, 137, 255);


    printf("background image width: %d, image height: %d, components: %d\n", background->image_width, background->image_height, background->components_per_pixel);
    total_size = background->image_width * background->image_height * background->components_per_pixel;
    unsigned char* save_data = (unsigned char*)malloc(sizeof(unsigned char) * total_size);

    // how we do this?
    int variation = 0;
    for(int bg = 0; bg < COLORS; bg++) {
        for(int skn = 0; skn < COLORS; skn++) {
            for(int trs = 0; trs < COLORS; trs++) {
                for(int j = 0; j < total_size; j += 4) {

                    color_t currentBgColor = GetColorFromImage(background, j);
                    color_t currentSkinColor = GetColorFromImage(head, j);
                    color_t currentTorsoColor = GetColorFromImage(torso, j);

                    if(Color_IsEqual(&currentBgColor, &default_color) == 1) {
                        PutColorOnData(save_data, j, &colors[bg]);
                    } else {
                        PutColorOnDataRGB(save_data, j, background->data[j], background->data[j+1], background->data[j+2]);
                    }

                    if(Color_IsEqual(&currentTorsoColor, &default_color) == 1) {
                        PutColorOnData(save_data, j, &colors[trs]);
                    } else if(!Color_IsEqual(&currentTorsoColor, &empty_color)) {
                        PutColorOnDataRGB(save_data, j, torso->data[j], torso->data[j+1], torso->data[j+2]);
                    }

                    if(Color_IsEqual(&currentSkinColor, &default_color) == 1) {
                        PutColorOnData(save_data, j, &colors[skn]);
                    } else if(!Color_IsEqual(&currentSkinColor, &empty_color)) {
                        PutColorOnDataRGB(save_data, j, head->data[j], head->data[j+1], head->data[j+2]);
                    }

                }


                char filename[50];
                char temp[5];
                memset(filename, 0, strlen(filename));
                memset(temp, 0, strlen(temp));
                sprintf(temp, "%d", variation);
                variation++;

                strcat(filename, "src/output/variation_");
                strcat(filename, temp);
                strcat(filename,".png");
                printf("Generating variation %d...\n", variation);
                stbi_write_png(filename, background->image_width, background->image_height, background->components_per_pixel, (void*)(save_data), 0);
            }
        }
    }

    free(save_data);

    Image_FreeImage(background);
    return 0;
}