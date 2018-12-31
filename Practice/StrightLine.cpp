#include "inc.hpp"
using namespace CG;

Canvas canvas(600, 600, 255);

void bresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = (x1 > x0) ? 1 : -1;
    int dy = abs(y1 - y0), sy = (y1 > y0) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    while(x0 != x1 || y0 != y1) {
        canvas.setPixel(y0, x0, 0);
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}

void tester1() {
    int w = 600, h = 600;
    float cx = w * 0.5f - 0.5f, cy = h * 0.5f - 0.5f;
    for (int j = 0; j < 5; j++) {
        float r1 = fminf(w, h) * (j + 0.5f) * 0.085f;
        float r2 = fminf(w, h) * (j + 1.5f) * 0.085f;
        float t = j * M_PI / 64.0f;
        for (int i = 1; i <= 64; i++, t += 2.0f * M_PI / 64.0f) {
            float ct = cosf(t), st = sinf(t);
            bresenham((int)(cx + r1 * ct), (int)(cy - r1 * st), (int)(cx + r2 * ct), (int)(cy - r2 * st));
        }
    }
}

int main() {
    tester1();
    canvas.refreshCanvas();
    canvas.wait();
    long double a = 1e3333L;
    std::cout << a << std::endl;
    return 0;
}
