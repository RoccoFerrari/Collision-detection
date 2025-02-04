// Use this command to link file.hh
// g++ Point.cpp GeometryUtils.cpp main.cpp -o build/test01.exe -o build/Point.o -o build/GeometryUtils.o -o build/main.o

#include <iostream>
#include "../include/Point.hh"
# include "../include/GeometryUtils.hh"

int main() {
    Geometry::Point points[] = {
        {0, 0},
        {1, 5},
        {2, 2},
        {3, 7},
        {4, 1},
        {5, 5},
        {6, 0},
        {7, 3},
        {8, 8},
        {9, 2}
    };
    int n = sizeof(points) / sizeof(points[0]);
    std::vector<Geometry::Point> hull = Geometry::GeometryUtils::QuickHull(points, n);
    std::cout << "Punti dell'inviluppo convesso:" << std::endl;
    for (const auto& point : hull) {
        std::cout << "(" << point.getX() << ", " << point.getX() << ")" << std::endl;
    }
    return 0;
}