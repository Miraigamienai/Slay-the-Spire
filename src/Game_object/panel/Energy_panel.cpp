#include "Game_object/panel/Energy_panel.hpp"
#include "Game_object/energy_orb/Energy_orb.hpp"
#include "Game_object/energy_orb/Red_orb.hpp"
#include "Game_object/character/Player.hpp"
#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Refresh_energy_effect.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

#include "Util/Logger.hpp"

namespace Panel
{
    static inline std::shared_ptr<EnergyOrb::Energy_orb> GetOrb(Character::PlayerType player_type){
        switch(player_type){
            case Character::PlayerType::Ironclad:return std::make_shared<EnergyOrb::Red_orb>();
            default:return nullptr;
        }
    }

    template<Character::PlayerType player_type>
    static inline auto &GetVFXIMG(){
        if constexpr (player_type==Character::PlayerType::Ironclad){
            static auto&IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/energyRedVFX.png");
            return IMG;
        }
    }

    static inline auto &GetVFXIMG(Character::PlayerType player_type){
        switch(player_type){
            case Character::PlayerType::Ironclad:return GetVFXIMG<Character::PlayerType::Ironclad>();
            default:
                LOG_ERROR("Try to get error vfximg.");
                return GetVFXIMG<Character::PlayerType::Ironclad>();
        }
    }

    Energy_panel::Energy_panel()
        :Panels(198.0F*Setting::SCALE, 190.0F*Setting::SCALE, -480.0F*Setting::SCALE, 200.0F*Setting::SCALE, true),
        current_energy(0),
        max_energy(0),
        vfx_angle(0.0F),
        vfx_scale(Setting::SCALE),
        vfx_color_a(0.0F),
        vfx_timer(0.0F),
        font_scale(1.0F),
        current_player_type(Character::PlayerType::NONE),
        energy_orb(nullptr),
        vfx_img(nullptr){}

    void Energy_panel::update(Dungeon::Dungeon_shared &dungeon_shared){
        current_energy=dungeon_shared.player->GetCurrEnergy();
        max_energy=dungeon_shared.player->GetMaxEnergy();
        this->update_position();
        if(dungeon_shared.player!=nullptr){
            if(dungeon_shared.player->player_type!=current_player_type){
                current_player_type=dungeon_shared.player->player_type;
                energy_orb=GetOrb(current_player_type);
                vfx_img=GetVFXIMG(current_player_type);
            }
            if(energy_orb!=nullptr) energy_orb->update(current_energy);
            update_vfx();
        }else{
            current_player_type=Character::PlayerType::NONE;
        }
        font_scale=RUtil::Math::varlerp(font_scale,1.0F,8.0F,0.003F);
    }

    void Energy_panel::update_vfx(){
        if(vfx_timer!=0.0F){
            vfx_color_a=RUtil::Math::interpolation_exp10in(0.5F,0.0F,1.0F-vfx_timer/2.0F);
            vfx_angle-=RUtil::Game_Input::delta_time()*30.0F;
            vfx_scale=Setting::SCALE*RUtil::Math::interpolation_exp10in(1.0F,0.1F,1.0F-vfx_timer/2.0F);
            vfx_timer-=RUtil::Game_Input::delta_time();
            if(vfx_timer<0.0F){
                vfx_timer=0.0F;
                vfx_color_a=0.0F;
            }
        }
    }

    void Energy_panel::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(energy_orb!=nullptr)energy_orb->render(r2, current_energy, current_x, current_y);
        if(vfx_img!=nullptr) render_vfx(r2);
        m_font.render_center_with_bg(r2, std::to_string(current_energy)+"/"+std::to_string(max_energy), current_x, current_y, 0.0F, 0.0F, 0.0F, font_scale*Setting::SCALE, TEXTCOLOR, 1.0F);
    }

    void Energy_panel::render_vfx(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(vfx_timer!=0.0F){
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
            r2->SetColor(RUtil::WHITE, vfx_color_a);
            r2->draw(vfx_img, current_x-128.0F, current_y-128.0F, 256.0F, 256.0F, -vfx_angle+50.0F, 128.0F, 128.0F, vfx_scale, vfx_scale);
            r2->draw(vfx_img, current_x-128.0F, current_y-128.0F, 256.0F, 256.0F, vfx_angle, 128.0F, 128.0F, vfx_scale, vfx_scale);
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        }
    }
    
    void Energy_panel::on_add_energy(Effect::Effect_group&effs){
        effs.AddTop(std::make_shared<Effect::Refresh_energy_effect>(this->current_x,this->current_y));
        font_scale=2.0F;
        vfx_timer=2.0F;
    }

    const Draw::NumberDrawer Energy_panel::m_font{32, FontWeight::bold};
} // namespace Panel
