#include "./DiamondCipher.hpp"
#include "./MenuManager.hpp"
#include "./menuExceptions.hpp"
#include <algorithm>
#include <cstdlib>

extern MenuManager menu;

/*Helper functions that establish program routines and operations*/

//Helper functions
const std::string formatMessage(std::string message);

// Cipher operations
void setEncryptionMessage();
void setDecryptionMessage();
void setRounds(DiamondCipher& grid);
void setSizeOneRoundEncrypt();
void printGrid(DiamondCipher& grid);
void autoSizeOneRoundEncrypt();
void setSizeOneRoundEncrypt();
void multiRoundEncrypt();
void decrypt();

// Menu navigation
void mainMenu();
void encryptMenu();
void oneRoundEncryptMenu();
void multiRoundEncryptMenu();
void decryptMenu();
void clearScreen();