#pragma once

#include "Game_object/effect/Effects.hpp"
#include "RUtil/Some_Math.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
}

namespace Effect{
class block_broken_eff final:public Effects
{
public:
    block_broken_eff(float x, float y)noexcept
        :x(x-32.0F), y(y-32.0F),
        offset_x(0.0F), offset_y(0.0F),
        angle(0.0F)
    {
        this->duration=DUR;
        this->color_a=1.0F;
    }
    ~block_broken_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const float x, y;
    float offset_x, offset_y;
    float angle;
    static const std::shared_ptr<Draw::ReTexture> &BLOCK_L_IMG, &BLOCK_R_IMG;
    static constexpr float DUR=1.1F;
    static constexpr Uint32 COLOR=RUtil::Math::GetColorUint32_RGB(0.6F, 0.93F, 0.98F);
};
}