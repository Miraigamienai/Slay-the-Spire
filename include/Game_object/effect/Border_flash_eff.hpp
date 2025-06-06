#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Border_flash_eff final:public Effects
{
public:
    Border_flash_eff(Uint32 color);
    ~Border_flash_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    static constexpr float DUR=1.0F;
};
}
