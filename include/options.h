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
  windowed
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
    int enviromentVolume = 100;
    int effectsVolume = 100;
    int musicVolume = 100;
    int masterVolume = 100;

  public:
    Options() {
      if (!loadFromFile())
        saveToFile();
    }
    bool getTutorials() const;
    void setTutorials(bool t);
    Resolution getResolution() const;
    void setResolution(Resolution r);
    Mode getMode() const;
    void setMode(Mode m);
    FPS getFPS() const;
    void setFPS(FPS f);
    Language getLanguage() const;
    void setLanguage(Language l);
    int getenviromentVolume() const;
    void setenviromentVolume(int v);
    int geteffectsVolume() const;
    void seteffectsVolume(int v);
    int getmusicVolume() const;
    void setmusicVolume(int v);
    int getmasterVolume() const;
    void setmasterVolume(int v);

    bool loadFromFile();
    void saveToFile() const;
};

#endif //OPTIONS_H
