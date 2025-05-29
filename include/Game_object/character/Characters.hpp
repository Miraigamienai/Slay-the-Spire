#pragma once

#include <type_traits>

#include "Game_object/power/Power_group.hpp"
#include "RUtil/Hitbox.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Game_Input.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

//fwd decl
struct Damage_info;
namespace Draw{
    class Draw_2D;
}
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Character{
enum class Animation:int
{
    ATTACK_FAST,
    ATTACK_SLOW,
    HOP,
    JUMP,
    STAGGER,
    FAST_SHAKE,
    SHAKE
};
enum class CharacterType
{
    PLAYER,
    MONSTER
};
class Characters : public std::enable_shared_from_this<Characters>
{
public:
    Characters(CharacterType type, float x, float y, float width, float height, float hb_offset_x, float hb_offset_y, int HP);
    virtual ~Characters()=default;
    virtual void damage(const Damage_info& damage_info)=0;
    virtual void heal(int num, Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2) const =0;
    virtual void update()=0;
    
    void AddBlock(int num);
    void ReduceBlock(int num, Dungeon::Dungeon_shared &dungeon_shared);

    template <Animation Anim>
    using FLOAT_PARAMETER_ANIM_TYPE = std::enable_if_t<Anim == Animation::FAST_SHAKE || Anim == Animation::SHAKE>;
    
    template <Animation Anim>
    using NONE_PARAMETER_ANIM_TYPE = std::enable_if_t<Anim != Animation::FAST_SHAKE && Anim != Animation::SHAKE>;

    template <Animation Anim>
    NONE_PARAMETER_ANIM_TYPE<Anim> use_animation()noexcept{
        if constexpr (Anim!=Animation::STAGGER){
            animX = animY = 0.0F;
            animation=Anim;
        }

        if constexpr (Anim==Animation::ATTACK_FAST){
            animation_timer=0.4F;
        }else if constexpr (Anim==Animation::ATTACK_SLOW){
            animation_timer=1.0F;
        }else if constexpr (Anim==Animation::HOP){
            speed_y=300.0F*Setting::SCALE;
            animation_timer=0.7F;
        }else if constexpr (Anim==Animation::JUMP){
            speed_y=500.0F*Setting::SCALE;
            animation_timer=0.7F;
        }else if constexpr (Anim==Animation::STAGGER){
            if(animY==0.0F){
                animX=0.0F;
                animation_timer=STAGGER_TIME;
                animation=Anim;
            }
        }
    }

    template <Animation Anim>
    FLOAT_PARAMETER_ANIM_TYPE<Anim> use_animation(float duration){
        if(animY==0.0F){
            animX=0.0F;
            animation_timer=duration;
            animation=Anim;
        }
    }
  
    auto&get_powers(){return powers;}
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared){powers.at_turn_end(dungeon_shared, shared_from_this());}
    void at_turn_start(Dungeon::Dungeon_shared &dungeon_shared){if(!powers.no_lose_block()) this->ReduceBlock(current_Block, dungeon_shared);}
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float temp_pos=boss_hitbox.CenterX() + boss_hitbox.Width() / 2.0F;
        if(temp_pos < TIP_X_THRESHOLD){//right
            powers.render_tip(r2, temp_pos + TIP_OFFSET_R_X, boss_hitbox.CenterY());
        }else{//left
            powers.render_tip(r2, temp_pos + TIP_OFFSET_L_X, boss_hitbox.CenterY());
        }
    }
    
    bool hovered()const noexcept(noexcept(boss_hitbox.Hovered())){return boss_hitbox.Hovered();}
    bool IsDie()const noexcept{return current_HP<=0;}
    auto GetCurrentBlock()const noexcept{return current_Block;}
    auto GetMaxHP()const noexcept{return max_HP;}
    auto GetCurrentHP()const noexcept{return current_HP;}
    auto GetWidth()const noexcept{return boss_hitbox.Width();}
    auto GetHeight()const noexcept{return boss_hitbox.Height();}
    auto GetcX()const noexcept{return boss_hitbox.CenterX();}
    auto GetcY()const noexcept{return boss_hitbox.CenterY();}
    auto getAnimX()const noexcept{return animX;}
    auto getAnimY()const noexcept{return animY;}
    auto GetFixedOriginX()const noexcept{return boss_hitbox.CenterX()-animX;}
    auto GetFixedOriginY()const noexcept{return boss_hitbox.CenterY()-animY;}

    static void render_reticle(const std::shared_ptr<Draw::Draw_2D> &r2, float center_x, float center_y, float width, float height, float time);
    const CharacterType type;
