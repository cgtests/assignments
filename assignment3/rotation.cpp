#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

const int WIDTH = 600;
const int HEIGHT = 300;

void setPixel(int x, int y, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int index = (y * WIDTH + x) * 3;
        image[index] = r;
        image[index + 1] = g;
        image[index + 2] = b;
    }
}

// Bresenham line algorithm
void drawLineBresenham(int x0, int y0, int x1, int y1, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int error = dx / 2;
    int y = y0;
    int yStep = (y0 < y1) ? 1 : -1;
    for (int x = x0; x <= x1; ++x) {
        if (steep) {
            setPixel(y, x, image, r, g, b);
        } else {
            setPixel(x, y, image, r, g, b);
        }
        error -= dy;
        if (error < 0) {
            y += yStep;
            error += dx;
        }
    }
}


void drawRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, unsigned char* image, int r, int g, int b) {
    drawLineBresenham(x1, y1, x2, y2, image, r, g, b); // Left
    drawLineBresenham(x2, y2, x3, y3, image, r, g, b); // Bottom
    drawLineBresenham(x3, y3, x4, y4, image, r, g, b); // Right
    drawLineBresenham(x4, y4, x1, y1, image, r, g, b); // Top
}

// Rotate
void rotate(int& x, int& y, float angle, int centerX, int centerY) {
    float rad = angle * M_PI / 180.0;

    // origin
    int translatedX = x - centerX;
    int translatedY = y - centerY;

    // rotation
    int rotatedX = static_cast<int>(translatedX * cos(rad) - translatedY * sin(rad));
    int rotatedY = static_cast<int>(translatedX * sin(rad) + translatedY * cos(rad));

    x = rotatedX + centerX;
    y = rotatedY + centerY;
}

// Save the image in PPM format
void savePPM(const char* filename, unsigned char* image) {
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    file.write(reinterpret_cast<char*>(image), WIDTH * HEIGHT * 3);
}

int main() {
    unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3]();

    int length = 150;
    int breadth = 80;
    int x1 = 300, y1 = 100; // Top-left corner of the rectangle

    int x2 = x1, y2 = y1 + breadth;           // Bottom-left corner
    int x3 = x1 + length, y3 = y1 + breadth;   // Bottom-right corner
    int x4 = x1 + length, y4 = y1;             // Top-right corner

    drawRectangle(x1, y1, x2, y2, x3, y3, x4, y4, image, 0, 255, 0);

    // angle
    float angle = 45;

    // center
    int centerX = (x1 + x3) / 2;
    int centerY = (y1 + y3) / 2;

    // Rotate the four corners
    rotate(x1, y1, angle, centerX, centerY);
    rotate(x2, y2, angle, centerX, centerY);
    rotate(x3, y3, angle, centerX, centerY);
    rotate(x4, y4, angle, centerX, centerY);

   
    drawRectangle(x1, y1, x2, y2, x3, y3, x4, y4, image, 0, 255, 255);

    // Save the image to a PPM file
    savePPM("rotate.ppm", image);
    delete[] image;
    std::cout << "Transformed image saved as rotate.ppm" << std::endl;
    return 0;
}
