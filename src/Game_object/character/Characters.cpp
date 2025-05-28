#include "Game_object/character/Characters.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Character{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractCreature))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractCreature);
    }

    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }

    Characters::Characters(float x, float y, float width, float height,float HPBarWidth)
        :boss_hitbox(x, y, width, height, false),
        HP_hb(x, y, width, HEALTH_BAR_HEIGHT, false),
        type(CharacterType::PLAYER),
        orgX(x),
        orgY(y)
    {
 
        shadow_a = 1.0F;
        bg_a = 1.0F;
        outline_a =  1.0F;
        block_offset = 0.0F;
        HP_anim_wait_timer=1.2F;
        health_width=HP_hb.Width();
        health_target_width=HP_hb.Width();

        animX=0.0F;
        animY=0.0F;
        shakeToggle=true;
        
        m_font.ChangeFontWeight(FontWeight::bold);
        m_font.SetFontSize(HP_FONTSIZE);

        IsFadeOut=false;
    }
    void Characters::updateHealthBar(){
        health_target_width=HP_hb.Width()*(current_HP/(float)max_HP);
        if(health_width-health_target_width!=0 && !HPDecrease){
            HP_anim_wait_timer-=DT();
            if(HP_anim_wait_timer<=0){
                HP_anim_wait_timer=1.2F;
                HPDecrease=true;
            }
        }
        else if (HPDecrease)
        {
            health_width=RUtil::Math::varlerp(health_width,health_target_width,9.0F,Setting::SCALE);
        }
        if(health_width==health_target_width){
            HPDecrease=false;
        }
    }
    void Characters::update_HP_and_power(){
        //hitbox update
        update_hb_pos();
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
                block_offset=RUtil::Math::interpolation_swing_out(36.0F*Setting::SCALE, 0.0F, t);
                block_num_scale=RUtil::Math::Apply(3.0F, 1.0F, std::pow(t, 3));
                block_icon_a=RUtil::Math::interpolation_powout2(0.0F, 1.0F, t);
                block_text_a=RUtil::Math::Apply(0.0F, 1.0F, std::pow(t, 5));
            }else if(block_num_scale!=1.0F){
                block_num_scale=RUtil::Math::varlerp(block_num_scale, 1.0F, 8.0F, 0.003F);
            }
            RUtil::Math::color_lerp_rgb
        }
        HP_hb.move(boss_hitbox.CenterX(), boss_hitbox.CenterY() - boss_hitbox.Height()/2.0F - HEALTH_BAR_HEIGHT*0.5F);
        boss_hitbox.update();
        HP_hb.update();
        updateHealthBar();
        updateAnimation();
        if (type==CharacterType::PLAYER){
            if(IsFadeOut){
                fadeTimer-=DT();
                img_color_a = RUtil::Math::interpolation_fade(1.0F,0.0F,fadeTimer/fadeTime);
            }
            else if(current_HP<=0){
                IsFadeOut=true;
            }
        }
        else{
            if(IsFadeOut){
                fadeTimer-=DT();
                img_color_a = RUtil::Math::interpolation_fade(0.0F,1.0F,fadeTimer/fadeTime);
            }
            else if(current_HP<=0){
                IsFadeOut=true;
            }
        }

        this->powers.update();
    }
    void Characters::render_HP_and_power(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float x=boss_hitbox.X(),
                    y=boss_hitbox.Y() + HP_offset_y/* - HEALTH_BAR_HEIGHT/2.0F */;
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
        }else{
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

    void Characters::setPosition(float x,float y){
        pos={x,y};
        boss_hitbox.move(x + boss_hitbox.Width()/2.0F, y + boss_hitbox.Height()/2.0F);
        HP_hb.move(boss_hitbox.CenterX(), y - HEALTH_BAR_HEIGHT*0.5F);
        orgX=x;
        orgY=y;
    }
    
    void Characters::useFastAttackAnimation(){
        animX=0.0F;
        animY=0.0F;
        animationTimer=0.4F;
        animation=Animation::ATTACK_FAST;
    }
    void Characters::useSlowAttackAnimation(){
        animX=0.0F;
        animY=0.0F;
        animationTimer=1.F;
        animation=Animation::ATTACK_SLOW;
    }
    void Characters::useHopAnimation(){
        animX=0.0F;
        animY=0.0F;
        vY=300.0F*Setting::SCALE;
        animationTimer=0.7F;
        animation=Animation::HOP;
    }
    void Characters::useJumpAnimation(){
        animX=0.0F;
        animY=0.0F;
        vY=500.0F*Setting::SCALE;
        animationTimer=0.7F;
        animation=Animation::JUMP;
    }
    void Characters::useStaggerAnimation(){
        if(animY==0.0F){
            animX=0.0F;
            animationTimer=0.3F;
            animation=Animation::STAGGER;
        }
    }
    void Characters::useFastShakeAnimation(float duration){
        if(animY==0.0F){
            animX=0.0F;
            animationTimer=duration;
            animation=Animation::STAGGER;
        }
    }
    void Characters::useShakeAnimation(float duration){
        if(animY==0.0F){
            animX=0.0F;
            animationTimer=duration;
            animation=Animation::SHAKE;
        }
    }
    void Characters::updateAnimation(){
        switch (animation) {
            case Animation::ATTACK_FAST:
                updateFastAttackAnimation();
                break;
            case Animation::ATTACK_SLOW:
                updateSlowAttackAnimation();
                break;
            case Animation::HOP:
                updateHopAnimation();
                break;
            case Animation::JUMP:
                updateJumpAnimation();
                break;
            case Animation::STAGGER:
                updateStaggerAnimation();
                break;
            case Animation::FAST_SHAKE:
                updateFastShakeAnimation();
                break;
            case Animation::SHAKE:
                updateShakeAnimation();
                break;
            case Animation::NONE:
                break;
            default:
                break;
        }
    }
    void Characters::updateFastAttackAnimation(){
        animationTimer-=DT();
        float targetPos=90.0F*Setting::SCALE;
        if(type!=CharacterType::PLAYER){
            targetPos=-targetPos;
        }
        if(animationTimer>0.5F){
            animX= targetPos*RUtil::Math::interpolation_expin(2.0F, 5.0F,(1.0F - animationTimer / 1.0F) * 2.0F);
        }
        else if (animationTimer<0.0F){
            animationTimer=0.0F;
            animX=0.0F;
            animation=Animation::NONE;
        }
        else{
            animX=RUtil::Math::interpolation_fade(0.0F, targetPos, animationTimer / 1.0F * 2.0F);
        }

    }
    void Characters::updateSlowAttackAnimation(){
        animationTimer-=DT();
        float targetPos=90.0F*Setting::SCALE;
        if(type!=CharacterType::PLAYER){
            targetPos=-targetPos;
        }
        if(animationTimer>0.5F){
            animX=targetPos*RUtil::Math::interpolation_expin(2.0F, 10.0F,(1.0F - animationTimer / 1.0F) * 2.0F);
        }
        else if (animationTimer<0.0F){
            animationTimer=0.0F;
            animX=0.0F;
            animation=Animation::NONE;
        }
        else{
            animX=RUtil::Math::interpolation_fade(0.0F, targetPos, animationTimer / 1.0F * 2.0F);
        }
    }
    void Characters::updateHopAnimation(){
        vY -= 17.0F * Setting::SCALE;
        animY += vY *DT();
        if (animY < 0.0F) {
           animationTimer = 0.0F;
           animY = 0.0F;
           animation=Animation::NONE;
        }
    }
    void Characters::updateJumpAnimation(){
        vY -= 17.0F * Setting::SCALE;
        animY += vY *DT();
        if (animY < 0.0F) {
           animationTimer = 0.0F;
           animY = 0.0F;
           animation=Animation::NONE;
        }
    }
    void Characters::updateStaggerAnimation(){
        if (animationTimer != 0.0F) {
            animationTimer -= DT();
            if (type!=CharacterType::PLAYER) {
               animX = RUtil::Math::interpolation_powout2(STAGGER_MOVE_SPEED, 0.0f, this->animationTimer / 0.3f);
            } else {
               animX = RUtil::Math::interpolation_powout2(-STAGGER_MOVE_SPEED, 0.0f, this->animationTimer / 0.3f);
            }
   
            if (animationTimer < 0.0F) {
               animationTimer = 0.0F;
               animX = 0.0F;
               vX = STAGGER_MOVE_SPEED;
               animation=Animation::NONE;
            }
         }
    }
    void Characters::updateFastShakeAnimation(){
        animationTimer -= DT();
        if (animationTimer < 0.0F) {
           animationTimer = 0.0F;
           animX = 0.0F;
           animation=Animation::NONE;
        } else if (shakeToggle) {
           animX += SHAKE_SPEED * DT();
           if (animX > SHAKE_THRESHOLD / 2.0F) {
              shakeToggle = !shakeToggle;
           }
        } else {
           animX -= SHAKE_SPEED * DT();
           if (animX < -SHAKE_THRESHOLD / 2.0F) {
              shakeToggle = !shakeToggle;
           }
        }
    }
    void Characters::updateShakeAnimation(){
        animationTimer -= DT();
        if (animationTimer < 0.0F) {
           animationTimer = 0.0F;
           animX = 0.0F;
           animation=Animation::NONE;
        } else if (shakeToggle) {
           animX += SHAKE_SPEED * DT();
           if (animX > SHAKE_THRESHOLD) {
              shakeToggle = !shakeToggle;
           }
        } else {
           animX -= SHAKE_SPEED * DT();
           if (animX < -SHAKE_THRESHOLD) {
              shakeToggle = !shakeToggle;
           }
        }
    }
    const Draw::NumberDrawer Characters::HP_num_drawer{HP_FONTSIZE, FontWeight::bold}, Characters::block_num_drawer{BLOCK_FONTSIZE, FontWeight::bold};
    const std::shared_ptr<Draw::ReTexture>  &Characters::_SHADOW_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/leftBg.png"),&Characters::_SHADOW_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/rightBg.png"),&Characters::_SHADOW_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/bodyBg.png"),
                                            &Characters::HEALTH_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/body7.png"),&Characters::HEALTH_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/left7.png"),&Characters::HEALTH_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/right7.png"),
                                            &Characters::BLOCK_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockBody3.png"),&Characters::BLOCK_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockRight3.png"),&Characters::BLOCK_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockLeft3.png"),
                                            &Characters::BLOCK_ICON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/block.png");

}