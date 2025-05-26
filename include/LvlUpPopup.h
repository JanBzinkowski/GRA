#ifndef LVLUPPOPUP_H
#define LVLUPPOPUP_H

#include "Hero.h"
#include "Options.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"

class LvlUpPopup: public sf::Drawable {
  private:
    Hero* m_hero;
    Options m_options;
    std::unique_ptr<sf::Texture> m_background_texture;
    std::unique_ptr<sf::Sprite> m_sprite;
    std::vector<std::unique_ptr<sf::Text>> m_texts;
    sf::Font m_font;

  protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  public:
    LvlUpPopup(Hero*& hero, sf::Font& font, Options& options, sf::RenderWindow*& window);
    void updateText(sf::RenderWindow*& window, bool stats = false);

};

#endif //LVLUPPOPUP_H
