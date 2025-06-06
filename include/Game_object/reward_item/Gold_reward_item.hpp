#pragma once

#include <SDL_stdinc.h>

#include "Game_object/reward_item/Reward_item.hpp"

namespace Reward{
class Gold_reward_item final:public Reward_item
{
public:
    Gold_reward_item(int gold_amount);
    ~Gold_reward_item()override=default;
    void child_render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void child_render_text(const std::shared_ptr<Draw::Draw_2D> &r2, Uint32 color)const override;
    void take_reward(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    const int gold_amt;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}