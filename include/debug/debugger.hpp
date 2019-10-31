#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

struct Debugger
{
    static void print(const sf::Vector2f&);
    static void print(const sf::FloatRect&);
};

#endif