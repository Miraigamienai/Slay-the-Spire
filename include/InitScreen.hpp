#pragma once

#include <array>

#include "Game_object/button/Menu_button.hpp"
#include "InitScreenBackground.hpp"

//fwd decl
enum class State:int;

class InitScreen
{
public:
    InitScreen(State &state);
    ~InitScreen()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const;
    void update();
    void reset()noexcept{
        darken=false;
        fade_a=0.0F;
    }
private:
    InitScreenBackground bg;
    State &state;
    std::array<Button::Menu_button, static_cast<int>(Button::MenuButtonType::quit)+1> buttons;
    bool darken;
    float fade_a;
};