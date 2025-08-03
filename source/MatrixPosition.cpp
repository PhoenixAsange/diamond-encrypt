#include "MatrixPosition.hpp"

//Helper functions
void MatrixPosition::moveUp(const int value) {
    row -= value;
}

void MatrixPosition::moveDown(const int value) {
    row += value;
}

void MatrixPosition::moveLeft(const int value) {
    column -= value;
}

void MatrixPosition::moveRight(const int value){ 
    column += value;
}

//Sets row and column
void MatrixPosition::setPosition(const int row, const int column) {
    this->row = row;
    this->column = column;
}

//Accessors 
const int MatrixPosition::getRow() const{
    return row;
}
const int MatrixPosition::getColumn() const{
    return column;
}

//Moves based on current position
void MatrixPosition::move(const int up, const int down, const int left, const int right) {
    moveUp(up);
    moveDown(down);
    moveLeft(left);
    moveRight(right);
}