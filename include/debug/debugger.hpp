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

#endif