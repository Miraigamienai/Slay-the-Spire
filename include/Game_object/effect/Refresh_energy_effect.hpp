#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Refresh_energy_effect final:public Effects
{
public:
    Refresh_energy_effect(const float &panel_x,const float &panel_y);
    ~Refresh_energy_effect()override=default;
    Refresh_energy_effect(const Refresh_energy_effect &) = delete;
    Refresh_energy_effect(Refresh_energy_effect &&) = delete;
    Refresh_energy_effect &operator=(const Refresh_energy_effect &) = delete;
    Refresh_energy_effect &operator=(Refresh_energy_effect &&) = delete;
    
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const float &panel_x,&panel_y;
};
} // namespace Effect