#include "inc.hpp"

CG::Canvas::Canvas(int height, int width):
    height(height), width(width) {
    imgmat = cv::Mat::zeros(height, width, CV_8UC3);
}

CG::Canvas::Canvas(int height, int width, int grayscale):
    height(height),
    width(width) {
    imgmat = cv::Mat::zeros(height, width, CV_8UC3);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            imgmat.ptr<cv::Vec3b>(i)[j] = cv::Vec3b(grayscale, grayscale, grayscale);
        }
    }
}

CG::Canvas::Canvas(int height, int width, Color color):
    height(height),
    width(width) {
    imgmat = cv::Mat::zeros(height, width, CV_8UC3);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            imgmat.ptr<cv::Vec3b>(i)[j] = cv::Vec3b(color.b, color.g, color.r);
        }
    }
}

void CG::Canvas::changeSize(int newHeight, int newWidth) {
    height = newHeight;
    width = newWidth;
    imgmat = cv::Mat::zeros(height, width, CV_8UC3);
}

int CG::Canvas::getHeight() { return height; }

int CG::Canvas::getWidth() { return width; }

void CG::Canvas::setPixel(int r, int c, int grayscale) {
    imgmat.ptr<cv::Vec3b>(r)[c] = cv::Vec3b(grayscale, grayscale, grayscale);
}

void CG::Canvas::setPixel(int r, int c, Color color) {
    imgmat.ptr<cv::Vec3b>(r)[c] = cv::Vec3b(color.b, color.g, color.r);
}

int CG::Canvas::getPixelGrayscale(int r, int c) {
    return (
        imgmat.ptr<cv::Vec3b>(r)[c][0] + 
        imgmat.ptr<cv::Vec3b>(r)[c][1] + 
        imgmat.ptr<cv::Vec3b>(r)[c][2]
    ) / 3;
}

CG::Color CG::Canvas::getPixelColor(int r, int c) {
    return CG::Color(
        imgmat.ptr<cv::Vec3b>(r)[c][2],
        imgmat.ptr<cv::Vec3b>(r)[c][1],
        imgmat.ptr<cv::Vec3b>(r)[c][0]
    );
}

cv::Vec3b* CG::Canvas::operator[](int r) {
    return imgmat.ptr<cv::Vec3b>(r);
}

void CG::Canvas::refreshCanvas() {
    if(!window) {
        window = true;
        cv::namedWindow("Canvas");
    }
    cv::imshow("Canvas", imgmat);
}

void CG::Canvas::outputPng(const std::string& filename) {
    cv::imwrite(filename, imgmat);
}

void CG::Canvas::wait() {
    if(!window) return;
    cv::waitKey();
}
