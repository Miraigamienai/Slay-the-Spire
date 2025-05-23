#pragma once

#include <glm/vec3.hpp>

#include "Game_object/effect/Effects.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace RUtil{
    enum class Powers_Text_ID:int;
}

namespace Effect{
class Power_buff_debuff_eff final:public Effects
{
public:
    Power_buff_debuff_eff(float x, float y, RUtil::Powers_Text_ID power_id, int amount, glm::vec3 target_rgb)noexcept(noexcept(common_setting()))
        :x(x),
        y(y),
        offset_y(START_OFFSET_Y),
        current_rgb(255, 255, 255),
        target_rgb(target_rgb),
        with_number(true),
        number(amount),
        power_id(power_id)
    {
        common_setting();
    }
    Power_buff_debuff_eff(float x, float y, RUtil::Powers_Text_ID power_id, glm::vec3 target_rgb)noexcept(noexcept(common_setting()))
        :x(x),
        y(y),
        offset_y(START_OFFSET_Y),
        current_rgb(255, 255, 255),
        target_rgb(target_rgb),
        with_number(false),
        number(0),
        power_id(power_id)
    {
        common_setting();
    }
    ~Power_buff_debuff_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    float x,y;
    float offset_y;
    glm::vec3 current_rgb;
    glm::vec3 target_rgb;
    const bool with_number;
    const int number;
    const RUtil::Powers_Text_ID power_id;

    void common_setting()noexcept{
        this->duration = DUR;
        this->color_a=1.0F;
    }
    static Draw::NumberDrawer s_number_drawer;
    static constexpr float START_OFFSET_Y = 60.0F * Setting::SCALE,
                           TARGET_OFFSET_Y = 100.0F * Setting::SCALE,
                           DUR = 2.0F;
    static constexpr int FONT_SIZE = 36;
};
}