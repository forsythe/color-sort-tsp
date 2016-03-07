#include "Tour.h"
#include "CSDLManagerLite.h"
#include "defs.h"

Tour::Tour() {
    for (int k = 0; k < NUM_COLORS; k++)
        colors[k] = Color(rand()%255, rand()%255, rand()%255);
}

void Tour::updateColors(Color t[]) {
    for (int k = 0; k < NUM_COLORS; k++)
        colors[k] = Color(t[k].r, t[k].b, t[k].g);
}

double Tour::getDist() {
    double ans = 0;
    for (int k = 0; k < NUM_COLORS-1; k++)
        ans += colors[k].distTo(colors[k+1]);

    ans+= colors[NUM_COLORS-1].distTo(colors[0]);
    return ans;
}

void Tour::swapColor(int a, int b) {
    Color temp = colors[a];
    colors[a] = colors[b];
    colors[b] = temp;
}

double Tour::getUpdatedDistWhenSwappedCities(int old_dist, int a, int b) {
    swapColor(a, b); //Temporary undo to calculate old partial score
    double amt = 0;

    if (a == 0) amt += (colors[a].distTo(colors[a+1]) + colors[a].distTo(colors[NUM_COLORS-1]));
    else if (a == NUM_COLORS-1) amt += (colors[a-1].distTo(colors[a]) + colors[0].distTo(colors[a]));
    else amt += (colors[a-1].distTo(colors[a]) + colors[a].distTo(colors[a+1]));

    if (b == 0) amt += (colors[b].distTo(colors[b+1]) + colors[b].distTo(colors[NUM_COLORS-1]));
    else if (b == NUM_COLORS-1) amt += (colors[b-1].distTo(colors[b]) + colors[0].distTo(colors[b]));
    else amt += (colors[b-1].distTo(colors[b]) + colors[b].distTo(colors[b+1]));

    old_dist -= amt;
    swapColor(a, b);

    if (a == 0) old_dist += (colors[a].distTo(colors[a+1]) + colors[a].distTo(colors[NUM_COLORS-1]));
    else if (a == NUM_COLORS-1) old_dist += (colors[a-1].distTo(colors[a]) + colors[0].distTo(colors[a]));
    else old_dist += (colors[a-1].distTo(colors[a]) + colors[a].distTo(colors[a+1]));

    if (b == 0) old_dist += (colors[b].distTo(colors[b+1]) + colors[b].distTo(colors[NUM_COLORS-1]));
    else if (b == NUM_COLORS-1) old_dist += (colors[b-1].distTo(colors[b]) + colors[0].distTo(colors[b]));
    else old_dist += (colors[b-1].distTo(colors[b]) + colors[b].distTo(colors[b+1]));

    return old_dist;
}

void Tour::twoOptSwap(int a, int b) {
    int counter = a;
    if (a == b) return;

    if (a > b)
        while (a-b>0)
            swapColor(a--, b++);

    if (a < b)
        while (b-a>0)
            swapColor(a++, b--);

}

double Tour::getUpdatedDistWhenTwoOptSwap(int old_dist, int x, int y) {
    if (x == y)
        return 0;

    int a = x < y? x : y;
    int b = x > y? x : y;

    old_dist -= colors[b].distTo(colors[a==0? NUM_COLORS-1 : a-1]);
    old_dist -= colors[a].distTo(colors[b==NUM_COLORS-1? 0 : b+1]);
    old_dist += colors[a].distTo(colors[a==0? NUM_COLORS-1 : a-1]);
    old_dist += colors[b].distTo(colors[b==NUM_COLORS-1? 0 : b+1]);

    return old_dist;
}

bool Tour::swapIsBeneficial(int x, int y) {
    if (x == y)
        return false;

    int a = x < y? x : y;
    int b = x > y? x : y;

    double ans = 0;

    ans -= colors[a].distTo(colors[a==0? NUM_COLORS-1 : a-1]);
    ans -= colors[b].distTo(colors[b==NUM_COLORS-1? 0 : b+1]);
    ans += colors[b].distTo(colors[a==0? NUM_COLORS-1 : a-1]);
    ans += colors[a].distTo(colors[b==NUM_COLORS-1? 0 : b+1]);

    return ans < 0;
}

void Tour::draw() {
    for(int k = 0; k < NUM_COLORS; k++) {
        Color temp = colors[k];
        CSDLManagerLite::getInstance()->setColor(temp.r, temp.b, temp.g, 255);
        CSDLManagerLite::getInstance()->drawRect(k*WIDTH/NUM_COLORS, 0, WIDTH/NUM_COLORS, HEIGHT);
    }
}
