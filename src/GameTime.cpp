#include "include/gametime.h"

#include <SFML/System/Time.hpp>

sf::Vector2i GameTime::gettime () const {
    return {game_hours, game_minutes};
}

void GameTime::timeFlow () {
    if (!isPaused) {
        sf::Time elapsed = game_clock.getElapsedTime();
        float minutes = elapsed.asSeconds();
        seconds_irl += minutes;
        while (seconds_irl >= 1.f) {
            seconds_irl -= 1.f;
            game_minutes++;
        }
        while (game_minutes >= 60) {
            game_minutes -= 60;
            game_hours++;
        }
        while (game_hours >= 24) {
            game_hours -= 24;
            newDayBlacksmith = true;
        }
    }
    game_clock.restart();
}

void GameTime::resetTimeMorning () {
    game_hours = 8;
    game_minutes = 0;
    game_clock.restart();
}

bool GameTime::getNewDayBlacksmith () const {
    return newDayBlacksmith;
}

void GameTime::setNewDayBlacksmith (bool isNewDayBlacksmith) {
    newDayBlacksmith = isNewDayBlacksmith;
}

void GameTime::pause () {
    isPaused = true;
}

void GameTime::resume () {
    isPaused = false;
}


