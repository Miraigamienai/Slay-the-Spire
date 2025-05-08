#pragma once

#include "Game_object/effect/Effects.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Shine_particle:public Effects
{
public:
    Shine_particle(float x, float y,float jitter);
    ~Shine_particle()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
private:
    bool img_bool;
    float x,y;
    float angle;
    float speed_x,speed_y;
    float floor;
    static constexpr float GRAVITY=3000.0F*Setting::SCALE;
};
}
