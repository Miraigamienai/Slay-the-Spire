#pragma once

#include "Game_object/effect/Effects.hpp"

namespace Effect{
class Intense_zoom_particle final:public Effects
{
public:
    Intense_zoom_particle(float x, float y);
    ~Intense_zoom_particle()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    const int img_type;
    const float x, y;
    float offset_x;
    float length_x, length_y;
    float angle;
    float call_randomize_timer;
    
    void randomize();
    static constexpr float DUR=1.5F;
};
}
