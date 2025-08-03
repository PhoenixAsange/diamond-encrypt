#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP

#include <string>
#include <functional>
#include <iostream>
#include <vector>

/*Class that manages menu option data*/

class MenuOption {
    private:
        std::string description;

    public:     
        MenuOption(const std::string& description, std::function<void()> function);

        std::function<void()> function;

        void createOption(const std::string& description, std::function<void()> function);

        const std::string getDescription() const;
    };
#endif