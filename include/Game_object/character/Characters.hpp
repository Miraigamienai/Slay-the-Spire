#pragma once

#include "Game_object/power/Power_group.hpp"
#include "RUtil/Hitbox.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/NumberDrawer.hpp"
#include "WindowSize.hpp"

//fwd decl
struct Damage_info;
namespace Draw{
    class Draw_2D;
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
    SHAKE,
    NONE
};
enum class CharacterType
{
    PLAYER,
    MONSTER
};
class Characters : public std::enable_shared_from_this<Characters>
{
public:
    Characters(CharacterType type, float x, float y, float width, float height, float hb_offset_x, float hb_offset_y)
        :type(type),
        max_HP(0), current_HP(0),
        current_Block(0),
        orgX(x), orgY(y),
        img_color_a(1.0F),
        hb_offset_x(hb_offset_x), hb_offset_y(hb_offset_y),
        boss_hitbox(width, height),
        HP_hb(width, HP_HIBOX_H),
        animX(0.0F), animY(0.0F),
        vX(0.0F), vY(0.0F)
    {
        update_hb_pos();
    }
    [[deprecated]]
    Characters(float x, float y, float width, float height,float HPBarWidth);
    virtual ~Characters()=default;
    virtual void damage(const Damage_info& damage_info)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2) const =0;
    virtual void update()=0;
    void setPosition(float x,float y);
    void AddBlock(int num){current_Block+=num;};
    void ReduceBlock(int num){current_Block-=num;};
    void setBlock(int num){current_Block=num;};
    void AddHP(int num){current_HP+num>=max_HP?current_HP=max_HP:current_HP+=num;};
    void setHP(int num){current_HP=num;};
    void updateHealthBar();
    
    void useFastAttackAnimation();
    void useSlowAttackAnimation();
    void useHopAnimation();
    void useJumpAnimation();
    void useStaggerAnimation();
    void useFastShakeAnimation(float duration);
    void useShakeAnimation(float duration);

    void updateFastAttackAnimation();
    void updateSlowAttackAnimation();
    void updateHopAnimation();
    void updateJumpAnimation();
    void updateStaggerAnimation();
    void updateFastShakeAnimation();
    void updateShakeAnimation();
    void updateAnimation();

    Animation getAnimation()const{return animation;}
    float getAnimX()const{return animX;}
    float getAnimY()const{return animY;}
  
    auto&get_powers(){return powers;}
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared){powers.at_turn_end(dungeon_shared, shared_from_this());}
    void at_turn_start(){if(!powers.no_lose_block()) this->ReduceBlock(current_Block);}
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
    bool IsFading()const noexcept{return fade_timer!=0.0F;}
    auto GetCurrentBlock()const noexcept{return current_Block;}
    auto GetMaxHP()const noexcept{return max_HP;}
    auto GetCurrentHP()const noexcept{return current_HP;}
    auto GetWidth()const noexcept{return boss_hitbox.Width();}
    auto GetHeight()const noexcept{return boss_hitbox.Height();}
    auto GetcX()const noexcept{return boss_hitbox.CenterX();}
    auto GetcY()const noexcept{return boss_hitbox.CenterY();}
    auto GetFixedOriginX()const noexcept{return boss_hitbox.CenterX()-animX;}
    auto GetFixedOriginY()const noexcept{return boss_hitbox.CenterY()-animY;}

    const CharacterType type;
protected:
    int max_HP,current_HP;
    int current_Block;
    const float orgX, orgY;
    float img_color_a;
    void render_HP_and_power(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update_HP_and_power();
private:
    //members
    const float hb_offset_x, hb_offset_y;
    RUtil::Hitbox boss_hitbox;
    RUtil::Hitbox HP_hb;
    float animX, animY;
    float vX, vY;
    float HP_hb_a, shadow_a, bg_a, block_icon_a, block_text_a, outline_a;//HP text also use outline_a
    float HP_offset_y, block_offset;
    float HP_hide_timer, HP_anim_wait_timer, block_anim_timer;
    float block_num_scale;
    Uint32 block_text_color;
    float fade_timer;

    float animationTimer;
    Animation animation=Animation::NONE;
    
    float health_width,health_target_width;
    bool shakeToggle,HPDecrease;
    Power::Power_group powers;
    //functions
    void update_hb_pos()noexcept(noexcept(HP_hb.move(0.0F, 0.0F)) && noexcept(HP_hb.CenterX()) && noexcept(HP_hb.CenterY()) && noexcept(HP_hb.Height())){
        boss_hitbox.move(orgX + animX + hb_offset_x, orgY + hb_offset_y);
        HP_hb.move(boss_hitbox.CenterX(), boss_hitbox.CenterY()-boss_hitbox.Height()/2.0F-HP_hb.Height()/2.0F);
    }
    //static members
    static const Draw::NumberDrawer HP_num_drawer, block_num_drawer;
    //static functions
    static inline void render_HP_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width, bool with_L=true);
    static inline void render_block_format(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float width);
    //static imgs
    static const std::shared_ptr<Draw::ReTexture>  &_SHADOW_L,&_SHADOW_R,&_SHADOW_B,
                                                &HEALTH_BAR_B,&HEALTH_BAR_L,&HEALTH_BAR_R,
                                                &BLOCK_BAR_B,&BLOCK_BAR_R,&BLOCK_BAR_L,
                                                &BLOCK_ICON;
    //HP constexpr
    static constexpr int ORG_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.5F,0.0F),
                         BLUE_BAR_COLOR=0x31568c00,
                         RED_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(0.8F,0.05F,0.05F),
                         BLOCK_COLOR=RUtil::Math::GetColorUint32_RGB(0.6F,0.93F,0.98F);
    static constexpr float HEALTH_BAR_HEIGHT=20.0F*Setting::SCALE,
                           HEALTH_BAR_OFFSET_Y=-28.0F*Setting::SCALE,
                           HEALTH_BG_OFFSET=28.0F*Setting::SCALE,
                           BLOCK_ICON_XY=-14.0F*Setting::SCALE,
                           HP_HIBOX_H=72.0F*Setting::SCALE;
    static constexpr int HP_FONTSIZE=22, BLOCK_FONTSIZE=24;
    //animation constexpr
    static constexpr float SHAKE_THRESHOLD = Setting::SCALE * 8.0F;
    static constexpr float SHAKE_SPEED = 150.0F * Setting::SCALE;
    static constexpr float STAGGER_MOVE_SPEED = 20.0F * Setting::SCALE;
    //tip constexpr
    static constexpr float TIP_X_THRESHOLD = 1554.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_R_X = 20.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_L_X = -600.0F * Setting::SCALE;
    //timer constexpr
    static constexpr float FADE_TIME = 1.5F;
    static constexpr float BLOCK_ANIM_TIME = 0.7F;
};
}