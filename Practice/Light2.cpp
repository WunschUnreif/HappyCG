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

std::function<bool(int, int)> predInBox(int x0, int y0, int x1, int y1) {
    return [&](int x, int y) -> bool {
        return !(x >= x0 && x <= x1 && y >= y0 && y <= y1);
    };
}

auto p1 = predInBox(90, 290, 100, 310);

bool judge(int x, int y) {
    return !(
        (x >= 90 && x <= 100 && y >= 293 && y <= 307) ||
        (x >= 500 && x <= 510 && y >= 293 && y <= 307) ||
        dist(x, y, 200, 400) <= 25
    );
}

void trace(int sx, int sy) {
    double angle = 0.0;
    for(int i = 0; i <= 720; ++i) {
        double dx = cos(angle), dy = sin(angle);
        double cx = sx, cy = sy;
        while((int)cx >= 0 && (int)cx < W && (int)cy >= 0 && (int)cy < H) {
            if(!judge(cx, cy)) break;
            mat[(int)cy][(int)cx] += 0.025;
            cx += dx, cy += dy;
        }
        angle += M_PI * 2 / 720;
    }
}

void drawLight() {
    int x0 = 100, y0 = 295;
    int x1 = 500, y1 = 305;
    int counter = 0;
    canvas.forEachPixelInRangeDo(x0, y0, x1, y1, [&](int x, int y)->bool {
        trace(x, y);
        std::cout << ++counter << '/' << (x1-x0) * (y1-y0) << std::endl;
        return true;
    });
    for(int i = 0; i < H; ++i) for(int j = 0; j < W; ++j) {
        canvas.setPixel(i, j, fmin(255.0, mat[i][j]));
    }
}

int main() {
    drawLight();
    canvas.outputPng("result/light2.png");
    return 0;
}
