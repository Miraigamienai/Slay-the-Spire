#ifndef GAME_OBJECT_CHARACTER_CHARACTERS
#define GAME_OBJECT_CHARACTER_CHARACTERS
#include "Draw/Draw_2D.hpp"
#include "RUtil/Hitbox.hpp"
#include "RUtil/Image_book.hpp"
#include "WindowSize.hpp"
#include "RUtil/Some_Math.hpp"

//fwd decl
struct Damage_info;

namespace Character{
enum class Animation
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
class Characters
{
public:
    Characters(float x, float y, float width, float height,float HPBarWidth);
    virtual ~Characters()=default;
    virtual void damage(const Damage_info& damage_info)=0;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2) const =0;
    void update();
    void setPosition(glm::vec2 vec,int WIDTH,int HIGHT);
    void setPosition(float x,float y);
    void setHPBarWidth(float width);
    bool hovered()const{return boss_hitbox.Hovered();}
    float GetcX()const{return Character_hb_cX;}
    float GetcY()const{return Character_hb_cY;}
    bool IsDie()const{return current_HP<=0;}//for test
    void AddBlock(int num){current_Block+=num;};
    void setBlock(int num){current_Block=num;};
    void AddHP(int num){current_HP+=num;};
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

protected:
    int max_HP,current_HP,current_Block;
    void render_HP(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    glm::vec2 getPosition()const{ return pos;};
    KindOfCharacter KindOfCharacter;
private:
    RUtil::Hitbox boss_hitbox;
    RUtil::Hitbox HPBar_hitbox;
    glm::vec2 pos={0,0};
    float HPBar_hb_width,HPBar_hb_height,HPBar_hb_a,HPBar_hb_cX,HPBar_hb_cY;
    float Character_hb_cX,Character_hb_cY,
          Character_hb_width,Character_hb_height;
    float animX,animY,vX,vY,orgX,orgY;
    float HPDecreaseWaitTimer,animationTimer;
    bool HPDecrease=false,shakeToggle;
    Animation animation=Animation::NONE;
    float shadow_a,bg_a,outline_a,health_width,health_target_width,block_offset;
    static const std::shared_ptr<Draw::ReTexture>  &_SHADOW_L,&_SHADOW_R,&_SHADOW_B,
                                                &HEALTH_BAR_B,&HEALTH_BAR_L,&HEALTH_BAR_R,
                                                &BLOCK_BAR_B,&BLOCK_BAR_R,&BLOCK_BAR_L,
                                                &BLOCK_ICON;
    static constexpr int ORG_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(1.0F,0.5F,0.0F),BLUE_BAR_COLOR=0x31568c00,RED_BAR_COLOR=RUtil::Math::GetColorUint32_RGB(0.8F,0.05F,0.05F),BLOCK_COLOR=RUtil::Math::GetColorUint32_RGB(0.6F,0.93F,0.98F);
    static constexpr float HEALTH_BAR_HEIGHT=20.0F*Setting::SCALE,HEALTH_BAR_OFFSET_Y=-28.0F*Setting::SCALE,HEALTH_BG_OFFSET=28.0F*Setting::SCALE,BLOCK_ICON_XY=-14.0F*Setting::SCALE;
    static constexpr float SHAKE_THRESHOLD = Setting::SCALE * 8.0F;
    static constexpr float SHAKE_SPEED = 150.0F * Setting::SCALE;
    static constexpr float STAGGER_MOVE_SPEED = 20.0F * Setting::SCALE;
};
}
#endif