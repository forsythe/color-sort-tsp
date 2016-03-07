#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "CSDLManagerLite.h"
#include "CSDLInputManagerLite.h"
#include "defs.h"
#include "Tour.h"

using namespace std;
inline float fast_log2 (float val)
{
    int * const    exp_ptr = reinterpret_cast <int *> (&val);
    int            x = *exp_ptr;
    const int      log_2 = ((x >> 23) & 255) - 128;
    x &= ~(255 << 23);
    x += 127 << 23;
    *exp_ptr = x;

    val = ((-1.0f/3) * val + 2) * val - 2.0f/3;   // (1)

    return (val + log_2);
}

inline float fast_log (const float &val)
{
    return (fast_log2 (val) * 0.69314718f);
}

//Acceptance probability
double accPrb(double energy, double new_energy, double temp)
{
    if (new_energy < energy)
        return 1.0;
    return exp((energy-new_energy)/temp);
}

void update() {
    CSDLManagerLite::getInstance()->drawFrame();
    CSDLInputManagerLite::getInstance()->update();
}

Tour cur = Tour();
Tour best_tour = Tour();
double cur_energy, new_energy;
bool done_twoOpt = false;

void twoOpt() {
    if (done_twoOpt) return;
    cur_energy = cur.getDist();
    int start, finish, temp;
    finish = -1;
    start = 0;

    while (finish < start) {
        start = cur.getDist();
        for (int r = 0; r < NUM_COLORS - 1; r++) {
            for (int c = r + 1; c < NUM_COLORS; c++) {
                if (!cur.swapIsBeneficial(r, c))  continue;
                cur.twoOptSwap(r, c);
                cur_energy = cur.getUpdatedDistWhenTwoOptSwap(cur_energy, r, c);
                if (ANIMATE) {
                cur.draw();
                update();
            }
            }

        }
        finish = cur.getDist();

        if (finish < start)
            best_tour.updateColors(cur.colors);
    }
    cout << "Final distance after 2-opt: " << best_tour.getDist() << endl;
    done_twoOpt = true;
}

int main(int argc, char * argv[])
{
    srand ( time(NULL) );
    CSDLManagerLite::getInstance()->initializeSDL(WIDTH, HEIGHT, TITLE);

    cout << "Initial distance: " << cur.getDist() << endl;
    cout << "Colors: " << NUM_COLORS << endl;

    int a, b;
    double cur_energy, new_energy;

    while (!CSDLInputManagerLite::getInstance() -> isExit())
    {
        CSDLManagerLite::getInstance()->delay(1000);
        twoOpt();
        best_tour.draw();
        update();
    }
    CSDLManagerLite::getInstance()->clean();
}
