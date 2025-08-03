#include "menuFunctions.hpp"
#include <cmath>
#include <iomanip>

DiamondCipher encryptionGrid;
DiamondCipher decryptionGrid;
MenuManager menu;
bool encrypted = false;
bool decrypted = false;

//Menu Operations

const std::string formatMessage(std::string message) {
    //Remove spaces
    message.erase(std::remove(message.begin(), message.end(), ' '), message.end());

    //Converts characters to lowercase 
    std::transform(message.begin(), message.end(), message.begin(),
           [](unsigned char character) { return std::tolower(character); });

    message.append(".");
    
    return message;
}

std::string getUserInt(const std::string& prompt) {
    std::string input;
    std::getline(std::cin, input);
    std::cout << "Enter " << prompt << ": ";

    return input;
}

std::string getUserString(const std::string& prompt) {
    std::string input;
    std::cout << "Enter " << prompt << ": ";
    std::getline(std::cin, input);

    if (input.empty() || std::all_of(input.begin(), input.end(), isspace)) {
        throw InvalidMessageException(input + " - Message cannot be empty or only spaces.");
    }

    return input;
}

//Cipher Operations
void setEncryptionMessage() {
    try {
        std::string message = getUserString("message");

        //Checks if all characters are letters
        for (char character : message) {
            if (!std::isalpha(character) && character != ' ') {
                throw InvalidMessageException(message + " - Message must only contain letters");
            }
        }

        clearScreen();
        message = formatMessage(message);
        encryptionGrid.setMessage(message); //Formats and sets message 

        std::cout << "Set message to: '" << message << "'" << std::endl;
        encrypted = false;
    } 
    catch (const InvalidMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

void setDecryptionMessage() {
    try {
        std::string message = getUserString("message");

        //Ensure message is the correct length
        int root = std::sqrt(message.length());
        if (root * root != message.length()) {
            throw InvalidMessageException(message + " - Message is not diamond encrypted");
        }

        //Checks if all characters are letters and for a period
        int periodCount = 0;
        for (char character : message) {
            if (character == '.') {
                periodCount++;
                if (periodCount > 1) {
                    throw InvalidMessageException(message + " - Message contains more than one full stop");
                }
            } else if (!std::isalpha(character)) {
                throw InvalidMessageException(message + " - Message must only contain letters");
            }
        }

        clearScreen();
        decryptionGrid.setMessage(message); //Sets message 

        std::cout << "Set message to: '" << message << "'" << std::endl;
        decrypted = false;
    } 
    catch (const InvalidMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}


void setRounds(DiamondCipher& grid) {
    try {
        std::string input = getUserInt("rounds");

        if (input.empty() || std::all_of(input.begin(), input.end(), isspace)) {
            throw InvalidRoundsException("Input cannot be empty or only spaces.");
        }

        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            throw InvalidRoundsException(input + " - Input must be numeric.");
        }

        int rounds;
        try {
            rounds = std::stoi(input); // Convert string to int
        } catch (const std::out_of_range&) {
            throw InvalidRoundsException(input + " - Number too large");
        }

        if (rounds <= 0) {
            throw InvalidRoundsException(input + " - Rounds must be positive");
        }

        clearScreen();
        grid.setRounds(rounds);
        std::cout << "Set rounds to " << rounds << std::endl;
    }
    catch (const InvalidRoundsException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

void printGrid(DiamondCipher& grid) {
    try {
        if (grid.getGridMatrix().empty() || grid.getGridMatrix().at(0).at(0) == ' ') {
            throw EmptyGridException("Cannot print");
        }
        else {
            std::string message = grid.getGrid().flatten();
            grid.getGrid().print();
            std::cout << "Message: " << message << std::endl;
        }
    }
    catch (const EmptyGridException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}


void autoSizeOneRoundEncrypt() {
    try {
        if (encryptionGrid.getMessage().empty()) {
            throw UndefinedMessageException("Cannot encrypt");
        }
        else {
            encryptionGrid.setGridDiamond(encryptionGrid.getMessage().length());
        }

        if (encrypted == true) {
            throw InvalidCipheringStateException("Message is encrypted");
        }

        if (encryptionGrid.getGridMatrix().empty() == ' ') {
            throw EmptyGridException("");
        }
        else {
            clearScreen();
            encryptionGrid.encrypt();
            encryptionGrid.getGrid().fillBlank();
            std::cout << "Message encrypted using automatic grid size" << std::endl;
        }
        encrypted = true;
    }
    catch (const UndefinedMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }    
    catch (const InvalidCipheringStateException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }
    catch (const EmptyGridException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

void setSizeOneRoundEncrypt() {
    try {
        if (encrypted == true) {
            throw InvalidCipheringStateException("Message is encrypted");
        }

        if (encryptionGrid.getMessage().empty()) {
            throw UndefinedMessageException("Cannot encrypt");
        }

        int minimumSize = encryptionGrid.getGrid().calculateMinimumSize(encryptionGrid.getMessage().length());

        std::cout << "grid size (minimum " + std::to_string(minimumSize) + ", odd and >= 3): ";
        std::string input = getUserInt("");

        if (input.empty() || std::all_of(input.begin(), input.end(), isspace)) {
            throw InvalidGridSizeException("Input cannot be empty or only spaces.");
        }

        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            throw InvalidGridSizeException(input + " - Input must be numeric.");
        }

        int size;
        try {
            size = std::stoi(input); // Convert string to int
        } catch (const std::out_of_range&) {
            throw InvalidGridSizeException(input + " - Number too large");
        }

        if (size <= 0) {
            throw InvalidGridSizeException(input + " - Rounds must be positive");
        }

        //Checks for valid grid size
        if ( size < 3 || size % 2 == 0 || size < minimumSize) {
            throw InvalidGridSizeException(std::to_string(size) + " - Grid must be greater than three and even");
        }
        else {
            clearScreen();
            encryptionGrid.setGridSize(size);
            std::cout << "Grid set to size " << size << " x " << size << std::endl;
        }

        if (encryptionGrid.getGridMatrix().empty()) {
            throw EmptyGridException("Cannot encrypt");
        }
        else {
            encryptionGrid.encrypt();
            encryptionGrid.getGrid().fillBlank();
            std::cout << "Message encrypted" << std::endl;
            encrypted = true;
        }
    }
    
    catch (const InvalidCipheringStateException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        printGrid(encryptionGrid);
        return;
    }
    catch (const UndefinedMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }
    catch (const InvalidGridSizeException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }
    catch (const EmptyGridException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

void multiRoundEncrypt() {
    try {
        if (encrypted == true) {
            throw InvalidCipheringStateException("Reset message to encrypt again");
        }

        if (encryptionGrid.getMessage().empty()) {
            throw UndefinedMessageException("Cannot encrypt");
        }
        else {
            encryptionGrid.setGridDiamond(encryptionGrid.getMessage().length());
        }

        if (encryptionGrid.getRounds() == 0) {
            throw UndefinedRoundsException("");
        }
        else {
            clearScreen();
            for (int i = 0; i < encryptionGrid.getRounds(); i++) {
                encryptionGrid.setGridDiamond(encryptionGrid.getMessage().length()); //Ensure grid is large enough

                //Encrypt
                encryptionGrid.encrypt();
                encryptionGrid.getGrid().fillBlank();

                encryptionGrid.setMessage(encryptionGrid.getGrid().flatten()); // Set encrypted message for next round

                std::cout << "Round " << i + 1 << "/" << encryptionGrid.getRounds() << ":" << std::endl;
                printGrid(encryptionGrid);
            }
            std::cout << "Message encrypted for " << encryptionGrid.getRounds() << " rounds" << std::endl;
            encrypted = true;
        }
    }
    
    catch (const InvalidCipheringStateException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        printGrid(encryptionGrid);
        return;
    }

    catch (const UndefinedMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }

    catch (const UndefinedRoundsException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

void decrypt() {
    try {
        if (decrypted == true) {
            throw InvalidCipheringStateException("Reset message to see all decryption rounds");
        }

        if (decryptionGrid.getMessage().empty()) {
            throw UndefinedMessageException("Cannot decrypt");
        }

        if (decryptionGrid.getRounds() == 0) {
            throw UndefinedRoundsException("");
        }
        else {
            //Replicates the encryption process, backwards using only rounds and encrypted message inputs
            clearScreen();
            std::string decryptedMessage;
            int size = 3;
            if (decryptionGrid.getRounds() != 1) { //Handles multi round encrypt

                std::cout << "MULTI" << std::endl;

                for (int i = 0; i < (decryptionGrid.getRounds() - 1); i++) {
                    std::cout << "Round " << i + 1 << "/" << decryptionGrid.getRounds() << ":" << std::endl;

                    //Handles first round
                    if (i == 0) {
                        decryptionGrid.setGridSize(sqrt(decryptionGrid.getMessage().length())); //Should be the same size as the final encryption round
                    }
                    else {
                        decryptionGrid.setGridDecryption((decryptionGrid.getGrid().getMatrix().size())); //Calculate the grid size that was used during encryption
                    }

                    decryptionGrid.fillGrid(); //Fill the grid with the message, junk at end is ignored
                    decryptedMessage = decryptionGrid.decryptRound(); //Reads the full diamond in current grid
                    decryptionGrid.setMessage(decryptedMessage); //Sets diamond for next round

                    printGrid(decryptionGrid);
                    std::cout << "Decoded Message: " << decryptedMessage << std::endl;
                }

                std::cout << "Final Round " << decryptionGrid.getRounds() << "/" << decryptionGrid.getRounds() << ":" << std::endl;

                while ((size * size) < decryptionGrid.getMessage().length()) {
                    size += 2;
                }
                decryptionGrid.setGridSize(size);

                decryptionGrid.fillGrid(); //Constructs a copy of the grid that was made during encryption
                printGrid(decryptionGrid);

                //Reads grid in diamond traversal pattern, until a full stop is reached
                decryptedMessage = decryptionGrid.decryptFinal();
                std::cout << "Decoded Message: " << decryptedMessage << std::endl;
            }
            else {
                std::cout << "SINGLE" << std::endl;
                std::cout << "Round " << decryptionGrid.getRounds() << "/" << decryptionGrid.getRounds() << ":" << std::endl;
                
                while ((size * size) < decryptionGrid.getMessage().length()) {
                    size += 2;
                }
                decryptionGrid.setGridSize(size);

                decryptionGrid.fillGrid(); //Constructs a copy of the grid that was made during encryption
                printGrid(decryptionGrid);

                //Reads grid in diamond traversal pattern, until a full stop is reached
                decryptedMessage = decryptionGrid.decryptFinal();
                std::cout << "Decoded Message: " << decryptedMessage << std::endl;
            }
            decrypted = true;
        }
    }
    
    catch (const InvalidCipheringStateException& e) {
        clearScreen();
        printGrid(decryptionGrid);
        std::cout << "Decoded Message: " << decryptionGrid.getMessage() << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    }

    catch (const UndefinedMessageException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
        return;
    }

    catch (const UndefinedRoundsException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
}

//Menus
void mainMenu() {
    clearScreen();
    while (true) {
        Menu main = menu.createMenu("Menu - Level 1");
        main.addOption("Encrypt a message", encryptMenu);
        main.addOption("Decrypt a message", decryptMenu);
        main.addOption("Quit", [] {
            clearScreen();
            std::cout << "Exiting" << std::endl;
            exit(0);
        });

        main.print();

        main.getMenuChoice();
    }
}

void encryptMenu() {
    clearScreen();
    while (true) {
        Menu encryption = menu.createMenu("Menu - Level 2: Encryption");
        encryption.addOption("Enter a message", setEncryptionMessage);
        encryption.addOption("One-round encryption", oneRoundEncryptMenu);
        encryption.addOption("Automatic multi-round encryption", multiRoundEncryptMenu);
        encryption.addOption("Back", mainMenu);

        encryption.print();

        encryption.getMenuChoice();
    }
}

void oneRoundEncryptMenu() {
    clearScreen();
    while (true) {
        Menu oneRoundEncryption = menu.createMenu("Menu - Level 3: Encryption");
        oneRoundEncryption.addOption("Enter a grid size", setSizeOneRoundEncrypt);
        oneRoundEncryption.addOption("Automatic grid size", autoSizeOneRoundEncrypt);
        oneRoundEncryption.addOption("Print the grid and the encoded message", []{printGrid(encryptionGrid);});
        oneRoundEncryption.addOption("Back", encryptMenu);

        oneRoundEncryption.print();

        oneRoundEncryption.getMenuChoice();
    }
}

void multiRoundEncryptMenu() {
    clearScreen();
    while (true) {
        Menu multiRoundEncryption = menu.createMenu("Menu - Level 3: Encryption");
        multiRoundEncryption.addOption("Enter the round number", []{setRounds(encryptionGrid);});
        multiRoundEncryption.addOption("For each round, print the grid and the corresponding encoded message", multiRoundEncrypt);
        multiRoundEncryption.addOption("Back", encryptMenu);

        multiRoundEncryption.print();

        multiRoundEncryption.getMenuChoice();
    }
}

void decryptMenu() {
    clearScreen();
    while (true) {
        Menu decryption = menu.createMenu("Menu - Level 2: Decryption");
        decryption.addOption("Enter a message", setDecryptionMessage);
        decryption.addOption("Enter the round number", []{setRounds(decryptionGrid);});
        decryption.addOption("For each round, print the grid and the corresponding decoded message", decrypt);
        decryption.addOption("Back", mainMenu);

        decryption.print();

        decryption.getMenuChoice();
    }
}