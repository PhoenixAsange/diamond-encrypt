#include "Grid.hpp"

//Return matrix
std::vector<std::vector<char>>& Grid::getMatrix() {
    return matrix;
}

//Fill blank matrix spaces with random letters
void Grid::fillBlank() {
    std::srand(std::time(0));
    for (auto& row : matrix) {
        for (auto& character : row) {
            if (character == ' ') {
                character = 'a' + rand() % 26;
            }
        }
    }
}

//Flatten matrix by concatenating all matrix characters
std::string Grid::flatten() const {
    std::string flattened;
    for (auto& row : matrix) {
        for (auto& character : row) {
            flattened += character;                    
        }
    }
    return flattened;
}

//Change grid size based
void Grid::setSize(const size_t& gridSize) {
    matrix.clear(); //Ensures blank grid
    matrix.resize(gridSize, std::vector<char>(gridSize, ' ')); //Resizes grid to n * n
}

//Change grid size based on message length
void Grid::setMinimumSize(const size_t& messageLength) {
    matrix.clear(); //Ensures blank grid
    int gridSize = calculateMinimumSize(messageLength);
    matrix.resize(gridSize, std::vector<char>(gridSize, ' ')); //Resizes grid to n * n
}

//Calculate grid size based on message length
int Grid::calculateMinimumSize(const size_t messageLength) {
    int gridSize = 3; //Has to be odd and greater than 3
    while (true) {
        int usableCells = (gridSize * gridSize) / 2; //Half of all cells are usable in diamond
        if (usableCells >= messageLength - 1) {
            return gridSize;
        }
        else{
            gridSize += 2;
        }
    }
}

//Prints the matrix
void Grid::print() const {             
    int columns = matrix[0].size();

    // Top border
    std::cout << "+";
    for (int i = 0; i < matrix.at(0).size(); ++i) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    for (const auto& row : matrix) {
        std::cout << "|";
        for (const auto& value : row) {
            std::cout << " " << value << " |";
        }
        std::cout << std::endl;

        // Row separator
        std::cout << "+";
        for (int i = 0; i < columns; ++i) {
            std::cout << "---+";
        }
        std::cout << std::endl;
    }
}      
