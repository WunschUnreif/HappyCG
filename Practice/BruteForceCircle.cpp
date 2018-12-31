#include "inc.hpp"
using namespace CG;

int W = 600, H = 600;
Canvas canvas(H, W, 255);

double sample(int x, int y, int cx, int cy, int radius, int t) {
    double diff = abs(sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) - radius);
    if(diff > 0.5 * t) return 255;
    return 255 / (0.25 * t * t) * diff * diff;
}

void bruteForceCircle(int cx, int cy, int rad, int t) {
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            canvas.setPixel(r, c, sample(r, c, cx, cy, rad, t));
        }
    }
}

int main() {
    bruteForceCircle(300, 300, 150, 5);
    canvas.outputPng("bfCircle.png");
    return 0;
}
