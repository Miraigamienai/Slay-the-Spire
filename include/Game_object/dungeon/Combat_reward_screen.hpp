#pragma once

#include <vector>
#include <memory>

#include "Game_object/interface/Is_screen.hpp"
#include "Game_object/button/Proceed_button.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
}
namespace Reward{
    class Reward_item;
}

namespace Dungeon{
class Combat_reward_screen final:public Interface::Is_screen
{
public:
    Combat_reward_screen();
    ~Combat_reward_screen()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Dungeon::Dungeon_shared &dungeon_shared);
private:
    Button::Proceed_button proceed_button;
    int now_reward_pos;
    float open_timer;
    float color_rgb;
    bool took_all;
    std::vector<std::shared_ptr<Reward::Reward_item>> reward_items;
    static const std::shared_ptr<Draw::ReTexture>&SHEET;
    static constexpr float OPENTIMER=0.2F;
};
}
