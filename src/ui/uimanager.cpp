#include "ui/uimanager.hpp"

namespace ui
{

UIManager::UIManager()
{
    nbElem = 0;
}

UIManager::UIManager(int _nbElem):nbElem(_nbElem)
{
    elements = new UI*[nbElem];
}

UIManager::~UIManager()
{
    if(nbElem!=0)delete[] elements;
}

void UIManager::initGameUI()
{

}

void UIManager::initStartUI()
{

}

void UIManager::update(float dt)
{
    for(uint i=0;i<nbElem;++i)
    {
        elements[i]->update(dt);
    }
}

void UIManager::dispatchEvent(const Event &evt)
{
    for(uint i=0;i<nbElem;++i)
    {
        elements[i]->manageEvent(evt);
    }
}

void UIManager::render(sf::RenderWindow &window)
{
    for(uint i=0;i<nbElem;++i)
    {
        window.draw(*(elements[i]));
    }
}

}