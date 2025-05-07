#pragma once

#include <SDL_stdinc.h>
#include <memory>
#include <vector>

#include "WindowSize.hpp"

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
}
namespace Draw{
    class Draw_2D;
}

namespace Room{
namespace Option{
//fwd decl
class Options;

class Option_handler
{
public:
    Option_handler(const Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color);
    ~Option_handler()=default;
    
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update();
    bool someone_be_clicked()const noexcept{return now_clicked_opts_pos!=-1;}

private:
    std::vector<std::shared_ptr<Options>> opts;
    int now_clicked_opts_pos;//default -1
    void set_opts_pos();
    static constexpr float BUTTON_START_X = static_cast<float>(Setting::WINDOW_WIDTH) * 0.416F,
                           BUTTON_START_Y = static_cast<float>(Setting::WINDOW_HEIGHT) / 2.0F + 180.0F * Setting::SCALE,
                           BUTTON_SPACING_X = 300.0F * Setting::SCALE,
                           BUTTON_SPACING_Y = -200.0F * Setting::SCALE,
                           BUTTON_EXTRA_SPACING_Y = -70.0F * Setting::SCALE;
};
}
}
