#pragma once

#include "Game_object/effect/Effects.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Enemy_turn_eff final:public Effects
{
public:
    Enemy_turn_eff(Uint32 dungeon_fade_color);
    ~Enemy_turn_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float current_h;
    static constexpr float TARGET_H = 150.0F*Setting::SCALE;
};
}