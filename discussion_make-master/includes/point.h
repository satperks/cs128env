#pragma once

#include <iostream>

class Point {
    public:
        Point();
        Point(int x, int y, int z);
        int x() const { return x_; }
        int y() const { return y_; }
        int z() const { return z_; }
        float len() const;

    private:
        int x_;
        int y_;
        int z_;
};

std::ostream& operator<<(std::ostream& os, const Point& point);
bool operator==(const Point& rhs, const Point& lhs);