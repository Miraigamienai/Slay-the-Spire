#pragma once

#include <list>

#include "Game_object/panel/Panels.hpp"
#include "Game_object/effect/Discard_glow_eff.hpp"
#include "RUtil/Hitbox.hpp"
#include "Draw/NumberDrawer.hpp"

namespace Panel{
class Discard_pile_panel final:public Panels
{
public:
    Discard_pile_panel();
    ~Discard_pile_panel()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    bool is_logically_clicked()const noexcept(noexcept(hb.Clicked()) && noexcept(is_hide())){return hb.Clicked()&&!is_hide()&&click_timer==0.0F;}
    void SetClickTimer()noexcept{click_timer=CLICK_TIME;}
private:
    std::list<Effect::Discard_glow_eff> vfx_above, vfx_below;
    RUtil::Hitbox hb;
    float scale;
    float floaty_timer;
    float floaty_y;
    int discard_pile_size;
    float click_timer;

    template <typename vfx_type>
    inline void _update(vfx_type &vfx);

    static const Draw::NumberDrawer s_num_drawer;
    static constexpr float CLICK_TIME=0.5F;
};
}