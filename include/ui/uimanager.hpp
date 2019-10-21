#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <event.hpp>

namespace ui
{

class UI : public sf::Drawable
{
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update(float) = 0;
    virtual void manageEvent(const Event&) = 0;
};

class UIManager
{
private:
    UI** elements;
    size_t nbElem;

public:
    UIManager();
    UIManager(int);
    ~UIManager();

    void initGameUI();
    void initStartUI();

    void update(float);
    void dispatchEvent(const Event &);

    void render(sf::RenderWindow &);
};
}
#endif