#pragma once

#include "Game_object/effect/Effects.hpp"
#include "RUtil/Some_Math.hpp"//RGB

//fwd decl
namespace Draw{
    class Atlas_Region;
}

namespace Effect{
class Card_flash final:public Effects
{
public:
    Card_flash(const std::shared_ptr<Draw::Atlas_Region>&silhouette,const float &card_x,const float &card_y,const float &card_angle,const float &card_scale,const bool quick_end=false);
    ~Card_flash()override=default;
    void change_color(const Uint32 color,const bool is_super_flash=false)noexcept{
        this->color=color;
        this->scale=0.0F;
        this->duration=0.5F;
        this->is_done=false;
        this->is_super_flash=is_super_flash;
    }
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private: 
    const float&card_x,&card_y;
    const float&card_angle,&card_scale;
    bool is_super_flash;
    const std::shared_ptr<Draw::Atlas_Region> &img;

    static const std::shared_ptr<Draw::Atlas_Region>&IMG_FLASH;
    static constexpr Uint32 DFAULT_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.8F,0.2F);
};
}