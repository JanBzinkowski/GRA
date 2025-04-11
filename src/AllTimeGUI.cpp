#include "AllTimeGUI.h"

bool AllTimeGUI::hpIsClicked(const sf::Vector2i& mousePos){
  return hppotion->isPressed(mousePos);
}

bool AllTimeGUI::manaIsClicked(const sf::Vector2i& mousePos){
  return manapotion->isPressed(mousePos);
}

bool AllTimeGUI::regenIsClicked(const sf::Vector2i& mousePos){
  return regenpotion->isPressed(mousePos);
}

bool AllTimeGUI::actionIsClicked(const sf::Vector2i& mousePos){
  return actionpotion->isPressed(mousePos);
}

bool AllTimeGUI::atk1IsClicked(const sf::Vector2i& mousePos) {
  return light->isPressed(mousePos);
}
bool AllTimeGUI::atk2IsClicked(const sf::Vector2i& mousePos) {
  return medium->isPressed(mousePos);
}

bool AllTimeGUI::atk3IsClicked(const sf::Vector2i& mousePos) {
  return heavy->isPressed(mousePos);
}