
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
const int WIDTH = 1600;
const int HEIGHT = 1600;
void setPixel(int x, int y, unsigned char *image, unsigned char r, unsigned char g, unsigned char b)
{
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
  {
    int index = (y * WIDTH + x) * 3;

    image[index] = r;
    image[index + 1] = g;
    image[index + 2] = b;
  }
}
// Bresenham
void drawLineBresenham(int x0, int y0, int x1, int y1, unsigned char *image,
                       unsigned char r, unsigned char g, unsigned char b)
{
  bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if (steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  int dx = x1 - x0;
  int dy = std::abs(y1 - y0);
  int error = dx / 2;
  int y = y0;
  int yStep = (y0 < y1) ? 1 : -1;
  for (int x = x0; x <= x1; ++x)
  {
    if (steep)
    {
      setPixel(y, x, image, r, g, b);
    }
    else
    {
      setPixel(x, y, image, r, g, b);
    }
    error -= dy;
    if (error < 0)
    {
      y += yStep;
      error += dx;
    }
  }
}

void savePPM(const char *filename, unsigned char *image)
{
  std::ofstream file(filename, std::ios::binary);
  file << "P6\n"
       << WIDTH << " " << HEIGHT << "\n255\n";
  file.write(reinterpret_cast<char *>(image), WIDTH * HEIGHT * 3);
}

int main()
{
  unsigned char *image = new unsigned char[WIDTH * HEIGHT * 3]();

  drawLineBresenham(300, 100, 500, 800, image, 0, 255, 0);
  savePPM("bresenhamLine.ppm", image);
  delete[] image;
  std::cout << "Image saved as bresenhamLine.ppm" << std::endl;
  return 0;
}
