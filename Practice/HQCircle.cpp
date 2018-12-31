#include "inc.hpp"
using namespace CG;

int W = 600, H = 600;
Canvas canvas(H, W, 255);

double dist(int x1, int y1, int x2, int y2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }
double sample(int x, int y, int cx, int cy, int radius, int t) {
    double diff = abs(dist(x, y, cx, cy) - radius);
    if(diff > 0.5 * t) return 255;
    return diff > 0.5 * t ? 255 : 255 / (0.25 * t * t) * diff * diff;
}
void setRel8Pix(int x, int y, int cx, int cy, int sam) {
    int relX = x - cx, relY = y - cy;
    canvas.setPixel(cx + relX, cy + relY, sam); canvas.setPixel(cx - relX, cy + relY, sam);
    canvas.setPixel(cx + relX, cy - relY, sam); canvas.setPixel(cx - relX, cy - relY, sam);
    canvas.setPixel(cx + relY, cy + relX, sam); canvas.setPixel(cx - relY, cy + relX, sam);
    canvas.setPixel(cx + relY, cy - relX, sam); canvas.setPixel(cx - relY, cy - relX, sam);
}
void hqCircle(int cx, int cy, int rad, int t) {
    int x = cx, y = cy - rad - t / 2.0;
    while(x - cx <= 0.708 * rad || cy - y >= 0.708 * rad) {
        int nx = x;
        double sam;
        do {
            sam = sample(x, y, cx, cy, rad, t);
            setRel8Pix(x, y, cx, cy, sam);
            x++;
        } while((int)sam == 255 && dist(x, y, cx, cy) <= rad + t);
        if(sam != 255) nx = x - 1;
        do {
            sam = sample(x, y, cx, cy, rad, t);
            setRel8Pix(x, y, cx, cy, sam);
            x++;
        } while((int)sam != 255 && dist(x, y, cx, cy) <= rad + t);
        x = nx;
        y++;
    }
}

int main() {
    hqCircle(300, 300, 150, 5);
    canvas.outputPng("hqCircle.png");
    return 0;
}
