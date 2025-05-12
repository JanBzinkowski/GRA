#ifndef HUD_H
#define HUD_H
#include <gametime.h>
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "global.h"
#include "math.h"
#include "Button.h"
#include <string>

class HUD: public sf::Drawable {
  private:
    sf::Texture m_blue_rectangle;
    sf::Texture m_white_rectangle;
    sf::Texture m_lock_texture;
    std::unique_ptr<sf::Text> m_gold_text;
    std::unique_ptr<sf::Text> m_time_text;
    std::unique_ptr<sf::Text> m_hp_text;
    std::unique_ptr<sf::Text> m_mana_text;
    std::unique_ptr<sf::Sprite> m_exp_white_rectangle_sprite;
    std::unique_ptr<sf::Sprite> m_exp_blue_rectangle_sprite;
    sf::Font m_font;
    sf::Texture m_top_hud_texture;
    sf::Texture m_bottom_hud_texture;
    std::unique_ptr<sf::Sprite> m_top_hud_sprite;
    std::unique_ptr<sf::Sprite> m_bottom_hud_sprite;
    Hero* m_hero_ptr;
    std::unique_ptr<Button> m_HP_potion_button;
    std::unique_ptr<Button> m_mana_potion_button;
    std::unique_ptr<Button> m_regen_potion_button;
    std::unique_ptr<Button> m_fast_action_potion_button;
    std::unique_ptr<Button> m_light_attack_button;
    std::unique_ptr<Button> m_medium_attack_button;
    std::unique_ptr<Button> m_heavy_attack_button;
    GameTime* m_game_time_ptr;

  protected:
    void draw (sf::RenderTarget& target, sf::RenderStates states) const override {
      int max_exp_threshold = 5 * pow(m_hero_ptr->getLvl(), 2.2) + 25;
      m_exp_blue_rectangle_sprite->setScale({m_hero_ptr->getCurrentExp() / float(max_exp_threshold) * scale, scale});
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
        m_HP_potion_button->setTexture(m_lock_texture);
      if (m_hero_ptr->getLvl() < 4)
        m_regen_potion_button->setTexture(m_lock_texture);
      if (m_hero_ptr->getLvl() < 5)
        m_mana_potion_button->setTexture(m_lock_texture);
      if (m_hero_ptr->getLvl() < 8)
        m_fast_action_potion_button->setTexture(m_lock_texture);
      target.draw(*m_HP_potion_button, states);
      target.draw(*m_regen_potion_button, states);
      target.draw(*m_mana_potion_button, states);
      target.draw(*m_fast_action_potion_button, states);
      target.draw(*m_medium_attack_button, states);
      target.draw(*m_heavy_attack_button, states);
      target.draw(*m_light_attack_button, states);
    }

  public:
    HUD (Hero*& hero, GameTime* game_time): m_hero_ptr(hero), m_game_time_ptr(game_time) {
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
      m_top_hud_sprite->scale({scale, scale});
      if (!m_bottom_hud_texture.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png");
      }
      m_bottom_hud_sprite = std::make_unique<sf::Sprite>(m_bottom_hud_texture);
      m_bottom_hud_sprite->setPosition({0, scale * 318.f});
      m_bottom_hud_sprite->scale({scale, scale});
      if (!m_white_rectangle.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png");
      }
      m_exp_white_rectangle_sprite = std::make_unique<sf::Sprite>(m_white_rectangle);
      m_exp_white_rectangle_sprite->setPosition({scale * 259.f, scale * 16.f});
      m_exp_white_rectangle_sprite->scale({scale, scale});
      if (!m_blue_rectangle.loadFromFile("..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png")) {
        std::cerr << "Failed to load texture from file: " << "..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png" << std::endl;
        throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png");
      }
      m_exp_blue_rectangle_sprite = std::make_unique<sf::Sprite>(m_blue_rectangle);
      m_exp_blue_rectangle_sprite->setPosition({scale * 257.f, scale * 16.f});
      m_exp_blue_rectangle_sprite->scale({scale, scale});
      m_hp_text = std::make_unique<sf::Text>(m_font, "", int(scale * 16));
      m_mana_text = std::make_unique<sf::Text>(m_font, "", int(scale * 16));
      m_gold_text = std::make_unique<sf::Text>(m_font, "", int(scale * 16));
      this->m_time_text = std::make_unique<sf::Text>(m_font, "", int(scale * 16));
      m_hp_text->setPosition({scale * 323.f, scale * 324.f});
      m_mana_text->setPosition({scale * 323.f, scale * 338.f});
      m_gold_text->setPosition({scale * 63.f, scale * 3.f});
      this->m_time_text->setPosition({530 * scale, scale * 3.f});

      m_HP_potion_button = std::make_unique<Button>(481.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\hp_potion20x20.png");
      m_mana_potion_button = std::make_unique<Button>(515.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\mana_potion20x20.png");
      m_regen_potion_button = std::make_unique<Button>(549.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\regen_potion20x20.png");
      m_fast_action_potion_button = std::make_unique<Button>(583.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\potions\\action_potion20x20.png");
      if (m_hero_ptr->getClass() == "Warrior") {
        m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_heavy.png");
        m_light_attack_button = std::make_unique<Button>(37.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_weak.png");
        m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_normal.png");
      }
      else if (m_hero_ptr->getClass() == "Archer") {
        m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_strong.png");
        m_light_attack_button = std::make_unique<Button>(37.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_weak.png");
        m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_normal.png");
      }
      else if (m_hero_ptr->getClass() == "Mage") {
        m_heavy_attack_button = std::make_unique<Button>(105.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_strong.png");
        m_light_attack_button = std::make_unique<Button>(37.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_weak.png");
        m_medium_attack_button = std::make_unique<Button>(71.f, 332.f, "..\\src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_medium.png");
      }
      m_gold_text->setFillColor(sf::Color::Black);
      m_mana_text->setFillColor(sf::Color::Black);
      m_hp_text->setFillColor(sf::Color::Black);
      this->m_time_text->setFillColor(sf::Color::Black);
    }

    bool isHpPotionClicked (const sf::Vector2i& mouse_position);
    bool isManaPotionClicked (const sf::Vector2i& mouse_position);
    bool isRegenPotionClicked (const sf::Vector2i& mouse_position);
    bool isFastActionPotionClicked (const sf::Vector2i& mouse_position);
    bool isLightAtkClicked (const sf::Vector2i& mouse_position);
    bool isMediumAtkClicked (const sf::Vector2i& mouse_position);
    bool isHeavyAtkClicked (const sf::Vector2i& mouse_position);
};

#endif //HUD_H
