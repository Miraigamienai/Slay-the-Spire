#pragma once

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

enum class AttackType:int;

namespace Effect{
class Flash_attack_effect final:public Effects,public Abstraction::Reusable<Flash_attack_effect>
{
public:
    Flash_attack_effect(const float x,const float y,const AttackType type)noexcept(noexcept(this->Initial(x,y,type))){this->Initial(x,y,type);}
    ~Flash_attack_effect()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(const float x,const float y,const AttackType type);
private:
    float x,y;
    float start_y,target_y;
    float rotation;
    AttackType type;
    static constexpr float DUR=0.6F;
};
}