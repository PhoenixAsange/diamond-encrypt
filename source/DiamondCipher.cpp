#include "DiamondCipher.hpp"
#include <cmath>

//Mutators
void DiamondCipher::setRounds(int rounds) {
    this->rounds = rounds;
}

void DiamondCipher::setMessage(std::string message) {
    this->message = message;
}

//Set grid size that ensures message will fit into diamond pattern
void DiamondCipher::setGridDiamond(const size_t& messageLength) {
    grid.setMinimumSize(messageLength);
}

//Set grid size (n * n)
void DiamondCipher::setGridSize(const size_t gridSize) {
    grid.setSize(gridSize);
}

//Calculates the grid size to replicate the encryption process
void DiamondCipher::setGridDecryption(int currentSize) {
   if (currentSize <= 3) {
        setGridSize(3);
        return;
    }

    //Calculate the size of the next grid
    int nextSize = currentSize / std::sqrt(2.0);

    if (nextSize % 2 == 0) {
        nextSize -= 1;
    }

    //Minimum allowed size
    if (nextSize < 3) {
        nextSize = 3;
    }

    setGridSize(nextSize);
}

//Accessors
Grid& DiamondCipher::getGrid() {return grid;}

std::vector<std::vector<char>> DiamondCipher::getGridMatrix() {return grid.getMatrix();}

const int& DiamondCipher::getRounds() const{return rounds;}

const std::string& DiamondCipher::getMessage() const{return message;}

//Fills grid with encoded message for decoding
void DiamondCipher::fillGrid() {
    int messageIndex = 0;
    auto& matrix = grid.getMatrix();

    //Fill grid with message
    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix[row].size(); ++col) {
            if (messageIndex < message.length()) {
                matrix[row][col] = message[messageIndex++];
            }
        }
    }
}

//Encryption
void DiamondCipher::encrypt() {
    //Set starting position
    size_t size = grid.getMatrix().size();
    position.setPosition(size / 2, 0); //Move GridPosition to first tile
    grid.getMatrix()[position.getRow()][position.getColumn()] = message.at(0); //Fill first tile
    int messageIndex = 1; //Track message progress

    //Initialize bounds to handle inner diamonds
    int rowUpperBound = size, columnUpperBound = size;
    int rowLowerBound = 0, columnLowerBound = 0;

    while (messageIndex < message.length()) {
        while (position.getRow() > rowLowerBound && messageIndex < message.length()) { //Checks bounds and message progress
            position.move(1, 0, 0, 1); // Up and right
            grid.getMatrix()[position.getRow()][position.getColumn()] = message.at(messageIndex++); //Fill tile at matrix position
        }
        rowLowerBound++; // Move bound inward for next iteration
    
        while (position.getColumn() + 1 < columnUpperBound && messageIndex < message.length()) { //Checks bounds and message progress
            position.move(0, 1, 0, 1); // Down and right
            grid.getMatrix()[position.getRow()][position.getColumn()] = message.at(messageIndex++); //Fill tile at matrix position
        }
        columnUpperBound--; // Move bound inward for next iteration
    
        while (position.getRow() + 1 < rowUpperBound && messageIndex < message.length()) { //Checks bounds and message progress
            position.move(0, 1, 1, 0); // Down and left
            grid.getMatrix()[position.getRow()][position.getColumn()] = message.at(messageIndex++); //Fill tile at matrix position
        }
        rowUpperBound--; // Move bound inward for next iteration
    
        while (position.getColumn() > columnLowerBound + 1 && messageIndex < message.length()) { //Checks bounds and message progress
            position.move(1, 0, 1, 0); // Up and left
            grid.getMatrix()[position.getRow()][position.getColumn()] = message.at(messageIndex++); //Fill tile at matrix position
        }
        columnLowerBound++; // Move bound inward for next iteration

        //Handles the final character
        if (messageIndex < message.length()) {
            if (position.getRow() > 0) {
                position.move(1, 0, 0, 0);
                grid.getMatrix()[position.getRow()][position.getColumn()] = message[messageIndex++];
            }
        }
    }
}

//Reads the entire diamond of a grid
std::string DiamondCipher::decryptRound() {
    std::string decodedMessage;

    //Set starting position
    size_t size = grid.getMatrix().size();
    position.setPosition(size / 2, 0); //Move GridPosition to first tile
    decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read first tile
    int usableTiles = (size * size) / 2 + 1; //Calculates number of tiles that need to be read

    //Initialize bounds to handle inner diamonds
    int rowUpperBound = size, columnUpperBound = size;
    int rowLowerBound = 0, columnLowerBound = 0;

    while (decodedMessage.length() < usableTiles) {
        while (position.getRow() > rowLowerBound && decodedMessage.length() < usableTiles) { //Checks bounds and message read progress
            position.move(1, 0, 0, 1); // Up and right
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        rowLowerBound++; // Move bound inward for next iteration
    
        while (position.getColumn() + 1 < columnUpperBound && decodedMessage.length() < usableTiles) { //Checks bounds and message read progress
            position.move(0, 1, 0, 1); // Down and right
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        columnUpperBound--; // Move bound inward for next iteration
    
        while (position.getRow() + 1 < rowUpperBound && decodedMessage.length() < usableTiles) { //Checks bounds and message read progress
            position.move(0, 1, 1, 0); // Down and left
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        rowUpperBound--; // Move bound inward for next iteration
    
        while (position.getColumn() > columnLowerBound + 1 && decodedMessage.length() < usableTiles) { //Checks bounds and message read progress
            position.move(1, 0, 1, 0); // Up and left
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        columnLowerBound++; // Move bound inward for next iteration

        //Handles the final character
        if (position.getRow() > 0 && decodedMessage.length() < usableTiles) {
            position.move(1, 0, 0, 0);
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()];
        }
        
    }

    return decodedMessage;
}

//Reads the diamond until a full stop is reached
std::string DiamondCipher::decryptFinal() {
    std::string decodedMessage;

    //Set starting position
    size_t size = grid.getMatrix().size();
    position.setPosition(size / 2, 0); //Move GridPosition to first tile
    decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read first tile

    //Initialize bounds to handle inner diamonds
    int rowUpperBound = size, columnUpperBound = size;
    int rowLowerBound = 0, columnLowerBound = 0;

    while (decodedMessage.back() != '.') {
        while (position.getRow() > rowLowerBound && decodedMessage.back() != '.') { //Checks bounds and message progress
            position.move(1, 0, 0, 1); // Up and right
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        rowLowerBound++; // Move bound inward for next iteration
    
        while (position.getColumn() + 1 < columnUpperBound && decodedMessage.back() != '.') { //Checks bounds and message progress
            position.move(0, 1, 0, 1); // Down and right
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        columnUpperBound--; // Move bound inward for next iteration
    
        while (position.getRow() + 1 < rowUpperBound && decodedMessage.back() != '.') { //Checks bounds and message progress
            position.move(0, 1, 1, 0); // Down and left
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        rowUpperBound--; // Move bound inward for next iteration
    
        while (position.getColumn() > columnLowerBound + 1 && decodedMessage.back() != '.') { //Checks bounds and message progress
            position.move(1, 0, 1, 0); // Up and left
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()]; //Read tile at matrix position
        }
        columnLowerBound++; // Move bound inward for next iteration

        //Handles the final character
        if (decodedMessage.back() != '.' && position.getRow() > 0) {
            position.move(1, 0, 0, 0);
            decodedMessage += grid.getMatrix()[position.getRow()][position.getColumn()];
        }
        
    }

    return decodedMessage;
}
