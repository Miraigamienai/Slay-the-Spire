#include <array>

#include "Game_object/card/Cards.hpp"//the hpp
#include "Game_object/effect/Card_glow_border.hpp"//eff
#include "Game_object/dungeon/Dungeon_shared.hpp"//get current situation for cheking if it is usable.
#include "Game_object/character/Player.hpp"//for energy check
#include "RUtil/Game_Input.hpp"//delat time & cursor pos
#include "RUtil/All_Image.hpp"//loading img
#include "RUtil/Text_Vector_Reader.hpp"//ui text reader
#include "RUtil/Cards_Text_Reader.hpp"//card text
#include "Draw/Atlas_Region.hpp"//img
#include "Draw/Text_layout.hpp"//ui text
#include "Draw/Draw_2D.hpp"//for rendering
#include "Game_object/power/Power_group.hpp"//calculate display damage
#include "Game_object/power/Powers.hpp"//calculate display damage

#include "Util/Logger.hpp"

namespace Card{
    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }

    static constexpr std::array<RUtil::AtlasRegionID, 6> energy_id_convert=[]()constexpr{
        std::array<RUtil::AtlasRegionID, 6>temp{};
        temp[static_cast<int>(Color::red)] = RUtil::AtlasRegionID::_512_card_red_orb;
        temp[static_cast<int>(Color::green)] = RUtil::AtlasRegionID::_512_card_green_orb;
        temp[static_cast<int>(Color::blue)] = RUtil::AtlasRegionID::_512_card_blue_orb;
        temp[static_cast<int>(Color::purple)] = RUtil::AtlasRegionID::_512_card_purple_orb;
        temp[static_cast<int>(Color::colorless)] = RUtil::AtlasRegionID::_512_card_colorless_orb;
        temp[static_cast<int>(Color::curse)] = RUtil::AtlasRegionID::_512_card_colorless_orb;
        return temp;
    }();

    static constexpr std::array<RUtil::AtlasRegionID, 5> bg_silhouette_id_convert = []() constexpr {
        std::array<RUtil::AtlasRegionID, 5> temp{};
        temp[static_cast<int>(Type::attack)] = RUtil::AtlasRegionID::_512_bg_attack_silhouette;
        temp[static_cast<int>(Type::power)] = RUtil::AtlasRegionID::_512_bg_power_silhouette;
        temp[static_cast<int>(Type::skill)] = RUtil::AtlasRegionID::_512_bg_skill_silhouette;
        temp[static_cast<int>(Type::status)] = RUtil::AtlasRegionID::_512_bg_skill_silhouette;
        temp[static_cast<int>(Type::curse)] = RUtil::AtlasRegionID::_512_bg_skill_silhouette;
        return temp;
    }();

    static constexpr std::array<std::array<RUtil::AtlasRegionID, 6>, 5> card_bg_convert = []() constexpr {
        std::array<std::array<RUtil::AtlasRegionID, 6>, 5> temp{};
        //attack
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::red)]       = RUtil::AtlasRegionID::_512_bg_attack_red;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::green)]     = RUtil::AtlasRegionID::_512_bg_attack_green;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::blue)]      = RUtil::AtlasRegionID::_512_bg_attack_blue;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::purple)]    = RUtil::AtlasRegionID::_512_bg_attack_purple;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::colorless)] = RUtil::AtlasRegionID::_512_bg_attack_gray;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Color::curse)]     = RUtil::AtlasRegionID::_512_bg_skill_black;
        //power    
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::red)]       = RUtil::AtlasRegionID::_512_bg_power_red;
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::green)]     = RUtil::AtlasRegionID::_512_bg_power_green;
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::blue)]      = RUtil::AtlasRegionID::_512_bg_power_blue;
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::purple)]    = RUtil::AtlasRegionID::_512_bg_power_purple;
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::colorless)] = RUtil::AtlasRegionID::_512_bg_power_gray;
        temp[static_cast<int>(Type::power)][static_cast<int>(Color::curse)]     = RUtil::AtlasRegionID::_512_bg_skill_black;
        //skill
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::red)]       = RUtil::AtlasRegionID::_512_bg_skill_red;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::green)]     = RUtil::AtlasRegionID::_512_bg_skill_green;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::blue)]      = RUtil::AtlasRegionID::_512_bg_skill_blue;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::purple)]    = RUtil::AtlasRegionID::_512_bg_skill_purple;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::colorless)] = RUtil::AtlasRegionID::_512_bg_skill_gray;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Color::curse)]     = RUtil::AtlasRegionID::_512_bg_skill_black;
        //other
        temp[static_cast<int>(Type::curse)] = temp[static_cast<int>(Type::status)] = temp[static_cast<int>(Type::skill)];
        return temp;
    }();

    static constexpr std::array<std::array<RUtil::AtlasRegionID, 6>, 5> card_frame_convert = []() constexpr {
        std::array<std::array<RUtil::AtlasRegionID, 6>, 5> temp{};
        //attack
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::rare)]     = RUtil::AtlasRegionID::_512_frame_attack_rare;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::uncommon)] = RUtil::AtlasRegionID::_512_frame_attack_uncommon;
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::common)]   =
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::basic)]    =
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::special)]  =
        temp[static_cast<int>(Type::attack)][static_cast<int>(Rarity::curse)]    = RUtil::AtlasRegionID::_512_frame_attack_common;
        //power    
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_frame_power_rare;
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_frame_power_uncommon;
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Type::power)][static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_frame_power_common;
        //skill
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_frame_skill_rare;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_frame_skill_uncommon;
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Type::skill)][static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_frame_skill_common;
        //other
        temp[static_cast<int>(Type::curse)] = temp[static_cast<int>(Type::status)] = temp[static_cast<int>(Type::skill)];
        return temp;
    }();

    static constexpr std::array<RUtil::AtlasRegionID, 6> card_left_frame_convert = []() constexpr {
        std::array<RUtil::AtlasRegionID, 6> temp{};
        temp[static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_rare_left;
        temp[static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_uncommon_left;
        temp[static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_common_left;
        return temp;
    }();

    static constexpr std::array<RUtil::AtlasRegionID, 6> card_right_frame_convert = []() constexpr {
        std::array<RUtil::AtlasRegionID, 6> temp{};
        temp[static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_rare_right;
        temp[static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_uncommon_right;
        temp[static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_common_right;
        return temp;
    }();

    static constexpr std::array<RUtil::AtlasRegionID, 6> card_mid_frame_convert = []() constexpr {
        std::array<RUtil::AtlasRegionID, 6> temp{};
        temp[static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_rare_center;
        temp[static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_uncommon_center;
        temp[static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_common_center;
        return temp;
    }();

    static constexpr std::array<RUtil::AtlasRegionID, 6> card_banner_convert = []() constexpr {
        std::array<RUtil::AtlasRegionID, 6> temp{};
        temp[static_cast<int>(Rarity::rare)]      = RUtil::AtlasRegionID::_512_banner_rare;
        temp[static_cast<int>(Rarity::uncommon)]  = RUtil::AtlasRegionID::_512_banner_uncommon;
        temp[static_cast<int>(Rarity::common)]    =
        temp[static_cast<int>(Rarity::basic)]     =
        temp[static_cast<int>(Rarity::special)]   =
        temp[static_cast<int>(Rarity::curse)]     = RUtil::AtlasRegionID::_512_banner_common;
        return temp;
    }();
    
    Cards::Cards(
        RUtil::AtlasRegionID card_name, RUtil::Cards_Text_ID card_text_id, Rarity rarity, Type type, 
        Color color, Target target, const int base_cost,
        const int base_damage, const int base_block, const int base_magic_num
    ) : 
        card_name(card_name), card_text_id(card_text_id), rarity(rarity),
        type(type), color(color), target(target),
        base_damage(base_damage), base_block(base_block),
        base_magic_num(base_magic_num), base_cost(base_cost), 
        damage(base_damage), block(base_block),
        magic_num(base_magic_num), cost(base_cost),
        m_card_flash(RUtil::All_Image::GetAtlasRegion(bg_silhouette_id_convert[static_cast<int>(type)]), this->current_x, this->current_y, this->m_angle, this->m_draw_scale, true),
        hb(IMG_WIDTH_S, IMG_HEIGHT_S), energy_num_color(RUtil::WHITE)
    {
        static bool once=false;
        if(!once){
            once=true;
            init_static_menber();
        }
        this->SetFontTypeOffset();
        
        can_hover_in_hand=true;
        can_use=false;
        darken=false;
        m_dark_timer=m_glow_timer=m_hover_timer=0.0F;
        m_draw_scale=m_target_draw_scale=0.7F;
        m_tint_a=0.0F;
        m_color_a= m_target_color_a =1.0F;
        
        this->current_x=this->current_y=0;
        this->target_x=this->target_y=0;
        this->m_angle=this->target_angle=0;
    }

    void Cards::update(Effect::Effect_group &top_effs){
        //flash update
        if(!m_card_flash.IsDone()) m_card_flash.update();
        //hover time update
        if(m_hover_timer!=0.0F)
            m_hover_timer=m_hover_timer<DT()?0.0F:m_hover_timer-DT();
        //if not flying
        if(!this->is_flying){
            //update position
            current_x=RUtil::Math::varlerp(current_x,target_x,6.0F,CARD_SNAP_THRESHOLD);
            current_y=RUtil::Math::varlerp(current_y,target_y,6.0F,CARD_SNAP_THRESHOLD);
        }
        //color_a
        if(this->m_color_a!=m_target_color_a){
            const float step=2.0F*DT();
            if(m_color_a>m_target_color_a){
                if(m_color_a - m_target_color_a < step) m_color_a=m_target_color_a;
                else m_color_a -= step;
            }else{
                if(m_target_color_a - m_color_a < step) m_color_a=m_target_color_a;
                else m_color_a += step;
            }
        }
        //angle
        if(this->m_angle!=this->target_angle){
            this->m_angle=RUtil::Math::varlerp(this->m_angle,target_angle,12.0F,0.003F);
        }
        //scale
        this->hb.move(this->current_x,this->current_y);
        this->hb.resize(IMG_WIDTH*this->m_draw_scale, IMG_HEIGHT*this->m_draw_scale);
        this->hb.update();
        if(hb.ClickStarted()){
            this->m_draw_scale=RUtil::Math::varlerp(this->m_draw_scale, this->m_target_draw_scale*0.9F, 7.5F, 0.003F);
            this->m_draw_scale=RUtil::Math::varlerp(this->m_draw_scale, this->m_target_draw_scale*0.9F, 7.5F, 0.003F);
        }else{
            this->m_draw_scale=RUtil::Math::varlerp(this->m_draw_scale, this->m_target_draw_scale, 7.5F, 0.003F);
        }

        //color
        if(m_dark_timer!=0.0F){
            m_dark_timer-=DT();
            if(m_dark_timer<0.0F)m_dark_timer=0.0F;
            m_tint_a=darken?(1.0F-m_dark_timer/0.3F):m_dark_timer/0.3F;
        }
        //glow
        if(can_use){
            m_glow_timer-=DT();
            if(m_glow_timer<0.0F){
                glowgroup.AddTop(std::make_shared<Effect::Card_glow_border>(RUtil::All_Image::GetAtlasRegion(bg_silhouette_id_convert[static_cast<int>(type)]),this->current_x,this->current_y,this->m_angle,this->m_draw_scale,GLOWCOLOR));
                m_glow_timer=0.3F;
            }
        }
        glowgroup.update();

        this->update_flying(top_effs);
    }

    void Cards::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(is_shuffling&&shuffle_invisible) return;
        //remember to adjust the alpha when flying.
        // if(is_shuffling){
        //     r2->SetColor(s_render_color,1.0F);
        //     format_render(r2,m_card_bg_silhouette,this->current_x,this->current_y,1.0F+this->m_tint_a/5.0F);
        // }
        //flash
        if(!m_card_flash.IsDone()){
            m_card_flash.render(r2);
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        }
        //glow
        if(!glowgroup.empty())
            glowgroup.render(r2);
        //image
        //shadow
        r2->SetColor(FRAME_SHADOW_COLOR,this->m_color_a/4.0F);
        this->format_render(r2, RUtil::All_Image::GetAtlasRegion(bg_silhouette_id_convert[static_cast<int>(type)]), this->current_x + SHADOW_OFFSET_X * this->m_draw_scale, this->current_y - SHADOW_OFFSET_Y * this->m_draw_scale);
        //bg
        r2->SetColor(DEFAULT_COLOR,this->m_color_a);
        this->format_render(r2, RUtil::All_Image::GetAtlasRegion(card_bg_convert[static_cast<int>(type)][static_cast<int>(color)]), this->current_x, this->current_y);
        //portrait
        auto &portrait_img=RUtil::All_Image::GetAtlasRegion(card_name);
        r2->draw(portrait_img, this->current_x-static_cast<float>(portrait_img->GetRegionWidth())/2.0F, this->current_y-static_cast<float>(portrait_img->GetRegionHeight())/2.0F+72.0F, static_cast<float>(portrait_img->GetRegionWidth()), static_cast<float>(portrait_img->GetRegionHeight()), this->m_angle, static_cast<float>(portrait_img->GetRegionWidth())/2.0F, static_cast<float>(portrait_img->GetRegionHeight())/2.0F-72.0F, this->m_draw_scale*Setting::SCALE, this->m_draw_scale*Setting::SCALE);
        //frame
        this->format_render(r2, RUtil::All_Image::GetAtlasRegion(card_frame_convert[static_cast<int>(type)][static_cast<int>(rarity)]), this->current_x, this->current_y);
        if(m_type_width>1.1F){//only need if text too long.
            this->frame_format_render(r2, RUtil::All_Image::GetAtlasRegion(card_mid_frame_convert[static_cast<int>(rarity)]), 0.0F, m_type_width);
            this->frame_format_render(r2, RUtil::All_Image::GetAtlasRegion(card_left_frame_convert[static_cast<int>(rarity)]), -m_type_offset, 1.0F);
            this->frame_format_render(r2, RUtil::All_Image::GetAtlasRegion(card_right_frame_convert[static_cast<int>(rarity)]), m_type_offset, 1.0F);
        }
        //banner
        this->format_render(r2, RUtil::All_Image::GetAtlasRegion(card_banner_convert[static_cast<int>(rarity)]), this->current_x, this->current_y);
        //type
        s_ui_vec[this->m_text_pos]->SetFontColor(TYPE_COLOR);
        s_ui_vec[this->m_text_pos]->SetFontAlpha(m_color_a);
        s_ui_vec[this->m_text_pos]->render_center(r2, this->current_x, this->current_y-21.0F, this->m_angle, 0.0F, 21.0F, m_draw_scale*Setting::SCALE);
        //title
        auto &card_info=RUtil::Cards_Text_Reader::GetInfo(card_text_id);
        card_info.name->SetFontSize(CARD_TITLE_FONT_SIZE);
        card_info.name->SetFontAlpha(m_color_a);
        if(upgraded){
            //name
            card_info.name->SetFontColor(RUtil::GREEN_TEXT_COLOR);
            auto plus_half_width=s_title_plus_drawer.Width("+")/2.0F;
            card_info.name->render_center(r2, current_x - plus_half_width, current_y + 175.0F, this->m_angle, plus_half_width, -175.0F, m_draw_scale*Setting::SCALE);
            //plus
            r2->SetColor(RUtil::GREEN_TEXT_COLOR, m_color_a);
            s_title_plus_drawer.render_center(r2, "+", current_x + card_info.name->GetWidth()/2.0F, current_y + 175.0F, this->m_angle, -card_info.name->GetWidth()/2.0F, -175.0F, m_draw_scale*Setting::SCALE);
        }else{
            card_info.name->SetFontColor(RUtil::WHITE);
            card_info.name->render_center(r2, current_x, current_y + 175.0F, this->m_angle, 0.0F, -175.0F, m_draw_scale*Setting::SCALE);
        }
        //description
        const auto &desc= upgraded && card_info.upgrade_desc!=nullptr ? card_info.upgrade_desc : card_info.desc;
        //render desc
        static constexpr auto foo=[](int a, int b)constexpr{return a==b?(Draw::NumStatus::normal):(a>b?Draw::NumStatus::up:Draw::NumStatus::down);};
        desc->set_num_info(Draw::number_info{damage, block, magic_num, foo(damage, base_damage), foo(block, base_block), foo(magic_num, base_magic_num)});
        desc->SetFontSize(CARD_DESC_FONT_SIZE);
        desc->SetFontAlpha(m_color_a);
        desc->SetFontColor(RUtil::CREAM_COLOR);
        desc->render_center(r2, current_x, current_y - 100.0F, this->m_angle, 0.0F, 100.0F, m_draw_scale*Setting::SCALE);
        if(base_cost>=0){
            //energy
            this->format_render(r2, RUtil::All_Image::GetAtlasRegion(energy_id_convert[static_cast<int>(this->color)]), current_x, current_y);
            //energy number
            s_energy_drawer.render_center_with_bg(r2, std::to_string(cost), current_x - 132.0F, current_y + 192.0F, this->m_angle, 132.0F, -192.0F, m_draw_scale*Setting::SCALE, energy_num_color, m_color_a);
        }
        //tint
        r2->SetColor(TINT_COLOR,this->m_tint_a);
        this->format_render(r2, RUtil::All_Image::GetAtlasRegion(bg_silhouette_id_convert[static_cast<int>(type)]), this->current_x, this->current_y);
    }
    void Cards::format_render(const std::shared_ptr<Draw::Draw_2D> &r2,const std::shared_ptr<Draw::Atlas_Region> &img,float x,float y,float scale)const{
        r2->draw(img, x + img->offsetX - (float)img->original_width / 2.0F, y + img->offsetY - (float)img->original_height / 2.0F,(float)img->GetRegionWidth(), (float)img->GetRegionHeight(),this->m_angle, (float)img->original_width / 2.0F - img->offsetX, (float)img->original_height / 2.0F - img->offsetY, this->m_draw_scale * Setting::SCALE*scale, this->m_draw_scale * Setting::SCALE*scale);
    }
    void Cards::frame_format_render(const std::shared_ptr<Draw::Draw_2D> &r2,const std::shared_ptr<Draw::Atlas_Region> &img,const float x_offset,const float x_scale)const{
        r2->draw(img, this->current_x + img->offsetX - (float)img->original_width / 2.0F + x_offset * this->m_draw_scale, this->current_y + img->offsetY - (float)img->original_height / 2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), this->m_angle, (float)img->original_width / 2.0F - img->offsetX - x_offset * this->m_draw_scale, (float)img->original_height / 2.0F - img->offsetY,  this->m_draw_scale * Setting::SCALE * x_scale, this->m_draw_scale * Setting::SCALE);
    }
    void Cards::Darken(bool immediate){
        darken=true;
        if(immediate){
            m_tint_a=1.0F;
            m_dark_timer=0.0F;
        }else{
            m_dark_timer=0.3F;
        }
    };
    void Cards::Lighten(){
        darken=false;
        m_dark_timer=0.3F;
    }
    void Cards::Unhover(){
        m_target_draw_scale=0.75F;
    }

    void Cards::CanUseUpdate(const Dungeon::Dungeon_shared &dungeon_shared){
        int last=can_use;
        can_use = this->CanUse(dungeon_shared);
        if(last && !can_use) StopGlowing();
        //update energy number color
        if(!is_flying){
            if(dungeon_shared.player->GetCurrEnergy() < cost || base_cost < cost){
                energy_num_color=ENERGY_RED_COLOR;
            }else if(base_cost>cost){
                energy_num_color=ENERGY_GREEN_COLOR;
            }else{
                energy_num_color=RUtil::WHITE;
            }
        }
    }

    bool Cards::CanUse(const Dungeon::Dungeon_shared &dungeon_shared)const{
        return this->cost <= dungeon_shared.player->GetCurrEnergy();
    }

    void Cards::CommonRefreshDamage(const Power::Power_group &player_powers){
        float dmg = static_cast<float>(base_damage);
        for(const auto&it:player_powers){
            dmg = it->calculate_damage_dealt(dmg);
        }
        for(const auto&it:player_powers){
            dmg = it->calculate_final_damage_dealt(dmg);
        }
        this->damage=static_cast<int>(dmg);
        if(this->damage < 0) this->damage = 0;
    }
    
    void Cards::CommonRefreshBlock(const Power::Power_group &player_powers){
        float blk = static_cast<float>(base_block);
        for(const auto&it:player_powers){
            blk = it->calculate_block_modify(blk);
        }
        for(const auto&it:player_powers){
            blk = it->calculate_final_block_modify(blk);
        }
        this->block=static_cast<int>(blk);
        if(this->block < 0) this->block = 0;
    }

    void Cards::CommonRefreshDamage(const Power::Power_group &player_powers, const Power::Power_group &monster_powers){
        float dmg = static_cast<float>(base_damage);
        for(const auto&it:player_powers) dmg = it->calculate_damage_dealt(dmg);
        for(const auto&it:monster_powers) dmg = it->calculate_damage_receive(dmg);
        for(const auto&it:player_powers) dmg = it->calculate_final_damage_dealt(dmg);
        for(const auto&it:monster_powers) dmg = it->calculate_final_damage_receive(dmg);
        this->damage=static_cast<int>(dmg);
        if(this->damage < 0) this->damage = 0;
    }

    void Cards::SetHoverTimer(const float value){m_hover_timer=value;}
    void Cards::MoveTargetY(const float value){target_y+=value;}
    void Cards::MoveTargetX(const float value){target_x+=value;}
    void Cards::MoveTargetAngle(const float value){target_angle+=value;}
    bool Cards::IsHoveredInHand(const float scale)const{
        //The hover detection area here will be larger than the card's hitbox if scale>m_draw_scale,
        //will be smaller if scale<m_draw_scale
        if(!can_hover_in_hand || m_hover_timer>0.0F) return false;
        const float x=(float)RUtil::Game_Input::getX(),y=(float)RUtil::Game_Input::getY(),
                    hw=IMG_WIDTH*scale/2.0F,hh=IMG_HEIGHT*scale/2.0F;
        return current_x-hw<x && x<current_x+hw && current_y-hh<y && y<current_y+hh;
    }
    void Cards::draw(){
        current_x=Card_soul::DRAW_PILE_X;
        current_y=Card_soul::DRAW_PILE_Y;
        m_angle=target_angle=0.0F;
        Lighten();
        m_draw_scale=0.12F;
        m_target_draw_scale=0.75F;
    }
    void Cards::render_hovered_shadow(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(0,0.66F);
        this->format_render(r2,RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_512_card_super_shadow),this->current_x,this->current_y,1.15F);
    }

    void Cards::init_static_menber(){
        s_ui_vec[0]->SetFontSize(CARD_TYPE_FONT_SIZE);
        constexpr float padding=10.0F*Setting::SCALE;
        float jitai_width=s_ui_vec[0]->GetWidth()+padding;
        constexpr float mid_frame_width=48.0F*Setting::SCALE;
        s_type_offset_attack=(jitai_width-mid_frame_width)/2.0F;
        s_type_width_attack=(jitai_width/mid_frame_width-1.0F)*2.0F+1.0F;//let the space have twice as large
        s_ui_vec[1]->SetFontSize(CARD_TYPE_FONT_SIZE);
        jitai_width=s_ui_vec[1]->GetWidth()+padding;
        s_type_offset_skill=(jitai_width-mid_frame_width)/2.0F;
        s_type_width_skill=(jitai_width/mid_frame_width-1.0F)*2.0F+1.0F;
        s_ui_vec[2]->SetFontSize(CARD_TYPE_FONT_SIZE);
        jitai_width=s_ui_vec[2]->GetWidth()+padding;
        s_type_offset_power=(jitai_width-mid_frame_width)/2.0F;
        s_type_width_power=(jitai_width/mid_frame_width-1.0F)*2.0F+1.0F;
        s_ui_vec[3]->SetFontSize(CARD_TYPE_FONT_SIZE);
        jitai_width=s_ui_vec[3]->GetWidth()+padding;
        s_type_offset_curse=(jitai_width-mid_frame_width)/2.0F;
        s_type_width_curse=(jitai_width/mid_frame_width-1.0F)*2.0F+1.0F;
        s_ui_vec[7]->SetFontSize(CARD_TYPE_FONT_SIZE);
        jitai_width=s_ui_vec[7]->GetWidth()+padding;
        s_type_offset_status=(jitai_width-mid_frame_width)/2.0F;
        s_type_width_status=(jitai_width/mid_frame_width-1.0F)*2.0F+1.0F;
    }
    
    void Cards::SetFontTypeOffset(){
        switch(this->type){
            case Type::attack:
                m_type_offset=s_type_offset_attack;
                m_type_width=s_type_width_attack;
                m_text_pos=0;
                break;
            case Type::skill:
                m_type_offset=s_type_offset_skill;
                m_type_width=s_type_width_skill;
                m_text_pos=1;
                break;
            case Type::power:
                m_type_offset=s_type_offset_power;
                m_type_width=s_type_width_power;
                m_text_pos=2;
                break;
            case Type::curse:
                m_type_offset=s_type_offset_curse;
                m_type_width=s_type_width_curse;
                m_text_pos=3;
                break;
            case Type::status:
                m_type_offset=s_type_offset_status;
                m_type_width=s_type_width_status;
                m_text_pos=7;
                break;
            default:
                LOG_ERROR("The type doesn't exist");
                break;
        }
    }

    const std::vector<std::shared_ptr<Draw::Text_layout>> &Cards::s_ui_vec=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::SingleCardViewPopup);
    float Cards::s_type_offset_attack=0.0F,Cards::s_type_offset_skill=0.0F,Cards::s_type_offset_power=0.0F,Cards::s_type_offset_status=0.0F,Cards::s_type_offset_curse=0.0F,Cards::s_type_width_attack=0.0F,Cards::s_type_width_skill=0.0F,Cards::s_type_width_power=0.0F,Cards::s_type_width_status=0.0F,Cards::s_type_width_curse=0.0F;
    Uint32 Cards::s_render_color;
    Draw::NumberDrawer const Cards::s_energy_drawer{ENERGY_Font_SIZE, FontWeight::bold},
                             Cards::s_title_plus_drawer{CARD_TITLE_FONT_SIZE, FontWeight::bold};
}