protected:
    const float orgX, orgY;
    int current_HP;
    bool escaping;
    void render_HP_and_power(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update_HP_and_power();
    void update_reticle();
    void update_animation(){
        if(animation_timer==0.0F) return;
        switch (animation) {
            case Animation::ATTACK_FAST:
                updateFastAttackAnimation(type==CharacterType::PLAYER ? ANIM_X_TARGET_POS : -ANIM_X_TARGET_POS);
                break;
            case Animation::ATTACK_SLOW:
                updateSlowAttackAnimation(type==CharacterType::PLAYER ? ANIM_X_TARGET_POS : -ANIM_X_TARGET_POS);
                break;
            case Animation::HOP:
                updateHopAnimation();
                break;
            case Animation::JUMP:
                updateJumpAnimation();
                break;
            case Animation::STAGGER:
                updateStaggerAnimation(type==CharacterType::PLAYER ? STAGGER_MOVE_SPEED : -STAGGER_MOVE_SPEED);
                break;
            case Animation::FAST_SHAKE:
                updateFastShakeAnimation();
                break;
            case Animation::SHAKE:
                updateShakeAnimation();
                break;
            default:
                break;
        }
        if(animation!=Animation::HOP && animation!=Animation::JUMP){
            animation_timer-=RUtil::Game_Input::delta_time();
            if(animation_timer<0.0F){
                animation_timer=0.0F;
                animX = animY = 0.0F;
            }
        }
    }
private:
    //members
    int max_HP;
    int current_Block;
    const float hb_offset_x, hb_offset_y;
    RUtil::Hitbox boss_hitbox;
    RUtil::Hitbox HP_hb;
    float animX, animY;
    float speed_y;
    float health_width, health_target_width;
    float HP_hb_a, shadow_a, bg_a, outline_a/*HP text also use outline_a*/, block_icon_a, block_text_a;
    float HP_offset_y, block_offset;
    float HP_hide_timer, HP_show_timer, HP_anim_wait_timer, block_anim_timer;
    float block_num_scale;
    Uint32 block_text_color;
    glm::vec3 block_text_color_vec;
    float animation_timer;
    Animation animation;
    bool shake_toggle;
    Power::Power_group powers;

    //functions
    void health_update_event()noexcept(noexcept(HP_hb.Width())){
        HP_anim_wait_timer=HP_ANIM_WAIT_TIME;
        if(max_HP==current_HP) health_width = health_target_width = HP_hb.Width(); 
        else health_target_width = HP_hb.Width()*static_cast<float>(current_HP)/static_cast<float>(max_HP);
        
        if(health_target_width > health_width) health_width=health_target_width;
    }
    void updateFastAttackAnimation(float target_x){
        if(animation_timer>0.5F) animX=RUtil::Math::interpolation_exp5in(0.0F, target_x, (1.0F-animation_timer)*2.0F);
        else animX=RUtil::Math::interpolation_fade(0.0F, target_x, animation_timer * 2.0F);
    }
    void updateSlowAttackAnimation(float target_x){
        if(animation_timer>0.5F) animX=RUtil::Math::interpolation_exp10in(0.0F, target_x, (1.0F-animation_timer)*2.0F);
        else animX=RUtil::Math::interpolation_fade(0.0F, target_x, animation_timer * 2.0F);    
    }
    void updateHopAnimation()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        speed_y-=17.0F*Setting::SCALE;
        animY+=speed_y*RUtil::Game_Input::delta_time();
        if(animY<0.0F) animY=0.0F;
    }
    void updateJumpAnimation()noexcept(noexcept(updateHopAnimation())){
        updateHopAnimation();
    }
    void updateStaggerAnimation(float target_x){
        animX=RUtil::Math::interpolation_pow2(target_x, 0.0F, 1.0F - animation_timer/STAGGER_TIME);
    }
    void updateFastShakeAnimation(){
        if(shake_toggle){
            animX+=SHAKE_SPEED*RUtil::Game_Input::delta_time();
            if(animX > SHAKE_THRESHOLD / 2.0F) shake_toggle=false;
        }else{
            animX-=SHAKE_SPEED*RUtil::Game_Input::delta_time();
            if(animX < -SHAKE_THRESHOLD / 2.0F) shake_toggle=true;
        }
    }
    void updateShakeAnimation(){
        if(shake_toggle){
            animX+=SHAKE_SPEED*RUtil::Game_Input::delta_time();
            if(animX > SHAKE_THRESHOLD) shake_toggle=false;
        }else{
            animX-=SHAKE_SPEED*RUtil::Game_Input::delta_time();
            if(animX < -SHAKE_THRESHOLD) shake_toggle=true;
        }
    }
    void update_hb_pos()noexcept(noexcept(HP_hb.move(0.0F, 0.0F)) && noexcept(HP_hb.CenterX()) && noexcept(HP_hb.CenterY()) && noexcept(HP_hb.Height())){
        boss_hitbox.move(orgX + animX + hb_offset_x, orgY + hb_offset_y);
        HP_hb.move(boss_hitbox.CenterX(), boss_hitbox.CenterY()-boss_hitbox.Height()/2.0F-HP_hb.Height()/2.0F);
    }
    //static members
    static const Draw::NumberDrawer HP_num_drawer, block_num_drawer;
    //static functions
    static inline void render_HP_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width, bool with_L=true);
    static inline void render_block_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width);
    static inline void render_reticle_corner(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, bool flip_x, bool flip_y, float alpha);
    //static imgs
    static const std::shared_ptr<Draw::ReTexture> &_SHADOW_L,&_SHADOW_R,&_SHADOW_B,
                                                &HEALTH_BAR_B,&HEALTH_BAR_L,&HEALTH_BAR_R,
                                                &BLOCK_BAR_B,&BLOCK_BAR_R,&BLOCK_BAR_L,
                                                &BLOCK_ICON;
    static const std::shared_ptr<Draw::ReTexture> &RETICLE_CORNER;
    //HP constexpr
    static constexpr int ORG_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.5F,0.0F),
                         BLUE_BAR_COLOR=0x31568c00,
                         RED_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(0.8F,0.05F,0.05F),
                         BLOCK_COLOR=RUtil::Math::GetColorUint32_RGB(0.6F,0.93F,0.98F);
    static constexpr float HEALTH_BAR_HEIGHT=20.0F*Setting::SCALE,
                           HEALTH_BAR_OFFSET_Y=-28.0F*Setting::SCALE,
                           HEALTH_BG_OFFSET=28.0F*Setting::SCALE,
                           BLOCK_ICON_XY=-14.0F*Setting::SCALE,
                           HP_HIBOX_H=72.0F*Setting::SCALE,
                           HP_START_OFFSET_Y=60.0F*Setting::SCALE,
                           BLOCK_START_OFFSET_Y=36.0F*Setting::SCALE;
    static constexpr glm::vec3 BLOCK_TEXT_COLOR_TARGET{1.0F, 1.0F, 1.0F},
                               BLOCK_GAIN_TEXT_COLOR=RUtil::Math::TO_VEC3(RUtil::GOLD_COLOR),
                               BLOCK_LOST_TEXT_COLOR=RUtil::Math::TO_VEC3(RUtil::ToRGBA(RUtil::Colors::TOMATO));
    static constexpr int HP_FONTSIZE=22, BLOCK_FONTSIZE=24;
    //animation constexpr
    static constexpr float SHAKE_THRESHOLD = Setting::SCALE * 8.0F;
    static constexpr float SHAKE_SPEED = 150.0F * Setting::SCALE;
    static constexpr float STAGGER_MOVE_SPEED = 20.0F * Setting::SCALE;
    static constexpr float ANIM_X_TARGET_POS = 90.0F * Setting::SCALE;
    //tip constexpr
    static constexpr float TIP_X_THRESHOLD = 1554.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_R_X = 20.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_L_X = -600.0F * Setting::SCALE;
    //timer constexpr
    static constexpr float FADE_TIME = 1.5F;
    static constexpr float BLOCK_ANIM_TIME = 0.7F;
    static constexpr float HP_ANIM_TIME = 0.7F;
    static constexpr float HP_ANIM_WAIT_TIME = 1.2F;
    static constexpr float STAGGER_TIME = 0.3F;
};
}