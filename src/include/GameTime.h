#ifndef GAMETIME_H
#define GAMETIME_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

class GameTime {
    private:
        sf::Clock game_clock;
        float seconds_irl = 0.f;
        int game_minutes = 0;
        int game_hours = 8;
        bool newDayBlacksmith = true;
        bool isPaused = false;

    public:
        GameTime () {
            game_clock.start();
        }

        sf::Vector2i gettime () const;
        void timeFlow ();
        void resetTimeMorning ();
        bool getNewDayBlacksmith () const;
        void setNewDayBlacksmith (bool isNewDayBlacksmith);
        void pause ();
        void resume ();
};

#endif
