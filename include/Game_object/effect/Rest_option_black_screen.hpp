#pragma once

#include <SDL_stdinc.h>

#include "Game_object/effect/Effects.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
}

namespace Effect{
class Rest_option_black_screen final:public Effects
{
public:
    Rest_option_black_screen(Uint32 dungeon_fade_color);
    ~Rest_option_black_screen()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
};
}