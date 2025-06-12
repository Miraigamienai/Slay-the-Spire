#include "Game_object/panel/Discard_pile_panel.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Panel{

    static SETTING_CONSTEXPR float HITBOX_W = 120.0F * Setting::SCALE;
    static SETTING_CONSTEXPR float FLOATY_DIST = 5.0F * Setting::SCALE;
    static SETTING_CONSTEXPR float DECK_X = 180.0F * Setting::SCALE - 64.0F;
    static SETTING_CONSTEXPR float DECK_Y = 70.0F * Setting::SCALE - 64.0F;
    static SETTING_CONSTEXPR float NUM_OFFSET_X = 134.0F * Setting::SCALE;
    static SETTING_CONSTEXPR float NUM_OFFSET_Y = 48.0F * Setting::SCALE;
      
    Discard_pile_panel::Discard_pile_panel()
        :Panels(static_cast<float>(Setting::WINDOW_WIDTH) - 256.0F*Setting::SCALE, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), -300.0F*Setting::SCALE, true),
        hb(static_cast<float>(Setting::WINDOW_WIDTH)-HITBOX_W, 0.0F, HITBOX_W, HITBOX_W),
        scale(Setting::SCALE),
        floaty_timer(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        floaty_y(std::sin(floaty_timer) * FLOATY_DIST),
        discard_pile_size(0),
        click_timer(0.0F){}

    
    template <typename vfx_type>
    inline void Discard_pile_panel::_update(vfx_type &vfx){
        for (auto it = vfx.begin(); it != vfx.end();) {
            (*it).set_offset(current_x - 1664.0F*Setting::SCALE, current_y+floaty_y*0.5F);
            (*it).update();
            if ((*it).IsDone())it = vfx.erase(it);
            else ++it;
        }
    }

    void Discard_pile_panel::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(click_timer>0.0F){
            click_timer-=RUtil::Game_Input::delta_time();
            if(click_timer<0.0F) click_timer=0.0F;
        }
        discard_pile_size=dungeon_shared.card_group_handler.size<Card::GroupType::m_discard>();
        this->update_position();
        floaty_timer+=RUtil::Game_Input::delta_time();
        floaty_y=std::sin(floaty_timer) * FLOATY_DIST;
        _update(vfx_above);
        _update(vfx_below);
        if(vfx_above.size()<9) vfx_above.emplace_back(true);
        if(vfx_below.size()<9) vfx_below.emplace_back(false);
        scale = RUtil::Math::varlerp(scale, Setting::SCALE, 8.0F, 0.003F);
        hb.update();
        if(hb.Hovered() && !is_hide()){
            scale = 1.2F*Setting::SCALE;
        }
    }

    void Discard_pile_panel::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //vfx below
        for(const auto&it:vfx_below) it.render(r2);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //img
        r2->SetColor(RUtil::WHITE);
        static const auto img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/discardButton/base.png"); 
        r2->draw(img, current_x+DECK_X, current_y+DECK_Y+floaty_y*0.5F, 128.0F, 128.0F, 0.0F, 64.0F, 64.0F, scale, scale);
        //vfx above
        for(const auto&it:vfx_above) it.render(r2);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //number
        s_num_drawer.render_center_with_bg(r2, std::to_string(discard_pile_size), current_x+NUM_OFFSET_X, current_y+NUM_OFFSET_Y, 0.0F, 0.0F, 0.0F, Setting::SCALE, RUtil::WHITE, 1.0F);
    }

    const Draw::NumberDrawer Discard_pile_panel::s_num_drawer{32, FontWeight::bold};
}