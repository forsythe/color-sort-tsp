#ifndef COLOR_H
#define COLOR_H


struct Color {
    Color(int, int, int);
    Color();
    int r;
    int b;
    int g;
    float distTo(Color);
};


#endif // COLOR_H
