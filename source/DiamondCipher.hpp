#ifndef DIAMONDCIPHER_HPP
#define DIAMONDCIPHER_HPP

#include <string>
#include <vector>
#include "./Grid.hpp"
#include "./MatrixPosition.hpp"
#include "./Cipher.hpp"

/*A class that prepares, encrypts and decrypts messages using a grid*/

class DiamondCipher : public Cipher {
    private:
        std::string message;
        int rounds;
        MatrixPosition position;
        Grid grid;

    public:
        // Mutators
        void setRounds(int rounds);
        void setMessage(std::string message) override;
        void setGridDiamond(const size_t& messageLength); 
        void setGridSize(const size_t gridSize);
        void setGridDecryption(int currentSize);

        // Accessors
        Grid& getGrid();
        std::vector<std::vector<char>> getGridMatrix();
        const int& getRounds() const;
        const std::string& getMessage() const override;

        // Encryption
        void encrypt() override;

        // Decryption
        void fillGrid();
        std::string decryptRound();
        std::string decryptFinal() override;
    };

#endif
