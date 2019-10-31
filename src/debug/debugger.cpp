#include "debug/debugger.hpp"

void Debugger::print(const sf::Vector2f& v)
{
    std::cout << "(" << v.x << "," << v.y << ")";
}

void Debugger::print(const sf::FloatRect& fr)
{
    std::cout << "(" << fr.left << "," << fr.top << ")[" 
    << fr.width <<"x"<<fr.height <<"]";
}