#include "./MenuOption.hpp"

// Constructor        
MenuOption::MenuOption(const std::string& description, std::function<void()> function) : description(description), function(function) {}

void MenuOption::createOption(const std::string& description, std::function<void()> function) {}

const std::string MenuOption::getDescription() const {
    return description;
}