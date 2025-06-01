#pragma once

#include <memory>

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

namespace Effect{
class Card_proof_particle final:public Effects,public Abstraction::Reusable<Card_proof_particle>
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
    int img_type;
    static constexpr float DUR=0.6F;
};
}