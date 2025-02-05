// Use cMake for link every part of the programm, follow online tutorials for get started
// For compile:
// 1. Using the Terminal, go to build/
// 2. Digit the command (I'm using mingw): mingw32-make
// 3. Search name_executable.exe (in my case Test01.exe) and press Enter

#include <iostream>
# include "../include/QuickHull.hh"

int main() {
    Geometry::Point2D points[] = {
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
    std::vector<Geometry::Point2D> hull = Geometry::QuickHull::quick_hull(points, n);
    // std::cout << "Punti dell'inviluppo convesso:" << std::endl;
    // for (const auto& point : hull) {
    //     std::cout << "(" << point.getX() << ", " << point.getX() << ")" << std::endl;
    // }
    return 0;
}