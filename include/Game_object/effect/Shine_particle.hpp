#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"
#include "WindowSize.hpp"

namespace Effect{
class Shine_particle:public Effects,public Interface::Reusable<Shine_particle>
{
public:
    Shine_particle(float x, float y,float jitter){Initial(color,x,y);}
    ~Shine_particle()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(float x, float y,float jitter);
private:
    float x,y;
    float angle;
    float speed_x,speed_y;
    float floor;
    bool img_bool;
    static constexpr float GRAVITY=3000.0F*Setting::SCALE;
};
}
