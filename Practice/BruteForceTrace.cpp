#include "../inc.hpp"
using namespace CG;

const int H = 600, W = 600;
Canvas canvas(H, W, 0);

int cx = 300, cy = 300, r = 50;
double mat[H][W];

double dist(int x1, int y1, int x2, int y2) { return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));}

bool isLightSource(int x, int y) {
    return dist(x, y, cx, cy) <= r;
}

void trace(int sx, int sy) {
    double angle = 0.0;
    for(int i = 0; i < 150; ++i) {
        double dx = cos(angle), dy = sin(angle);
        double cx = sx, cy = sy;
        while((int)cx >= 0 && (int)cx < W && (int)cy >= 0 && (int)cy < H) {
            mat[(int)cy][(int)cx] += 0.04;
            cx += dx, cy += dy;
        }
        angle += M_PI * 2 / 150;
    }
}

void drawLight() {
    int x0 = cx - r, y0 = cy - r;
    int x1 = cx + r, y1 = cy + r;
    canvas.forEachPixelInRangeDo(x0, y0, x1, y1, [&](int x, int y)->bool {
        if(isLightSource(x, y)) trace(x, y);
        return true;
    });
    for(int i = 0; i < H; ++i) for(int j = 0; j < W; ++j) {
        canvas.setPixel(i, j, fmin(255.0, mat[i][j]));
    }
}

int main() {
    drawLight();
    canvas.outputPng("result/light.png");
    return 0;
}
