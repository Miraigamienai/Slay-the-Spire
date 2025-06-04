#pragma once

#include <memory>

#include "RUtil/Hitbox.hpp"//hb member
#include "RUtil/Some_Math.hpp"

namespace Draw{
    class Draw_2D;
    class Text_layout;
}

namespace Button{
class Return_to_start_button
{
public:
    Return_to_start_button();
    ~Return_to_start_button()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    bool Clicked()const noexcept(noexcept(hb.Clicked())){return hb.Clicked();}
    void set_text(const std::shared_ptr<Draw::Text_layout> &text)noexcept{this->text=text;}
    void move(float center_x, float center_y)noexcept(noexcept(hb.move(center_x, center_y))){hb.move(center_x, center_y);}
private:
    RUtil::Hitbox hb;
    std::shared_ptr<Draw::Text_layout> text;

    static constexpr Uint32 TEXT_NORMAL_COLOR=RUtil::Math::GetColorUint32_RGB(0.7F, 0.7F, 0.7F);
};
}