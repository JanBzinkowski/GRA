#include "include/gametime.h"

void gameTime::setTime (int newTime)
{
    Time=newTime;
}
int gameTime::gettime() const
{
    return Time;
}

void gameTime::addTime (int timeDiff)
{
    Time+=timeDiff;
}

void gameTime::timeFlow()
{
    std::chrono::time_point<std::chrono::steady_clock> lastUpdate = startTime;
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    int elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();
    if (elapsedSec > 0)
    {
        if (Time>1440 && !newDayBlacksith)
        {
            newDayBlacksith=true;
        }
        Time=(Time+elapsedSec)%1440;
        if (Time < 0) Time += 1440;
        startTime=now;
    }
}

void gameTime::resetTime()
{
    Time=480;
    startTime = std::chrono::steady_clock::now();
    newDayBlacksith=true;
}

void gameTime::printTime() const
{
    std::cout<<"InGame time: "<<Time/60<<":";
    if((Time%60)<10)
        std::cout<<"0";
    std::cout<<Time%60<<"\n\n"<<std::endl;
}
