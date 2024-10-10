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
// DDA
void drawLineDDA(int x0, int y0, int x1, int y1, unsigned char *image, unsigned char r, unsigned char g, unsigned char b)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);
  float xInc = dx / static_cast<float>(steps);
  float yInc = dy / static_cast<float>(steps);
  float x = x0;
  float y = y0;
  for (int i = 0; i <= steps; ++i)
  {
    setPixel(static_cast<int>(x + 0.5f), static_cast<int>(y + 0.5f), image,
             r, g, b);
    x += xInc;

    y += yInc;
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
  drawLineDDA(300, 300, 600, 800, image, 255, 0, 0);
  savePPM("lines.ppm", image);
  delete[] image;
  std::cout << "Image saved as lines.ppm" << std::endl;
  return 0;
}
