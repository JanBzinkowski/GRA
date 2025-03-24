#ifndef OPTIONS_H
#define OPTIONS_H

#include "global.h"

enum class FPS{
  _30,
  _60,
  _144,
};

enum class Mode{
  fullscreen,
  borderless,
};

enum class Language{
  PL,
  ENG
};

enum class Resolution{
  p360,
  p1080,
  p1440,
};



class Options {
  private:
    bool tutorials = true;
    Resolution resolution = Resolution::p1080;
    Mode mode = Mode::fullscreen;
    FPS fps = FPS::_60;
    Language language = Language::ENG;
    float enviromentVolume = 100.f;
    float effectsVolume = 100.f;
    float musicVolume = 100.f;
    float masterVolume = 100.f;

  public:
    Options() {
      if (!loadFromFile())
        saveToFile();
    }
    bool getTutorials();
    void setTutorials(bool t);
    Resolution getResolution();
    void setResolution(Resolution r);
    Mode getMode();
    void setMode(Mode m);
    FPS getFPS();
    void setFPS(FPS f);
    Language getLanguage();
    void setLanguage(Language l);
    float getenviromentVolume();
    void setenviromentVolume(float v);
    float geteffectsVolume();
    void seteffectsVolume(float v);
    float getmusicVolume();
    void setmusicVolume(float v);
    float getmasterVolume();
    void setmasterVolume(float v);

    bool loadFromFile();
    void saveToFile();
};

#endif //OPTIONS_H
