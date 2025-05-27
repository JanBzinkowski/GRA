#include "HUD.h"

HUD::HUD (Hero*& hero, GameTime* game_time, sf::RenderWindow*& window): m_hero_ptr(hero), m_game_time_ptr(game_time) {
  m_scale = window->getSize().y / 360.f;
  if (!m_font.openFromFile("..\\src\\fonts\\pixel-8x8.ttf")) {
    std::cerr << "Failed to load font from file: " << "..\\src\\fonts\\pixel-8x8.ttf" << std::endl;
    throw std::runtime_error("Failed to load font from file: ..\\src\\fonts\\pixel-8x8.ttf");
  }
  if (!m_top_hud_texture.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png")) {
    std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png" << std::endl;
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png");
  }
  if (!m_lock_texture.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png")) {
    std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png" << std::endl;
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");
  }
  m_top_hud_sprite = std::make_unique<sf::Sprite>(m_top_hud_texture);
  m_top_hud_sprite->setPosition({0, 0});
  m_top_hud_sprite->scale({m_scale, m_scale});
  if (!m_bottom_hud_texture.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png")) {
    std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png" << std::endl;
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png");
  }
  m_bottom_hud_sprite = std::make_unique<sf::Sprite>(m_bottom_hud_texture);
  m_bottom_hud_sprite->setPosition({0, m_scale * 318.f});
  m_bottom_hud_sprite->scale({m_scale, m_scale});
  if (!m_white_rectangle.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png")) {
    std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png" << std::endl;
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png");
  }
  m_exp_white_rectangle_sprite = std::make_unique<sf::Sprite>(m_white_rectangle);
  m_exp_white_rectangle_sprite->setPosition({m_scale * 259.f, m_scale * 16.f});
  m_exp_white_rectangle_sprite->scale({m_scale, m_scale});
  if (!m_blue_rectangle.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png")) {
    std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png" << std::endl;
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png");
  }
  m_exp_blue_rectangle_sprite = std::make_unique<sf::Sprite>(m_blue_rectangle);
  m_exp_blue_rectangle_sprite->setPosition({m_scale * 257.f, m_scale * 16.f});
  m_exp_blue_rectangle_sprite->scale({m_scale, m_scale});
  m_hp_text = std::make_unique<sf::Text>(m_font, "", int(m_scale * 16));
  m_mana_text = std::make_unique<sf::Text>(m_font, "", int(m_scale * 16));
  m_gold_text = std::make_unique<sf::Text>(m_font, "", int(m_scale * 16));
  this->m_time_text = std::make_unique<sf::Text>(m_font, "", int(m_scale * 16));
  m_hp_text->setPosition({m_scale * 323.f, m_scale * 324.f});
  m_mana_text->setPosition({m_scale * 323.f, m_scale * 338.f});
  m_gold_text->setPosition({m_scale * 63.f, m_scale * 3.f});
  this->m_time_text->setPosition({530 * m_scale, m_scale * 3.f});

  m_HP_potion_button = std::make_unique<Button>(481.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\hp_potion20x20.png");
  m_mana_potion_button = std::make_unique<Button>(515.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\mana_potion20x20.png");
  m_regen_potion_button = std::make_unique<Button>(549.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\regen_potion20x20.png");
  m_fast_action_potion_button = std::make_unique<Button>(583.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\action_potion20x20.png");
  if (m_hero_ptr->getClass() == "Warrior") {
    m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f,  window,"..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_heavy.png");
    m_light_attack_button = std::make_unique<Button>(37.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_weak.png");
    m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_normal.png");
  }
  else if (m_hero_ptr->getClass() == "Archer") {
    m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_strong.png");
    m_light_attack_button = std::make_unique<Button>(37.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_weak.png");
    m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_normal.png");
  }
  else if (m_hero_ptr->getClass() == "Mage") {
    m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_strong.png");
    m_light_attack_button = std::make_unique<Button>(37.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_weak.png");
    m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, window, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_medium.png");
  }
  m_gold_text->setFillColor(sf::Color::Black);
  m_mana_text->setFillColor(sf::Color::Black);
  m_hp_text->setFillColor(sf::Color::Black);
  this->m_time_text->setFillColor(sf::Color::Black);
}

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

void HUD::draw (sf::RenderTarget& target, sf::RenderStates states) const {
  int max_exp_threshold = 5 * pow(m_hero_ptr->getLvl(), 2.2) + 25;
  m_exp_blue_rectangle_sprite->setScale({m_hero_ptr->getCurrentExp() / float(max_exp_threshold) * m_scale, m_scale});
  m_hp_text->setString(std::to_string(m_hero_ptr->getCurrentHP()) + "/" + std::to_string(m_hero_ptr->getStats().base_hp));
  m_mana_text->setString(std::to_string(m_hero_ptr->getCurrentMana()) + "/" + std::to_string(m_hero_ptr->getStats().mana));
  m_gold_text->setString(std::to_string(m_hero_ptr->getCurrentGold()));
  std::string timeString = (m_game_time_ptr->gettime().x < 10? "0" : "") + std::to_string(m_game_time_ptr->gettime().x) + ":" + (m_game_time_ptr->gettime().y < 10? "0" : "") + std::to_string(m_game_time_ptr->gettime().y);
  m_time_text->setString(timeString);
  target.draw(*m_exp_white_rectangle_sprite);
  target.draw(*m_exp_blue_rectangle_sprite);
  target.draw(*m_top_hud_sprite, states);
  target.draw(*m_bottom_hud_sprite, states);
  target.draw(*m_hp_text, states);
  target.draw(*m_mana_text, states);
  target.draw(*m_gold_text, states);
  target.draw(*m_time_text, states);
  if (m_hero_ptr->getLvl() < 2)
    m_HP_potion_button->setNewTexture(m_lock_texture);
  if (m_hero_ptr->getLvl() < 4)
    m_regen_potion_button->setNewTexture(m_lock_texture);
  if (m_hero_ptr->getLvl() < 5)
    m_mana_potion_button->setNewTexture(m_lock_texture);
  if (m_hero_ptr->getLvl() < 8)
    m_fast_action_potion_button->setNewTexture(m_lock_texture);
  target.draw(*m_HP_potion_button, states);
  target.draw(*m_regen_potion_button, states);
  target.draw(*m_mana_potion_button, states);
  target.draw(*m_fast_action_potion_button, states);
  target.draw(*m_medium_attack_button, states);
  target.draw(*m_heavy_attack_button, states);
  target.draw(*m_light_attack_button, states);
}