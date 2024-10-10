#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

const int WIDTH = 600;
const int HEIGHT = 600;

struct Edge {
    int yMax;
    float xMin;
    float dx; // Change in x per scan line (1/slope)
};

// Set the pixel in the image array
void setPixel(int x, int y, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int index = (y * WIDTH + x) * 3;
        image[index] = r;
        image[index + 1] = g;
        image[index + 2] = b;
    }
}

// Bresenham Line
void drawLineBresenham(int x0, int y0, int x1, int y1, unsigned char* image, unsigned char r, unsigned char g, unsigned char b) {
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = abs(y1 - y0);
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

// Scan Line Fill Algorithm
void scanLineFill(const std::vector<int>& x, const std::vector<int>& y, int n, unsigned char* image) {
    // Find ymin and ymax
    int ymin = *std::min_element(y.begin(), y.end());
    int ymax = *std::max_element(y.begin(), y.end());

    // Create the edge table (ET)
    std::vector<Edge> edgeTable;
    for (int i = 0; i < n; ++i) {
        int x1 = x[i];
        int y1 = y[i];
        int x2 = x[(i + 1) % n];
        int y2 = y[(i + 1) % n];

        if (y1 == y2) continue;

        if (y1 > y2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        Edge edge;
        edge.yMax = y2;
        edge.xMin = x1;
        edge.dx = (float)(x2 - x1) / (y2 - y1); // 1/m

        edgeTable.push_back(edge);
    }

    // Sort ET
    std::sort(edgeTable.begin(), edgeTable.end(), [](const Edge& e1, const Edge& e2) {
        if (e1.yMax != e2.yMax) return e1.yMax < e2.yMax;
        return e1.xMin < e2.xMin;
    });

    // Active Edge Table (AET)
    std::vector<Edge> activeEdgeTable;

    // Start scan line from ymax to ymin
    for (int scanline = ymax; scanline >= ymin; --scanline) {
        // erase for yMax = current scan line
        activeEdgeTable.erase(
            std::remove_if(activeEdgeTable.begin(), activeEdgeTable.end(), [scanline](Edge& e) {
                return e.yMax <= scanline;
            }),
            activeEdgeTable.end());

        // Add edges that start at the current scan line
        for (const auto& edge : edgeTable) {
            if (edge.yMax > scanline && scanline >= edge.xMin) {
                activeEdgeTable.push_back(edge);
            }
        }

        // Sort AET
        std::sort(activeEdgeTable.begin(), activeEdgeTable.end(), [](const Edge& e1, const Edge& e2) {
            return e1.xMin < e2.xMin;
        });

        // Fill pixels between pairs of intersections (RED)
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
            if (i + 1 >= activeEdgeTable.size()) break;

            int xStart = (int)activeEdgeTable[i].xMin;
            int xEnd = (int)activeEdgeTable[i + 1].xMin;
            for (int x = xStart; x <= xEnd; ++x) {
                setPixel(x, scanline, image, 255, 0, 0);
            }
        }

        // Update xMin for each edge
        for (auto& edge : activeEdgeTable) {
            edge.xMin += edge.dx;
        }
    }
}

// Save the image in PPM format
void savePPM(const char* filename, unsigned char* image) {
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    file.write(reinterpret_cast<char*>(image), WIDTH * HEIGHT * 3);
}

int main() {
    unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3]();

    // polygon
    int n = 4;
    std::vector<int> x = {10, 400, 400, 10}; 
    std::vector<int> y = {10, 10, 500, 500}; 


    for (int i = 0; i < n; ++i) {
        drawLineBresenham(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], image, 0, 255, 0);
    }

    //apply scanLine
    scanLineFill(x, y, n, image);

    // Save output
    savePPM("scanline_fill.ppm", image);

    delete[] image;
    std::cout << "Polygon filled and saved as scanline_fill.ppm" << std::endl;
    return 0;
}
