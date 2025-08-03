#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <iostream>
#include <functional>
#include <vector>

#include "./Menu.hpp"
#include "./MenuOption.hpp"

/*Class that manages menu options and provides menu helper functions*/

class Menu {
    private:
        std::string menuTitle;
        std::vector<MenuOption> options;

    public:
        //Constructor
        Menu(std::string menuTitle) : menuTitle(menuTitle) {}

        //Accessors
        std::vector<MenuOption> getOptions() const;
        const std::string getMenuTitle() const;
        
        void addOption(const std::string& description, std::function<void()> function);
        void print();
        void getMenuChoice();
        void runOption(size_t index) const;
};

#endif