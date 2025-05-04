#pragma once

#include <SDL_stdinc.h>

#include "Game_object/reward_item/Reward_item.hpp"
#include "Game_object/reward_item/Card_reward.hpp"

namespace Reward{
class Card_reward_item final:public Reward_item
{
public:
    Card_reward_item(const std::vector<std::shared_ptr<Card::Cards>>&cards,Uint32 PlayerColor_RGB);
    ~Card_reward_item()override=default;
    void child_render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void child_render_text(const std::shared_ptr<Draw::Draw_2D> &r2, Uint32 color)const override;
    void take_reward(Dungeon::Dungeon_shared &dungeon_shared)override;
private:
    Uint32 PlayerColor_RGB;
    Reward::Card_reward card_reward;
    static const std::shared_ptr<Draw::ReTexture> &NORMAL_IMG;
};
}