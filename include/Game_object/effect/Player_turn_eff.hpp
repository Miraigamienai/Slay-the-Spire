#pragma once

#include <string>

#include "Game_object/effect/Effects.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Player_turn_eff final:public Effects
{
public:
    Player_turn_eff(Uint32 dungeon_fade_color, int turn_num);
    ~Player_turn_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float current_h;
    const std::string turn_num;
    static const Draw::NumberDrawer s_turn_num_drawer;
    static constexpr float TARGET_H = 150.0F*Setting::SCALE;
    static constexpr float MAIN_MSG_OFFSET = 20.0F*Setting::SCALE;
    static constexpr float TURN_MSG_OFFSET = -30.0F*Setting::SCALE;
    static constexpr Uint32 TURN_MSG_COLOR = RUtil::Math::GetColorUint32_RGB(0.7F, 0.7F, 0.7F);
    static constexpr int TURN_NUM_FONT_SIZE=32;
};
}