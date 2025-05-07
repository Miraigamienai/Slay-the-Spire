#pragma once

#include <memory>

#include "RUtil/Game_Input.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Dungeon{
namespace GridScreenAction{
class Render_arrow
{
public:
    Render_arrow()noexcept:oscillate_timer(0.0F){};
    virtual ~Render_arrow()=default;
    void arrow_update()noexcept(noexcept(RUtil::Game_Input::delta_time())){oscillate_timer+=RUtil::Game_Input::delta_time() * 2.0F;}
    void arrow_render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
private:
    float oscillate_timer;
    static const std::shared_ptr<Draw::ReTexture> &ARROW;

    static constexpr float START_X=static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - 73.0F*Setting::SCALE - 32.0F;
};
}
}