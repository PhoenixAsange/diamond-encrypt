#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include "Menu.hpp"
#include <utility>
#include <string>
#include <iostream>
#include <functional>
#include <vector>

/*Class that stores and manages a menu system*/

class MenuManager {
    private:
        std::vector<Menu> menus;
    
    public:
        Menu createMenu(const std::string title);
        Menu getMenu(const std::string title);
    };

#endif