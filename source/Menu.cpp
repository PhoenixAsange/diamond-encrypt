#include "./Menu.hpp"
#include "./MenuOption.hpp"
#include "./menuExceptions.hpp"
#include <iomanip>
#include <algorithm>

//Clears CLI
void clearScreen() {
    system("cls");
}

//Accessors

std::vector<MenuOption> Menu::getOptions() const {return options;}

const std::string Menu::getMenuTitle() const {return menuTitle;}

//Add an option to the menu, appends to corresponding vector
void Menu::addOption(const std::string& description, std::function<void()> function) {
    options.emplace_back(description, function); //Creates menu option inside vector
}

//Prints Menu with loaded options
void Menu::print() {
    std::cout << std::setfill('*') << std::setw(30) << "*" << std::endl;
    std::cout << "* " << "Menu - " << menuTitle << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "* " << (i + 1) << ". " << options[i].getDescription() << std::endl;
    }
    std::cout << std::setfill('*') << std::setw(30) << "*" << std::endl;
}

void Menu::getMenuChoice() {
    std::string input;
    std::cout << "Select an option (1-" << options.size() << "): ";
    std::getline(std::cin, input);

    try {
        if (input.empty()) {
            throw InvalidMenuOptionException("Empty input");
        }

        // Check if input is numeric
        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            throw InvalidMenuOptionException(input + " Is not a number");
        }

        int choice;
        try {
            choice = std::stoi(input); // Convert string to int
        } catch (const std::out_of_range&) {
            throw InvalidRoundsException(input + " - Number too large");
        }

        //Esures menu option exists
        if (choice >= 1 && choice <= options.size()) {
            runOption(choice - 1);
        } 
        else {
            throw InvalidMenuOptionException(std::to_string(choice) + " is not a menu option");
        }
    }
    catch (const InvalidMenuOptionException& e) {
        clearScreen();
        std::cerr << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        clearScreen();
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

//Runs function
void Menu::runOption(size_t index) const {
    if (index < options.size()) {
        options[index].function();
    } else {
        std::cout << "Invalid option selected.\n";
    }
}