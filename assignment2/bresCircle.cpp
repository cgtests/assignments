
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
const int WIDTH = 800;

const int HEIGHT = 800;
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
// circle
void drawCircleBresenham(int xc, int yc, int r, unsigned char *image, unsigned char red, unsigned char green, unsigned char blue)
{
  int x = 0;
  int y = r;
  int d = 3 - 2 * r;
  auto plotCirclePoints = [&](int cx, int cy)
  {
    setPixel(cx + x, cy + y, image, red, green, blue);
    setPixel(cx - x, cy + y, image, red, green, blue);
    setPixel(cx + x, cy - y, image, red, green, blue);
    setPixel(cx - x, cy - y, image, red, green, blue);
    setPixel(cx + y, cy + x, image, red, green, blue);
    setPixel(cx - y, cy + x, image, red, green, blue);
    setPixel(cx + y, cy - x, image, red, green, blue);
    setPixel(cx - y, cy - x, image, red, green, blue);
  };
  plotCirclePoints(xc, yc);
  while (x < y)
  {
    if (d < 0)
    {
      d = d + 4 * x + 6;
    }
    else
    {
      d = d + 4 * (x - y) + 10;
      y--;
    }
    x++;
    plotCirclePoints(xc, yc);
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
  drawCircleBresenham(WIDTH / 2, HEIGHT / 2, 255, image, 255, 255, 0); 
  savePPM("circle.ppm", image);
  delete[] image;
  std::cout << "Image saved as circle.ppm" << std::endl;
  return 0;
}
