#ifndef __CANVAS__HPP__
#define __CANVAS__HPP__

#include "inc.hpp"

namespace CG {

struct Color {
    unsigned char r, g, b;
    Color() {}
    Color(unsigned char r, unsigned char g, unsigned b): r(r), g(g), b(b) {}
};

class Canvas {
private: 
    cv::Mat imgmat;
    int height;
    int width;
    bool window = false;
public:
    Canvas() {};
    Canvas(int height, int width);
    Canvas(int height, int width, int grayscale);
    Canvas(int height, int width, Color color);

    int getHeight();
    int getWidth();

    void changeSize(int newHeight, int newWidth);

    void setPixel(int r, int c, int grayscale);
    void setPixel(int r, int c, Color color);
    int getPixelGrayscale(int r, int c);
    Color getPixelColor(int r, int c);

    cv::Vec3b* operator[](int r);

    void refreshCanvas();
    void wait();
    void outputPng(const std::string& filename);
};

}

#endif
