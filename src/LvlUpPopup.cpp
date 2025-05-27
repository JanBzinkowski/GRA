#include "LvlUpPopup.h"
#include "TextCentering.h"

LvlUpPopup::LvlUpPopup(Hero*& hero, sf::Font& font, Options& options, sf::RenderWindow*& window): m_hero(hero), m_font(font), m_options(options) {
  m_background_texture = std::make_unique<sf::Texture>();
  if (!m_background_texture->loadFromFile("..\\src\\textures\\GUI\\lvlupframe.png")) {
    std::cerr << "Failed to load texture from file: ..\\src\\textures\\GUI\\lvlupframe.png\n";
    throw std::runtime_error("Failed to load texture from file: ..\\src\\textures\\GUI\\lvlupframe.png");
  }
  m_sprite = std::make_unique<sf::Sprite>(*m_background_texture);
  sf::FloatRect bounds = m_sprite->getLocalBounds();
  m_sprite->setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
  m_sprite->setPosition({window->getSize().x/2.f, window->getSize().y/2.f});
  m_sprite->scale({scale, scale});
}

void LvlUpPopup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*m_sprite, states);
  for(int i = 0; i < m_texts.size(); i++) {
    target.draw(*m_texts[i], states);
  }
}

void LvlUpPopup::updateText(sf::RenderWindow*& window, bool stats) {
  std::string lvlup;
  m_texts.clear();
  if(!stats) {
    if(m_options.getLanguage() == Language::ENG) {
      lvlup += "Congratulations!\nYou have reached LVL:";
    }
    else if(m_options.getLanguage() == Language::PL) {
      lvlup += "Gratulacje!\nOsiągnąłeś LVL:";
    }
    lvlup += "\n\n";
    if (m_hero->getLvl() == 2) {
      if(m_options.getLanguage() == Language::ENG) {
        lvlup += "You have unlocked:\nInstant Health Potion\nAbilities";
      }
      else if(m_options.getLanguage() == Language::PL) {
        lvlup += "Odblokowałeś(aś):\nMikstura Natychmiastowego Zdrowia\nUmiejętności";
      }
    }
    if (m_hero->getLvl() == 4) {
      if(m_options.getLanguage() == Language::ENG) {
        lvlup += "You have unlocked:\nPotion of Regeneration";
      }
      else if(m_options.getLanguage() == Language::PL) {
        lvlup += "Odblokowałeś(aś):\nMikstura Regeneracji";
      }
    }
    if (m_hero->getLvl() == 5) {
      if(m_options.getLanguage() == Language::ENG) {
        lvlup += "You have unlocked:\nPotion of Mana Regeneration";
      }
      else if(m_options.getLanguage() == Language::PL) {
        lvlup += "Odblokowałeś(aś):\nMikstura Regeneracji Many";
      }
    }
    if (m_hero->getLvl() == 8) {
      if(m_options.getLanguage() == Language::ENG) {
        lvlup += "You have unlocked:\nPotion of Fast Action";
      }
      else if(m_options.getLanguage() == Language::PL) {
        lvlup += "Odblokowałeś(aś):\nMikstura Dodatkowej Akcji";
      }
    }

    m_texts.push_back(std::make_unique<sf::Text>(m_font, std::to_string(m_hero->getLvl()), 32*scale));
    sf::FloatRect bounds = m_texts[0]->getLocalBounds();
    m_texts[0]->setOrigin({bounds.size.x / 2.0f, 0.f});
    m_texts[0]->setPosition({window->getSize().x/2.f, window->getSize().y/2.f-3*scale});
    TextCentering::textCentering(m_texts, lvlup, m_font, 16*scale, {window->getSize().x/2.f, window->getSize().y/2.f-28.f*scale});
  }
  else {
    Stats stats = m_hero->getStats();
    StatsIncrese inc_stats = m_hero->getStatsInc();
    if(m_options.getLanguage() == Language::ENG) {
      lvlup += "Current Stats:\n";
    }
    else if(m_options.getLanguage() == Language::PL) {
      lvlup += "Obecne Statystyki:\n";
    }
    lvlup += std::to_string(stats.base_hp-inc_stats.base_HP_inc) + "(+" + std::to_string(inc_stats.base_HP_inc) + ") HP\n";
    lvlup += std::to_string(stats.ad-inc_stats.ad_inc) + "(+" + std::to_string(inc_stats.ad_inc) + ") AD\n";
    lvlup += std::to_string(stats.def-inc_stats.def_inc) + "(+" + std::to_string(inc_stats.def_inc) + ") DEF\n";
    lvlup += std::to_string(stats.mana-inc_stats.mana_inc) + "(+" + std::to_string(inc_stats.mana_inc) + ") Mana\n";
    lvlup += std::to_string(stats.speed-inc_stats.speed_inc) + "(+" + std::to_string(inc_stats.speed_inc) + ") Speed\n";
    TextCentering::textCentering(m_texts, lvlup, m_font, 16*scale, {window->getSize().x/2.f, window->getSize().y/2.f-28.f*scale});
  }
}