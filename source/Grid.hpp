#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

/*A class that manages a matrix*/

class Grid {
private:
    std::vector<std::vector<char>> matrix;

public:
    std::vector<std::vector<char>>& getMatrix();
    void fillBlank();
    std::string flatten() const;
    void setSize(const size_t& gridSize);
    void setMinimumSize(const size_t& messageLength);
    int calculateMinimumSize(const size_t messageLength);
    void print() const;
};

#endif
