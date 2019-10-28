#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream &os, const sf::FloatRect &fr)
{
    os << "(" << fr.left << "," << fr.top << ")[" 
    << fr.width <<"x"<<fr.height <<"]";
    return os;
}

std::ostream& operator<<(std::ostream &os, const sf::Vector2f &v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

#endif