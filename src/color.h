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