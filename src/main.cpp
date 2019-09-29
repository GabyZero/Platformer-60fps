#include "gamev1.hpp"

#include <stdlib.h>

int main()
{
    //Game *test = new GameTest();

    //test->run();
    Game *test = new Gamev1();
    test->initGame();
    test->run();

    delete test;
    exit(0);
}
