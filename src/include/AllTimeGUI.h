#ifndef ALLTIMEGUI_H
#define ALLTIMEGUI_H
#include <gametime.h>
#include <SFML/Graphics.hpp>
#include "character.h"
#include "global.h"
#include "math.h"
#include "Button.h"
#include <string>

class AllTimeGUI: public sf::Drawable {
  private:
    sf::Texture blue;
    sf::Texture white;
    sf::Texture lock;
    std::unique_ptr<sf::Text> gold;
    std::unique_ptr<sf::Text> time;
    std::unique_ptr<sf::Text> hp;
    std::unique_ptr<sf::Text> mana;
    std::unique_ptr<sf::Sprite> expWhite;
    std::unique_ptr<sf::Sprite> expBlue;
    sf::Font font;
    sf::Texture top;
    sf::Texture bottom;
    std::unique_ptr<sf::Sprite> guiTop;
    std::unique_ptr<sf::Sprite> guiBottom;
    character* main;
    std::unique_ptr<Button> hppotion;
    std::unique_ptr<Button> manapotion;
    std::unique_ptr<Button> regenpotion;
    std::unique_ptr<Button> actionpotion;
    std::unique_ptr<Button> light;
    std::unique_ptr<Button> medium;
    std::unique_ptr<Button> heavy;
    GameTime* game_time;

  protected:
    void draw (sf::RenderTarget& target, sf::RenderStates states) const override {
      int maxexp = 5 * pow(main->stat.lvl, 2.2) + 25;
      expBlue->setScale({main->exp / float(maxexp) * scale, scale});
      hp->setString(std::to_string(main->currenthp) + "/" + std::to_string(main->stat.basehp));
      mana->setString(std::to_string(main->currentmana) + "/" + std::to_string(main->stat.mana));
      gold->setString(std::to_string(main->currentgold));
      std::string timeString = (game_time->gettime().x < 10? "0" : "") + std::to_string(game_time->gettime().x) + ":" +
                               (game_time->gettime().y < 10? "0" : "") + std::to_string(game_time->gettime().y);
      time->setString(timeString);
      target.draw(*expWhite);
      target.draw(*expBlue);
      target.draw(*guiTop, states);
      target.draw(*guiBottom, states);
      target.draw(*hp, states);
      target.draw(*mana, states);
      target.draw(*gold, states);
      target.draw(*time, states);
      if (main->getLvl() < 2)
        hppotion->setTexture(lock);
      if (main->getLvl() < 4)
        regenpotion->setTexture(lock);
      if (main->getLvl() < 5)
        manapotion->setTexture(lock);
      if (main->getLvl() < 8)
        actionpotion->setTexture(lock);
      target.draw(*hppotion, states);
      target.draw(*regenpotion, states);
      target.draw(*manapotion, states);
      target.draw(*actionpotion, states);
      target.draw(*medium, states);
      target.draw(*heavy, states);
      target.draw(*light, states);
    }

