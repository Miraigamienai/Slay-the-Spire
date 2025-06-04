#pragma once

#include <memory>

#include "RUtil/Hitbox.hpp"//hb member

namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Button{
enum class MenuButtonType:int{
    play,
    info,
    stat,
    setting,
    patch_notes,
    quit
};
class Menu_button
{
public:
    Menu_button(MenuButtonType type, int index);
    ~Menu_button()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2, bool activate)const;
    bool Clicked()const noexcept(noexcept(hb.Clicked())){return hb.Clicked();}
    const MenuButtonType type;
private:
    RUtil::Hitbox hb;
    float x;
    float target_x;
    float highlight_a;

    static const std::shared_ptr<Draw::ReTexture> &HIGHLIGHT_IMG;
    static constexpr float FONTSIZE=32;
};
}