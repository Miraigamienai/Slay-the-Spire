#pragma once

#include "Game_object/energy_orb/Energy_orb.hpp"

namespace EnergyOrb{
class Red_orb final:public Energy_orb
{
public:
    Red_orb():angle(){}
    ~Red_orb()override=default;
    void update(float energy) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2, float energy, float panel_x, float panel_y)const override;
private:
    float angle[5]={0.0F};
    static constexpr float ANGLE_SLOW[]={72.0F,8.0F,-8.0F,5.0F,-5.0F};
    static constexpr float ANGLE_QUICK[]={360.0F,40.0F,-40.0F,20.0F,-20.0F};
    static const std::shared_ptr<Draw::ReTexture> &slow1,&slow2,&slow3,&slow4,&slow5,
                                                  &quick1,&quick2,&quick3,&quick4,&quick5,
                                                  &layer6;
};
}