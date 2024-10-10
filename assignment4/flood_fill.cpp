#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
const int WIDTH = 1600;
const int HEIGHT = 1600;
void setPixel(int x, int y, unsigned char* image, unsigned char r, unsigned
char g, unsigned char b) {
if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
int index = (y * WIDTH + x) * 3;


image[index] = r;
image[index + 1] = g;
image[index + 2] = b;
}
}
// Bresenham
void drawLineBresenham(int x0, int y0, int x1, int y1, unsigned char* image,
unsigned char r, unsigned char g, unsigned char b) {
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

void savePPM(const char* filename, unsigned char* image) {
std::ofstream file(filename, std::ios::binary);
file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
file.write(reinterpret_cast<char*>(image), WIDTH * HEIGHT * 3);
}


void drawRectangle(int x1,int y1,int length,int breadth, unsigned char* image)
{
drawLineBresenham(x1, y1, x1, y1+breadth, image, 0, 255, 0); //left
drawLineBresenham(x1, y1+breadth, x1+length, y1+breadth, image, 0, 255, 0);
//bottom
drawLineBresenham(x1+length, y1+breadth, x1+length, y1, image, 0, 255, 0);
//right
drawLineBresenham(x1+length, y1, x1, y1, image, 0, 255, 0); //top
}




void floodFill(int x, int y, unsigned char* image, unsigned char fillR, unsigned char fillG, unsigned char fillB, unsigned char boundaryR, unsigned char boundaryG, unsigned char boundaryB) {
    int stackSize = WIDTH * HEIGHT; // Maximum stack size
    int* stackX = new int[stackSize];
    int* stackY = new int[stackSize];
    int stackTop = 0;

    // Push initial point onto stack
    stackX[stackTop] = x;
    stackY[stackTop] = y;
    stackTop++;

    while (stackTop > 0) {
        stackTop--;
        int cx = stackX[stackTop];
        int cy = stackY[stackTop];

        // Check if the current point is within bounds
        if (cx < 0 || cx >= WIDTH || cy < 0 || cy >= HEIGHT) continue;

        // Check if the current point is not the boundary color
        int index = (cy * WIDTH + cx) * 3;
        if (image[index] == boundaryR && image[index + 1] == boundaryG && image[index + 2] == boundaryB) continue;

        // Check if the current point is already filled with the fill color
        if (image[index] == fillR && image[index + 1] == fillG && image[index + 2] == fillB) continue;

        // Fill the current pixel with the fill color
        image[index] = fillR;
        image[index + 1] = fillG;
        image[index + 2] = fillB;

        // Push neighboring pixels onto the stack
        stackX[stackTop] = cx + 1;
        stackY[stackTop] = cy;
        stackTop++;

        stackX[stackTop] = cx - 1;
        stackY[stackTop] = cy;
        stackTop++;

        stackX[stackTop] = cx;
        stackY[stackTop] = cy + 1;
        stackTop++;

        stackX[stackTop] = cx;
        stackY[stackTop] = cy - 1;
        stackTop++;
    }

    delete[] stackX;
    delete[] stackY;
}

int main() {
unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3]();

drawRectangle(300, 100, 500, 800, image);
floodFill(310, 110, image, 0, 0, 255, 0, 255, 0);
savePPM("floodFILL.ppm", image);
delete[] image;
std::cout << "Image saved as floodFILL.ppm" << std::endl;
return 0;
}
