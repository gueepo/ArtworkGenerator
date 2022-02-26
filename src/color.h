#ifndef __COLOR_H__
#define __COLOR_H__

struct Color {
    int r;
    int g;
    int b;
    int a;
};

typedef struct Color color_t;

void Color_FillColor(color_t* color, int r, int g, int b, int a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

int Color_IsEqual(color_t* color_a, color_t* color_b) {
    if(
        color_a->r == color_b->r && 
        color_a->g == color_b->g && 
        color_a->b == color_b->b && 
        color_a->a == color_b->a 
        ) {
            return 1;
    }

    return 0;
}

#endif