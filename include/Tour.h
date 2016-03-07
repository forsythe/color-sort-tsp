#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include "Color.h"
#include "defs.h"

struct Tour {
    Tour();

    Color colors[NUM_COLORS];
    double dist;

    double getDist();
    double getUpdatedDistWhenSwappedCities(int old_dist, int, int);
    void updateColors(Color[]);
    void swapColor(int, int);
    void draw();
    bool swapIsBeneficial(int, int);
    void twoOptSwap(int, int);
    double getUpdatedDistWhenTwoOptSwap(int old_dist, int, int);
};

#endif // TOUR_H
