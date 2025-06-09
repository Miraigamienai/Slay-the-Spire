#pragma once

#include <memory>

#include "Game_object/panel/Energy_panel.hpp"
#include "Game_object/button/End_turn_button.hpp"

//fwd decl
namespace Character{
    class Player;
}

namespace Dungeon{
class Overlay
{
public:
    Overlay()=default;
    ~Overlay()=default;

    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void hide_combat_panel();
    void show_combat_panel();

    void set_player_to_energy_panel(const std::shared_ptr<Character::Player>&player){energy_panel.set_player(player);}
    void on_use_energy()noexcept(noexcept(energy_panel.on_use_energy())){energy_panel.on_use_energy();}
    void on_add_energy(Effect::Effect_group&effs){energy_panel.on_add_energy(effs);}

    void render_black_screen(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void set_black_screen_a(float value)noexcept{black_screen_target_a=value;}
private:
    Panel::Energy_panel energy_panel;
    float black_screen_a=0.0F,black_screen_target_a=0.0F;
    void update_black_screen_a();
};
}