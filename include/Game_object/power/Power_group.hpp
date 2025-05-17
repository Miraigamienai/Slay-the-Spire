#pragma once

#include <list>
#include <memory>

#include "Game_object/Group_template.hpp"
#include "Game_object/effect/Effect_group.hpp"

//fwd decl
namespace Power{
    class Powers;
}
namespace Draw{
    class Draw_2D;
}

namespace Power
{
class Power_group final:public Template::Group_template<std::list<std::shared_ptr<Powers>>>
{
public:
    Power_group()=default;
    ~Power_group()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void update();
private:
    Effect::Effect_group power_effs;
};
} // namespace Power
