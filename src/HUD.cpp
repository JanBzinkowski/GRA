#include "HUD.h"

bool HUD::isHpPotionClicked(const sf::Vector2i& mouse_position){
  return m_HP_potion_button->isPressed(mouse_position);
}

bool HUD::isManaPotionClicked(const sf::Vector2i& mouse_position){
  return m_mana_potion_button->isPressed(mouse_position);
}

bool HUD::isRegenPotionClicked(const sf::Vector2i& mouse_position){
  return m_regen_potion_button->isPressed(mouse_position);
}

bool HUD::isFastActionPotionClicked(const sf::Vector2i& mouse_position){
  return m_fast_action_potion_button->isPressed(mouse_position);
}

bool HUD::isLightAtkClicked(const sf::Vector2i& mouse_position) {
  return m_light_attack_button->isPressed(mouse_position);
}
bool HUD::isMediumAtkClicked(const sf::Vector2i& mouse_position) {
  return m_medium_attack_button->isPressed(mouse_position);
}

bool HUD::isHeavyAtkClicked(const sf::Vector2i& mouse_position) {
  return m_heavy_attack_button->isPressed(mouse_position);
}