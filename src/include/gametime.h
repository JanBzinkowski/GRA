#include <iostream>
#include <time.h>
#include <chrono>

class gameTime
{
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    int Time = 480;

public:
    bool newDayBlacksith=true;
    gameTime()
    {
        startTime = std::chrono::steady_clock::now();
    }
    void setTime (int newTime);
    int gettime() const;
    void addTime (int timeDiff);
    void timeFlow ();
    void resetTime();
    void printTime() const;
};
