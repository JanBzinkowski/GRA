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