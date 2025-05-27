#ifndef GAME_OBJECT_CHARACTER_CHARACTERS
#define GAME_OBJECT_CHARACTER_CHARACTERS
#include "Draw/Draw_2D.hpp"
#include "RUtil/Hitbox.hpp"
#include "RUtil/Image_book.hpp"
#include "WindowSize.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/NumberDrawer.hpp"
#include "Game_object/power/Power_group.hpp"

//fwd decl
struct Damage_info;

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
enum class KindOfCharacter
{
    PLAYER,
    MONSTER
};
class Characters : public std::enable_shared_from_this<Characters>
{
public:
    Characters(float x, float y, float width, float height,float HPBarWidth);
    virtual ~Characters()=default;
    virtual void damage(const Damage_info& damage_info)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2) const =0;
    void update();
    void setPosition(float x,float y);
    void setHPBarWidth(float width);
    bool hovered()const{return boss_hitbox.Hovered();}
    bool IsDie()const{return current_HP<=0 && fadeTimer<=0;}
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

    bool isPlayer()const{return KindOfCharacter==KindOfCharacter::PLAYER;}
    
    auto&get_powers(){return powers;}
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared){powers.at_turn_end(dungeon_shared, shared_from_this());}
    void at_turn_start(){
        if(!powers.no_lose_block()) this->ReduceBlock(current_Block);
    }
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float temp_pos=boss_hitbox.CenterX() + boss_hitbox.Width() / 2.0F;
        if(temp_pos < TIP_X_THRESHOLD){//right
            powers.render_tip(r2, temp_pos + TIP_OFFSET_R_X, boss_hitbox.CenterY());
        }else{//left
            powers.render_tip(r2, temp_pos + TIP_OFFSET_L_X, boss_hitbox.CenterY());
        }
    }
    
    auto GetCurrentBlock()const noexcept{return current_Block;}
    auto GetMaxHP()const noexcept{return max_HP;}
    auto GetCurrentHP()const noexcept{return current_HP;}
    auto GetWidth()const noexcept{return boss_hitbox.Width();}
    auto GetHeight()const noexcept{return boss_hitbox.Height();}
    auto GetcX()const noexcept{return boss_hitbox.CenterX();}
    auto GetcY()const noexcept{return boss_hitbox.CenterY();}
    auto GetOriginX()const noexcept{return boss_hitbox.CenterX()-animX;}
    auto GetOriginY()const noexcept{return boss_hitbox.CenterY()-animY;}
    
protected:
    int max_HP,current_HP,current_Block;
    void render_HP(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    glm::vec2 getPosition()const{return pos;}
    KindOfCharacter KindOfCharacter;

    bool HPDecrease=false,shakeToggle,IsFadeOut;
    float fadeTimer,FadeColorA,fadeTime=1.5F;
private:
    RUtil::Hitbox boss_hitbox;
    RUtil::Hitbox HPBar_hitbox;
    glm::vec2 pos={0,0};
    float HPBar_hb_width, HPBar_hb_a;
    float animX,animY,vX,vY,orgX,orgY;
    float HPDecreaseWaitTimer,animationTimer;
    Animation animation=Animation::NONE;
    Draw::NumberDrawer m_font;
    Power::Power_group powers;
    float shadow_a,bg_a,outline_a,health_width,health_target_width,block_offset,font_scale;
    static const std::shared_ptr<Draw::ReTexture>  &_SHADOW_L,&_SHADOW_R,&_SHADOW_B,
                                                &HEALTH_BAR_B,&HEALTH_BAR_L,&HEALTH_BAR_R,
                                                &BLOCK_BAR_B,&BLOCK_BAR_R,&BLOCK_BAR_L,
                                                &BLOCK_ICON;
    static constexpr int ORG_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.5F,0.0F),BLUE_BAR_COLOR=0x31568c00,RED_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(0.8F,0.05F,0.05F),BLOCK_COLOR=RUtil::Math::GetColorUint32_RGB(0.6F,0.93F,0.98F);
    static constexpr float HEALTH_BAR_HEIGHT=20.0F*Setting::SCALE,HEALTH_BAR_OFFSET_Y=-28.0F*Setting::SCALE,HEALTH_BG_OFFSET=28.0F*Setting::SCALE,BLOCK_ICON_XY=-14.0F*Setting::SCALE;
    static constexpr float SHAKE_THRESHOLD = Setting::SCALE * 8.0F;
    static constexpr float SHAKE_SPEED = 150.0F * Setting::SCALE;
    static constexpr float STAGGER_MOVE_SPEED = 20.0F * Setting::SCALE;
    static constexpr float TIP_X_THRESHOLD = 1554.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_R_X = 20.0F * Setting::SCALE;
    static constexpr float TIP_OFFSET_L_X = -600.0F * Setting::SCALE;
      
    static constexpr int FONTSIZE=22;

};
}
#endif