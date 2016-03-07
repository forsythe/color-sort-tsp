#include "Color.h"
#include "CSDLManagerLite.h"

Color::Color() {

}

Color::Color(int x, int y, int z) {
    r = x;
    b = y;
    g = z;
}

float fastSqrt(float x) {
    unsigned int i = *(unsigned int*) &x;

    // adjust bias
    i  += 127 << 23;
    // approximation of square root
    i >>= 1;

    return *(float*) &i;
}

float Color::distTo(Color c) {
    return fastSqrt((r-c.r)*(r-c.r) + (b-c.b)*(b-c.b) + (g-c.g)*(g-c.g));
}
