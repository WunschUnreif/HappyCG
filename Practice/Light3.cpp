#include "../inc.hpp"
using namespace CG;

const int H = 600, W = 600;
Canvas canvas(H, W, 0);

double mat[H][W];

double dist(int x1, int y1, int x2, int y2) { return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));}

bool isLightSource(int x, int y) {
    return dist(x, y, 300, 200) <= 25 ||
            dist(x, y, 300, 400) <= 25;
}

bool judge(int x, int y) {
    return !(
        (x >= 90 && x <= 100 && y >= 293 && y <= 307) ||
        (x >= 500 && x <= 510 && y >= 293 && y <= 307) ||
        false // dist(x, y, 200, 400) <= 25
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
    int counter = 0;
    canvas.forEachPixelDo([&](int x, int y)->bool {
        if(isLightSource(x, y)) trace(x, y);
        std::cout << ++counter << '/' << W * H << std::endl;
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
