#pragma once

#include <vector>

#include "Game_object/effect/Effects.hpp"

//fwd decl
namespace Draw{
    class Text_layout;
}

namespace Effect{
//TODO: this class
class Battle_start_eff final:public Effects
{
public:
    Battle_start_eff(){};
    ~Battle_start_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override{};
    void update() override{};
private:
public:
    static constexpr int FONTSIZE=72;
};
}