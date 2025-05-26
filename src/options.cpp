#include "options.h"
#include <iostream>
#include <fstream>

void Options::setTutorials(bool t) {
  tutorials = t;
}

bool Options::getTutorials() const {
  return tutorials;
}

Language Options::getLanguage() const {
  return language;
}

void Options::setLanguage(Language l) {
  language = l;
}

FPS Options::getFPS() const {
  return fps;
}

void Options::setFPS(FPS f) {
  fps = f;
}

Resolution Options::getResolution() const {
  return resolution;
}

void Options::setResolution(Resolution r) {
  resolution = r;
}

Mode Options::getMode() const {
  return mode;
}

void Options::setMode(Mode m) {
  mode = m;
}

void Options::setenviromentVolume(int v){
  enviromentVolume = v;
}

int Options::getenviromentVolume() const {
  return enviromentVolume;
}

void Options::seteffectsVolume(int v){
  effectsVolume = v;
}

int Options::geteffectsVolume() const {
  return effectsVolume;
}

void Options::setmusicVolume(int v){
  musicVolume = v;
}

int Options::getmusicVolume() const {
  return musicVolume;
}

void Options::setmasterVolume(int v) {
  masterVolume = v;
}

int Options::getmasterVolume() const {
  return masterVolume;
}

void Options::saveToFile() const {
  std::string filename = "..\\src\\options\\options.txt";
  std::ofstream file(filename, std::ios::out);
  if (file.is_open())
  {
    file << tutorials<< std::endl;
    file << static_cast<int>(language) << std::endl;
    file << static_cast<int>(fps) << std::endl;
    file << static_cast<int>(resolution) << std::endl;
    file << static_cast<int>(mode) << std::endl;
    file << enviromentVolume << std::endl;
    file << effectsVolume << std::endl;
    file << musicVolume << std::endl;
    file << masterVolume << std::endl;
    file.close();
  }
  else{
    std::cerr << "Acces violation at path: " + filename << std::endl;
    throw std::runtime_error("Acces violation at path: " + filename);
  }
}

bool Options::loadFromFile() {
  std::string filename = "..\\src\\options\\options.txt";
  std::ifstream file(filename, std::ios::in);
  if (file.is_open()){
    int temp;
    file >> tutorials;
    file >> temp;
    language = static_cast<Language>(temp);
    file >> temp;
    fps = static_cast<FPS>(temp);
    file >> temp;
    resolution = static_cast<Resolution>(temp);
    file >> temp;
    mode = static_cast<Mode>(temp);
    file >> enviromentVolume;
    file >> effectsVolume;
    file >> musicVolume;
    file >> masterVolume;
    file.close();
    return true;
  }
  else
    return false;
}