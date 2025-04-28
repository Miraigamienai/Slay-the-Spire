#pragma once

#include <memory>

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

//fwd decl
namespace Draw{
    class Atlas_Region;
}

namespace Effect{
class Card_proof_particle final:public Effects,public Interface::Reusable<Card_proof_particle>
{
public:
    Card_proof_particle(const float x,const float y){Initial(x,y);}
    ~Card_proof_particle()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(const float x,const float y);
private:
    bool flip_x,flip_y;
    float delay_time;
    float x,y, rotation;
    float rotate_speed, x_speed, y_speed;
    const std::shared_ptr<Draw::Atlas_Region>* img;
    static const std::shared_ptr<Draw::Atlas_Region> &SMOKE1,&SMOKE2,&SMOKE3;
    static constexpr float DUR=0.6F;
};
}