  public:
    AllTimeGUI (character*& hero, GameTime* time): main(hero), game_time(time) {
      if (!font.openFromFile("src\\fonts\\pixel-8x8.ttf")) {
        std::cerr << "Failed to load font from file: " << "src\\fonts\\pixel-8x8.ttf" << std::endl;
        throw std::runtime_error("Failed to load font from file: src\\fonts\\pixel-8x8.ttf");
      }
      if (!top.loadFromFile("src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png" <<
            std::endl;
        throw std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\AllTimeGui\\gui_topscreen.png");
      }
      if (!lock.loadFromFile("src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png")) {
        std::cerr << "Failed to load texture from file: " <<
            "src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png" << std::endl;
        throw
            std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\AllTimeGui\\potions\\gui_lock20x20.png");
      }
      guiTop = std::make_unique<sf::Sprite>(top);
      guiTop->setPosition({0, 0});
      guiTop->scale({scale, scale});
      if (!bottom.loadFromFile("src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png")) {
        std::cerr << "Failed to load texture from file: " << "src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png" <<
            std::endl;
        throw
            std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\AllTimeGui\\gui_bottomscreen.png");
      }
      guiBottom = std::make_unique<sf::Sprite>(bottom);
      guiBottom->setPosition({0, scale * 318.f});
      guiBottom->scale({scale, scale});
      if (!white.loadFromFile("src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png")) {
        std::cerr << "Failed to load texture from file: " <<
            "src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png" << std::endl;
        throw
            std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_white.png");
      }
      expWhite = std::make_unique<sf::Sprite>(white);
      expWhite->setPosition({scale * 259.f, scale * 16.f});
      expWhite->scale({scale, scale});
      if (!blue.loadFromFile("src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png")) {
        std::cerr << "Failed to load texture from file: " <<
            "src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png" << std::endl;
        throw
            std::runtime_error("Failed to load texture from file: src\\textures\\GUI\\AllTimeGui\\rectangles\\gui_exp_rect_blue.png");
      }
      expBlue = std::make_unique<sf::Sprite>(blue);
      expBlue->setPosition({scale * 257.f, scale * 16.f});
      expBlue->scale({scale, scale});
      hp = std::make_unique<sf::Text>(font, main->currenthp + "/" + main->stat.basehp, int(scale * 16));
      mana = std::make_unique<sf::Text>(font, main->currentmana + "/" + main->stat.mana, int(scale * 16));
      gold = std::make_unique<sf::Text>(font, "" + main->currentgold, int(scale * 16));
      this->time = std::make_unique<sf::Text>(font, main->currenthp + "/" + main->stat.basehp, int(scale * 16));
      hp->setPosition({scale * 323.f, scale * 324.f});
      mana->setPosition({scale * 323.f, scale * 338.f});
      gold->setPosition({scale * 63.f, scale * 3.f});
      this->time->setPosition({530 * scale, scale * 3.f});

      hppotion = std::make_unique<Button>(481.f, 332.f, "src\\textures\\GUI\\AllTimeGui\\potions\\hp_potion20x20.png");
      manapotion = std::make_unique<Button>(515.f, 332.f,
                                            "src\\textures\\GUI\\AllTimeGui\\potions\\mana_potion20x20.png");
      regenpotion = std::make_unique<Button>(549.f, 332.f,
                                             "src\\textures\\GUI\\AllTimeGui\\potions\\regen_potion20x20.png");
      actionpotion = std::make_unique<Button>(583.f, 332.f,
                                              "src\\textures\\GUI\\AllTimeGui\\potions\\action_potion20x20.png");
      if (main->getClass() == "Warrior") {
        heavy = std::make_unique<Button>(105.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_heavy.png");
        light = std::make_unique<Button>(37.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_weak.png");
        medium = std::make_unique<Button>(71.f, 332.f,
                                          "src\\textures\\GUI\\AllTimeGui\\attacks\\warrior\\warrior_NA_normal.png");
      }
      else if (main->getClass() == "Archer") {
        heavy = std::make_unique<Button>(105.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_strong.png");
        light = std::make_unique<Button>(37.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_weak.png");
        medium = std::make_unique<Button>(71.f, 332.f,
                                          "src\\textures\\GUI\\AllTimeGui\\attacks\\archer\\archer_NA_normal.png");
      }
      else if (main->getClass() == "Mage") {
        heavy = std::make_unique<Button>(105.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_strong.png");
        light = std::make_unique<Button>(37.f, 332.f,
                                         "src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_weak.png");
        medium = std::make_unique<Button>(71.f, 332.f,
                                          "src\\textures\\GUI\\AllTimeGui\\attacks\\mage\\mage_NA_medium.png");
      }
      gold->setFillColor(sf::Color::Black);
      mana->setFillColor(sf::Color::Black);
      hp->setFillColor(sf::Color::Black);
      this->time->setFillColor(sf::Color::Black);
    }

    bool hpIsClicked (const sf::Vector2i& mousePos);
    bool manaIsClicked (const sf::Vector2i& mousePos);
    bool regenIsClicked (const sf::Vector2i& mousePos);
    bool actionIsClicked (const sf::Vector2i& mousePos);
    bool atk1IsClicked (const sf::Vector2i& mousePos);
    bool atk2IsClicked (const sf::Vector2i& mousePos);
    bool atk3IsClicked (const sf::Vector2i& mousePos);
};

#endif //ALLTIMEGUI_H
