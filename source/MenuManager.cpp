#include "MenuManager.hpp"

Menu MenuManager::createMenu(const std::string title) {
    menus.emplace_back(title); //Creates menu inside vector
    return menus.back();
}

Menu MenuManager::getMenu(const std::string title) {
    for (auto& menu : menus) {
        if (menu.getMenuTitle() == title) {
            return menu;
        }
    }
    throw std::runtime_error("Menu not found.");
}