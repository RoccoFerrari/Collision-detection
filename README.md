# Collision Detection

A powerful and efficient C++ library for handling virtual collisions between 2D and 3D objects.

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/RoccoFerrari/collision-detection.svg)](https://github.com/RoccoFerrari/collision-detection/stargazers)

## Overview

This library provides a robust and optimized solution for detecting collisions between various geometric shapes in both 2D and 3D environments. It's designed to be fast and accurate, making it suitable for real-time applications such as games, simulations, and robotics.

## Features

* **2D and 3D Support:** Handles collisions between a wide range of shapes, including circles, rectangles, polygons, spheres, boxes, and meshes.
* **Efficient Algorithms:** Implements optimized algorithms for collision detection, ensuring high performance even with complex scenes.
* **Inspired by "Real-Time Collision Detection":** Draws inspiration from Christer Ericson's renowned book, incorporating proven techniques and best practices.
* **Easy to Use:** Provides a simple and intuitive API, allowing for quick integration into your projects.
* **Customizable:** Offers flexibility to customize collision detection behavior and add support for custom shapes.

## Getting Started

### Prerequisites

* A C++ compiler that supports C++11 or later.
* CMake (optional, for building the library).

### Installation

1.  Clone the repository:

    ```bash
    git clone [https://github.com/RoccoFerrari/Collision-detection.git]
    ```

2.  Build the library using CMake (recommended):

    ```bash
    cd Collision-detection
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  Include the library in your project and start detecting collisions!

### Just an easy example

```c++
#include <vector>
#include "../include/QuickHull.hh"

int main() {
    //Create a Point2D vector
    std::vector<Geometry::Point2D> vec = {
        (1,2),(2,3),(4,1),(4,3),(5,2),(3,2),
        (7,0),(1,3),(3,4)
    };
    // Return a vector of Point2D that rapresent a hull of the given vector of Point2D
    std::vector<Geometry::Point2D> res;
    res = Geometry::QuickHull::quick_hull(vec);

    return 0;
}
