#ifndef MATRIXPOSITION_HPP
#define MATRIXPOSITION_HPP

#include "./Grid.hpp"

/*A class that stores a matrix's position without bounds checking*/

class MatrixPosition {
private:
    int row;
    int column;

    void moveUp(const int value);
    void moveDown(const int value);
    void moveLeft(const int value);
    void moveRight(const int value);

public:
    void setPosition(int row, int column);

    const int getRow() const;
    const int getColumn() const;

    void move(int up = 0, int down = 0, int left = 0, int right = 0);
};

#endif
