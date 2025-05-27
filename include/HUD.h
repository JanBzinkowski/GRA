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
    float m_scale=1.f;
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
    void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

  public:
    HUD (Hero*& hero, GameTime* game_time, sf::RenderWindow*& window);

    bool isHpPotionClicked (const sf::Vector2i& mouse_position);
    bool isManaPotionClicked (const sf::Vector2i& mouse_position);
    bool isRegenPotionClicked (const sf::Vector2i& mouse_position);
    bool isFastActionPotionClicked (const sf::Vector2i& mouse_position);
    bool isLightAtkClicked (const sf::Vector2i& mouse_position);
    bool isMediumAtkClicked (const sf::Vector2i& mouse_position);
    bool isHeavyAtkClicked (const sf::Vector2i& mouse_position);
};

#endif //HUD_H
