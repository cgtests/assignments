// #include <iostream>
// #include <fstream>
// #include <cmath>
// #include <algorithm>

// const int WIDTH = 800;
// const int HEIGHT = 400;

// void setPixel(int x, int y, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
//    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
//        int index = (y * WIDTH + x) * 3;
//        image[index] = r;
//        image[index + 1] = g;
//        image[index + 2] = b;
//    }
// }

// // Bresenham
// void drawLineBresenham(int x0, int y0, int x1, int y1, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
//    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
//    if (steep) {
//        std::swap(x0, y0);
//        std::swap(x1, y1);
//    }
//    if (x0 > x1) {
//        std::swap(x0, x1);
//        std::swap(y0, y1);
//    }
//    int dx = x1 - x0;
//    int dy = std::abs(y1 - y0);
//    int error = dx / 2;
//    int y = y0;
//    int yStep = (y0 < y1) ? 1 : -1;
//    for (int x = x0; x <= x1; ++x) {
//        if (steep) {
//            setPixel(y, x, image, r, g, b);
//        } else {
//            setPixel(x, y, image, r, g, b);
//        }
//        error -= dy;
//        if (error < 0) {
//            y += yStep;
//            error += dx;
//        }
//    }
// }

// // Function to draw a rectangle
// void drawRectangle(int x1, int y1, int length, int breadth, unsigned char* image, int r, int g, int b) {
//    drawLineBresenham(x1, y1, x1, y1 + breadth, image, r, g, b);          // Left
//    drawLineBresenham(x1, y1 + breadth, x1 + length, y1 + breadth, image, r, g, b); // Bottom
//    drawLineBresenham(x1 + length, y1 + breadth, x1 + length, y1, image, r, g, b); // Right
//    drawLineBresenham(x1 + length, y1, x1, y1, image, r, g, b);          // Top
// }

// // Scaling transformation
// void scale(int& x, int& y, float scaleX, float scaleY, int centerX, int centerY) {
//    // Translate the point to the origin
//    x -= centerX;
//    y -= centerY;
  
//    // Apply scaling
//    x = static_cast<int>(x * scaleX);
//    y = static_cast<int>(y * scaleY);
  
//    // Translate the point back to its original position
//    x += centerX;
//    y += centerY;
// }

// // Save the image in PPM format
// void savePPM(const char* filename, unsigned char* image) {
//    std::ofstream file(filename, std::ios::binary);
//    file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
//    file.write(reinterpret_cast<char*>(image), WIDTH * HEIGHT * 3);
// }

// void pixel(int r, int g, int b)
// {
//     printf("\x1b[38;2;%d;%d;%dm█", r, g, b);
// }
// void finish(void)
// {
//     printf("\x1b[0m");
// }
// int main() {
//    unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3]();

//    int length = 150;
//    int breadth = 80;
//    int p[] = {300, 100};

//    drawRectangle(p[0], p[1], length, breadth, image, 0, 255, 0);

//      // Scale factors
//    float scaleX = 3, scaleY = 2;

//    // Compute center of rectangle
//    int centerX = p[0] + length / 2;
//    int centerY = p[1] + breadth / 2;

//    //scale:
//    scale(p[0], p[1], scaleX, scaleY, centerX, centerY);
//    length = static_cast<int>(length * scaleX);
//    breadth = static_cast<int>(breadth * scaleY);

//    drawRectangle(p[0], p[1], length, breadth, image, 0, 255, 255);
//    savePPM("scale.ppm", image);
// //    delete[] image;
//    std::cout << "Transformed image saved as scale.ppm" << std::endl;
//     for (int y = 0; y < WIDTH * HEIGHT * 3; y++) {
        
//             pixel((image[y]/WIDTH)/20.0*256, 0, (image[y]%WIDTH)/80.0*256);
        
//         putchar('\n');
//     }
//     finish();
//    return 0;
// }


#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

const int WIDTH = 80;
const int HEIGHT = 40;

void setPixel(int x, int y, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
   if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
       int index = (y * WIDTH + x) * 3;
       image[index] = r;
       image[index + 1] = g;
       image[index + 2] = b;
   }
}

// Bresenham Line Drawing Algorithm
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

// Function to draw a rectangle
void drawRectangle(int x1, int y1, int length, int breadth, unsigned char* image, int r, int g, int b) {
   drawLineBresenham(x1, y1, x1, y1 + breadth, image, r, g, b);          // Left
   drawLineBresenham(x1, y1 + breadth, x1 + length, y1 + breadth, image, r, g, b); // Bottom
   drawLineBresenham(x1 + length, y1 + breadth, x1 + length, y1, image, r, g, b); // Right
   drawLineBresenham(x1 + length, y1, x1, y1, image, r, g, b);          // Top
}

// Scaling transformation
void scale(int& x, int& y, float scaleX, float scaleY, int centerX, int centerY) {
   // Translate the point to the origin
   x -= centerX;
   y -= centerY;
  
   // Apply scaling
   x = static_cast<int>(x * scaleX);
   y = static_cast<int>(y * scaleY);
  
   // Translate the point back to its original position
   x += centerX;
   y += centerY;
}

// Save the image in PPM format
void savePPM(const char* filename, unsigned char* image) {
   std::ofstream file(filename, std::ios::binary);
   file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
   file.write(reinterpret_cast<char*>(image), WIDTH * HEIGHT * 3);
}

void pixel(int r, int g, int b) {
    printf("\x1b[38;2;%d;%d;%dm█", r, g, b);  // Print colored block
}

void finish(void) {
    printf("\x1b[0m");  // Reset the terminal colors
}

int main() {
   unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3]();

   int length = 15;
   int breadth = 8;
   int p[] = {30, 10};

   drawRectangle(p[0], p[1], length, breadth, image, 0, 255, 0);

   // Scale factors
   float scaleX = 3, scaleY = 2;

   // Compute center of rectangle
   int centerX = p[0] + length / 2;
   int centerY = p[1] + breadth / 2;

   // Scale:
   scale(p[0], p[1], scaleX, scaleY, centerX, centerY);
   length = static_cast<int>(length * scaleX);
   breadth = static_cast<int>(breadth * scaleY);

   drawRectangle(p[0], p[1], length, breadth, image, 0, 255, 255);
   savePPM("scale.ppm", image);
   std::cout << "Transformed image saved as scale.ppm" << std::endl;

   // Display the image in terminal
   for (int y = 0; y < HEIGHT; ++y) {
       for (int x = 0; x < WIDTH; ++x) {
           int index = (y * WIDTH + x) * 3;
           int r = image[index];
           int g = image[index + 1];
           int b = image[index + 2];
           pixel(r, g, b);
       }
       putchar('\n');  // Move to the next line after printing a row of pixels
   }
   finish();

   delete[] image;
   return 0;
}
