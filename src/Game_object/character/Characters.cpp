#include "Game_object/character/Characters.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/block_broken_eff.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

#include "Util/Logger.hpp"

namespace Character{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractCreature))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractCreature);
    }

    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }

    Characters::Characters(CharacterType type, float x, float y, float width, float height, float hb_offset_x, float hb_offset_y, int HP)
        :type(type),
        orgX(x), orgY(y),
        current_HP(HP),
        escaping(false),
        max_HP(HP),
        current_Block(0),
        hb_offset_x(hb_offset_x), hb_offset_y(hb_offset_y),
        boss_hitbox(width, height),
        HP_hb(width, HP_HIBOX_H),
        animX(0.0F), animY(0.0F),
        speed_y(0.0F),
        health_width(width), health_target_width(width),
        HP_hb_a(0.0F), shadow_a(0.0F), bg_a(0.0F), outline_a(0.0F),
        HP_offset_y(HP_START_OFFSET_Y), block_offset(BLOCK_START_OFFSET_Y),
        HP_hide_timer(1.0F), HP_show_timer(0.0F), HP_anim_wait_timer(0.0F), block_anim_timer(0.0F),
        block_num_scale(1.0F),
        block_text_color(RUtil::WHITE),
        block_text_color_vec(BLOCK_TEXT_COLOR_TARGET),
        animation_timer(0.0F),
        animation(static_cast<Character::Animation>(0)),
        shake_toggle(false)
    {
        update_hb_pos();
    }

    void Characters::AddBlock(int num){
        const bool not_have_block = current_Block==0;
        current_Block+=num;
        if(not_have_block && current_Block>0){
            block_anim_timer = BLOCK_ANIM_TIME;
            block_text_a = 0.0F;
            block_icon_a = 0.0F;
        }else{
            block_text_color_vec=BLOCK_GAIN_TEXT_COLOR;
            block_num_scale=5.0F;
        }
    }
    
    void Characters::ReduceBlock(int num, Dungeon::Dungeon_shared &dungeon_shared){
        if(current_Block < num){
            LOG_ERROR("Reducing block when current_block is {}, num is {}, type{}", current_Block, num, static_cast<int>(type));
            return;
        }
        current_Block-=num;
        if(num>0){
            if(current_Block==0){
                dungeon_shared.effs.AddTop(std::make_shared<Effect::block_broken_eff>(boss_hitbox.X()+BLOCK_ICON_XY, boss_hitbox.Y()+BLOCK_ICON_XY));
            }else{
                block_text_color_vec=BLOCK_LOST_TEXT_COLOR;
                block_num_scale=5.0F;
            }
        }
    }
    
    void Characters::render_reticle(const std::shared_ptr<Draw::Draw_2D> &r2, float center_x, float center_y, float width, float height, float time){
        static SETTING_CONSTEXPR auto RETICLE_OFFSET_DIST = 15.0F*Setting::SCALE;
        const float alpha = time<1.0F/3.0F ? time*3.0F : 1.0F;
        const float offset=RUtil::Math::interpolation_elastic_out(RETICLE_OFFSET_DIST, 0.0F, (time<1.0F?time:1.0F));
        render_reticle_corner(r2, center_x - width / 2.0F + offset, center_y + height / 2.0F - offset, false, false, alpha);
        render_reticle_corner(r2, center_x + width / 2.0F - offset, center_y + height / 2.0F - offset, true, false, alpha);
        render_reticle_corner(r2, center_x - width / 2.0F + offset, center_y - height / 2.0F + offset, false, true, alpha);
        render_reticle_corner(r2, center_x + width / 2.0F - offset, center_y - height / 2.0F + offset, true, true, alpha);
   }
    
    inline void Characters::render_reticle_corner(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, bool flip_x, bool flip_y, float alpha){
        static SETTING_CONSTEXPR auto SHADOW_OFFSET=4.0F*Setting::SCALE;
        r2->SetColor(RUtil::BLACK, alpha/4.0F);
        r2->draw(RETICLE_CORNER, x-18.0F+SHADOW_OFFSET, y-18.0F-SHADOW_OFFSET, 36.0F, 36.0F, 0.0F, 18.0F, 18.0F, Setting::SCALE, Setting::SCALE, flip_x, flip_y);
        r2->SetColor(RUtil::WHITE, alpha);
        r2->draw(RETICLE_CORNER, x-18.0F, y-18.0F, 36.0F, 36.0F, 0.0F, 18.0F, 18.0F, Setting::SCALE, Setting::SCALE, flip_x, flip_y);
    }

    void Characters::update_HP_and_power(){
        //hitbox update
        update_hb_pos();
        HP_hb.update();
        boss_hitbox.update();
        //HP_hide_timer update
        if(HP_hb.Hovered()){
            HP_hide_timer-=DT()*4.0F;
            if(HP_hide_timer<0.2F) HP_hide_timer=0.2F;
        }else{
            HP_hide_timer+=DT()*4.0F;
            if(HP_hide_timer>1.0F) HP_hide_timer=1.0F;
        }
        //block anim update
        if(current_Block>0){
            if(block_anim_timer!=0.0F){
                block_anim_timer-=DT();
                if(block_anim_timer<0.0F) block_anim_timer=0.0F;
                const float t = 1.0F - block_anim_timer/BLOCK_ANIM_TIME;
                block_offset=RUtil::Math::interpolation_swing_out(BLOCK_START_OFFSET_Y, 0.0F, t);
                block_num_scale=RUtil::Math::Apply(3.0F, 1.0F, std::pow(t, 3));
                block_icon_a=RUtil::Math::interpolation_powout2(0.0F, 1.0F, t);
                block_text_a=RUtil::Math::Apply(0.0F, 1.0F, std::pow(t, 5));
            }else if(block_num_scale!=1.0F){
                block_num_scale=RUtil::Math::varlerp(block_num_scale, 1.0F, 8.0F, 0.003F);
            }
            //text color update
            if(block_text_color_vec != BLOCK_TEXT_COLOR_TARGET){
                block_text_color_vec = RUtil::Math::varlerp(block_text_color_vec, BLOCK_TEXT_COLOR_TARGET, 3.0F, 0.01F);
                block_text_color = RUtil::Math::GetColorUint32_RGB(block_text_color_vec.r, block_text_color_vec.g, block_text_color_vec.b);
            }
        }
        //update show HP anim
        if(HP_show_timer>0.0F){
            HP_show_timer-=DT();
            if(HP_show_timer<0.0F) HP_show_timer=0.0F;
            const float hp_t=1.0F - HP_show_timer/HP_ANIM_TIME;
            HP_hb_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, hp_t);
            HP_offset_y=RUtil::Math::interpolation_exp10out(HP_START_OFFSET_Y, 0.0F, hp_t);
        }
        //update health display
        if(HP_anim_wait_timer>0.0F) HP_anim_wait_timer-=DT();
        else if(health_target_width < health_width){
            health_width = RUtil::Math::varlerp(health_width, health_target_width, 9.0F, Setting::SCALE);
        }
        //HP alphas update
        if(escaping && type==CharacterType::MONSTER){
            HP_hb_a=RUtil::Math::fadelerp(HP_hb_a, 0.0F);
            bg_a=HP_hb_a*0.75F;
            shadow_a=HP_hb_a*0.5F;
            outline_a=HP_hb_a;
            health_target_width=0.0F;
        }else if(health_target_width==0.0F && HP_anim_wait_timer==0.0F){
            shadow_a=RUtil::Math::fadelerp(shadow_a, 0.0F);
            bg_a=RUtil::Math::fadelerp(bg_a, 0.0F);
            outline_a=RUtil::Math::fadelerp(outline_a, 0.0F);
        }else{
            bg_a=HP_hb_a*0.5F;
            shadow_a=HP_hb_a*0.2F;
            outline_a=HP_hb_a;
        }
        //powers update
        this->powers.update();
    }

    void Characters::render_HP_and_power(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float x=boss_hitbox.X(),
                    y=boss_hitbox.Y() + HP_offset_y;
        //shadow
        r2->SetColor(RUtil::BLACK, shadow_a);
        r2->draw(_SHADOW_L, x-HEALTH_BAR_HEIGHT, y-HEALTH_BG_OFFSET, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        r2->draw(_SHADOW_B, x, y-HEALTH_BG_OFFSET, HP_hb.Width(), HEALTH_BAR_HEIGHT);
        r2->draw(_SHADOW_R, x+HP_hb.Width(), y-HEALTH_BG_OFFSET, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        if(current_HP!=max_HP){
            //empty hp render
            r2->SetColor(RUtil::BLACK, bg_a);
            render_HP_format(r2, x, y, HP_hb.Width());
        }
        if(health_target_width!=0.0F){
            //hp just move //orange
            r2->SetColor(ORG_BAR_COLOR, HP_hb_a);
            render_HP_format(r2, x, y, health_width);
            //hp //red //if have block,blue
            r2->SetColor(current_Block>0 ? BLUE_BAR_COLOR : RED_BAR_COLOR, HP_hb_a);
            render_HP_format(r2, x, y, health_target_width, current_HP>0);
        }
        //check HP_hb_a cuz outline_a != HP_hb_a || block_icon_a != HP_hb_a
        if(current_Block>0 && HP_hb_a!=0.0F){
            //reder block outline
            r2->SetColor(BLOCK_COLOR, outline_a);
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
            render_block_format(r2, x, y, HP_hb.Width());
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            //block icon and value
            r2->SetColor(BLOCK_COLOR, block_icon_a);
            r2->draw(BLOCK_ICON, x+BLOCK_ICON_XY-32.0F, y+BLOCK_ICON_XY-32.0F+block_offset, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
            block_num_drawer.render_center_with_bg(r2, std::to_string(current_Block), x+BLOCK_ICON_XY, y-16.0F*Setting::SCALE, 0.0F, 0.0F, 0.0F, block_num_scale*Setting::SCALE, block_text_color, block_text_a);
        }
        //HP text
        if(health_target_width!=0.0F){
            HP_num_drawer.render_center_with_bg(r2, std::to_string(current_HP)+"/"+std::to_string(max_HP), boss_hitbox.CenterX(), y+HEALTH_BAR_OFFSET_Y+11.0F*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE, RUtil::WHITE, outline_a*HP_hide_timer);
        }else if(!escaping){
            TEXT_VEC()[0]->ChangeFontWeight(FontWeight::bold);
            TEXT_VEC()[0]->SetFontColorAlpha(RUtil::WHITE, outline_a);
            TEXT_VEC()[0]->SetFontSize(HP_FONTSIZE);
            TEXT_VEC()[0]->render_center(r2, boss_hitbox.CenterX(), y+HEALTH_BAR_OFFSET_Y+5.0F*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        }
        //powers
        powers.render(r2, x, y, outline_a);
    }

    inline void Characters::render_HP_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width, bool with_L){
        if(with_L) r2->draw(HEALTH_BAR_L, x - HEALTH_BAR_HEIGHT, y + HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        r2->draw(HEALTH_BAR_B, x, y + HEALTH_BAR_OFFSET_Y, width, HEALTH_BAR_HEIGHT);
        r2->draw(HEALTH_BAR_R, x + width, y + HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
    }

    inline void Characters::render_block_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width){
        r2->draw(BLOCK_BAR_L, x - HEALTH_BAR_HEIGHT, y + HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        r2->draw(BLOCK_BAR_B, x, y + HEALTH_BAR_OFFSET_Y, width, HEALTH_BAR_HEIGHT);
        r2->draw(BLOCK_BAR_R, x + width, y + HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
    }

    const Draw::NumberDrawer Characters::HP_num_drawer{HP_FONTSIZE, FontWeight::bold}, Characters::block_num_drawer{BLOCK_FONTSIZE, FontWeight::bold};
    const std::shared_ptr<Draw::ReTexture>  &Characters::_SHADOW_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/leftBg.png"),&Characters::_SHADOW_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/rightBg.png"),&Characters::_SHADOW_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/bodyBg.png"),
                                            &Characters::HEALTH_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/body7.png"),&Characters::HEALTH_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/left7.png"),&Characters::HEALTH_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/right7.png"),
                                            &Characters::BLOCK_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockBody3.png"),&Characters::BLOCK_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockRight3.png"),&Characters::BLOCK_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockLeft3.png"),
                                            &Characters::BLOCK_ICON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/block.png");
    const std::shared_ptr<Draw::ReTexture>  &Characters::RETICLE_CORNER=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/reticleCorner.png");
}