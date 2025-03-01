#include "include/game.h"
#include <optional>
#include <conio.h>
#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR_SCREEN system("cls");
#else
    #define CLEAR_SCREEN system("clear");
#endif

void clearScreenMain() {
    CLEAR_SCREEN;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(static_cast<unsigned int>(std::time(0)));
    srand(time(0));
    postac* hero=nullptr;
    game game(hero, gen);
    while (true)
    {
        if(game.getLocation()==Location::MainMenu)
        {
            if(game.mainMenu(hero))
                break;
        }
        else if (game.getLocation()==Location::Map)
        {
            game.worldMap(hero);
        }
        else if (game.getLocation()==Location::City)
        {
            game.city(hero);
        }
        else if (game.getLocation()==Location::Church)
        {
            game.church(hero);
        }
    }
    delete hero;
    return 0;
}
