#include "Game_object/character/Characters.hpp"

#include "RUtil/Some_Math.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Some_Math.hpp"
namespace Character{
    Characters::Characters(float x, float y, float width, float height,float HPBarWidth):boss_hitbox(x, y, width, height, false)
    ,HPBar_hitbox(x,y,HPBarWidth,HEALTH_BAR_HEIGHT,false)
    {
        Character_hb_width=width;
        HPBar_hb_width=HPBarWidth;
        HPBar_hb_a=1.0F;

        Character_hb_height=height;
        
        shadow_a = 1.0F;
        bg_a = 1.0F;
        outline_a =  1.0F;
        block_offset = 0.0F;
        HPDecreaseWaitTimer=1.2F;
        health_width=HPBar_hb_width;
        health_target_width=HPBar_hb_width;

        animX=0.0F;
        animY=0.0F;
        shakeToggle=true;

        pos={x,y};
        Character_hb_cX=x+Character_hb_width*0.5F;
        Character_hb_cY=y+Character_hb_height*0.5F;
        HPBar_hb_cX=x+Character_hb_width*0.5F;
        HPBar_hb_cY=y-HEALTH_BAR_HEIGHT*0.5F;
        orgX=x;
        orgY=y;
        
        m_font.ChangeFontWeight(FontWeight::bold);
        m_font.SetFontSize(FONTSIZE);
        font_scale=1.0F;

        fadeTimer=fadeTime;
        IsFadeOut=false;
    }
    void Characters::updateHealthBar(){
        health_target_width=HPBar_hb_width*(current_HP/(float)max_HP);
        if(health_width-health_target_width!=0 && !HPDecrease){
            HPDecreaseWaitTimer-=RUtil::Game_Input::delta_time();
            if(HPDecreaseWaitTimer<=0){
                HPDecreaseWaitTimer=1.2F;
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
    void Characters::update(){
        updateHealthBar();
        boss_hitbox.update();
        HPBar_hitbox.update();
        updateAnimation();
        pos.x=orgX+animX;
        pos.y=orgY+animY;
        if (KindOfCharacter==KindOfCharacter::PLAYER){
            if(IsFadeOut){
                fadeTimer-=RUtil::Game_Input::delta_time();
                FadeColorA = RUtil::Math::interpolation_fade(1.0F,0.0F,fadeTimer/fadeTime);
            }
            else if(current_HP<=0){
                IsFadeOut=true;
            }
        }
        else{
            if(IsFadeOut){
                fadeTimer-=RUtil::Game_Input::delta_time();
                FadeColorA = RUtil::Math::interpolation_fade(0.0F,1.0F,fadeTimer/fadeTime);
            }
            else if(current_HP<=0){
                IsFadeOut=true;
            }
        }

        
        
    }
    void Characters::render_HP(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float x=HPBar_hb_cX-HPBar_hb_width/2.0F,y=HPBar_hb_cY-HEALTH_BAR_HEIGHT/2.0F;

        //shadow
        r2->SetColor(0,shadow_a);
        r2->draw(_SHADOW_L, x-HEALTH_BAR_HEIGHT, y-HEALTH_BG_OFFSET, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        r2->draw(_SHADOW_B, x, y-HEALTH_BG_OFFSET, HPBar_hb_width, HEALTH_BAR_HEIGHT);
        r2->draw(_SHADOW_R, x+HPBar_hb_width, y-HEALTH_BG_OFFSET, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        if(current_HP!=max_HP){
            //background
            r2->SetColor(0,bg_a);
            r2->draw(HEALTH_BAR_L, x-HEALTH_BAR_HEIGHT, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
            r2->draw(HEALTH_BAR_B, x, y+HEALTH_BAR_OFFSET_Y, HPBar_hb_width, HEALTH_BAR_HEIGHT);
            r2->draw(HEALTH_BAR_R, x+HPBar_hb_width, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
        }
        if(health_target_width!=0.0F){
            //hp just move //orange
            if(health_width-health_target_width!=0){
                r2->SetColor(ORG_BAR_COLOR,HPBar_hb_a);
                r2->draw(HEALTH_BAR_B, x+health_target_width, y+HEALTH_BAR_OFFSET_Y, health_width-health_target_width, HEALTH_BAR_HEIGHT);
                r2->draw(HEALTH_BAR_R, x+health_width, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
            }
            //hp //red //if have block,blue
            r2->SetColor(current_Block>0?BLUE_BAR_COLOR:RED_BAR_COLOR,HPBar_hb_a);
            r2->draw(HEALTH_BAR_L, x-HEALTH_BAR_HEIGHT, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
            r2->draw(HEALTH_BAR_B, x, y+HEALTH_BAR_OFFSET_Y, health_target_width, HEALTH_BAR_HEIGHT);
            r2->draw(HEALTH_BAR_R, x+health_target_width, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);

        }
        //check HPBar_hb_a cuz outline_a != HPBar_hb_a
        if(current_Block!=0&&HPBar_hb_a!=0.0F){
            //reder block outline
            r2->SetColor(BLOCK_COLOR,outline_a);
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
            r2->draw(BLOCK_BAR_L, x-HEALTH_BAR_HEIGHT, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
            r2->draw(BLOCK_BAR_B, x, y+HEALTH_BAR_OFFSET_Y, HPBar_hb_width, HEALTH_BAR_HEIGHT);
            r2->draw(BLOCK_BAR_R, x+HPBar_hb_width, y+HEALTH_BAR_OFFSET_Y, HEALTH_BAR_HEIGHT, HEALTH_BAR_HEIGHT);
            r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        }
        r2->SetColor(-1,1);
        m_font.render_center(r2, std::to_string(current_HP)+"/"+std::to_string(max_HP), HPBar_hb_cX, HPBar_hb_cY+HEALTH_BAR_OFFSET_Y, font_scale*Setting::SCALE);
        if(current_Block!=0&&HPBar_hb_a!=0.0F){
            //block icon
            r2->SetColor(BLOCK_COLOR,1);
            r2->draw(BLOCK_ICON, x+BLOCK_ICON_XY-32.0F, y+BLOCK_ICON_XY-32.0F+block_offset, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
            r2->SetColor(-1,1);
            m_font.render_center(r2, std::to_string(current_Block), x+BLOCK_ICON_XY, y+BLOCK_ICON_XY+block_offset, font_scale*Setting::SCALE);
        }
    }
    void Characters::setPosition(float x,float y){
        pos={x,y};
        Character_hb_cX=x+Character_hb_width*0.5F;
        Character_hb_cY=y+Character_hb_height*0.5F;
        HPBar_hb_cX=x+Character_hb_width*0.5F;
        HPBar_hb_cY=y-HEALTH_BAR_HEIGHT*0.5F;
        orgX=x;
        orgY=y;
    }
    void Characters::setHPBarWidth(float width){
        HPBar_hb_width=width;
    };
    
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
        animationTimer-=RUtil::Game_Input::delta_time();
        float targetPos=90.0F*Setting::SCALE;
        if(!isPlayer()){
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
        animationTimer-=RUtil::Game_Input::delta_time();
        float targetPos=90.0F*Setting::SCALE;
        if(!isPlayer()){
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
        animY += vY *RUtil::Game_Input::delta_time();
        if (animY < 0.0F) {
           animationTimer = 0.0F;
           animY = 0.0F;
           animation=Animation::NONE;
        }
    }
    void Characters::updateJumpAnimation(){
        vY -= 17.0F * Setting::SCALE;
        animY += vY *RUtil::Game_Input::delta_time();
        if (animY < 0.0F) {
           animationTimer = 0.0F;
           animY = 0.0F;
           animation=Animation::NONE;
        }
    }
    void Characters::updateStaggerAnimation(){
        if (animationTimer != 0.0F) {
            animationTimer -= RUtil::Game_Input::delta_time();
            if (!isPlayer()) {
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
        animationTimer -= RUtil::Game_Input::delta_time();
        if (animationTimer < 0.0F) {
           animationTimer = 0.0F;
           animX = 0.0F;
           animation=Animation::NONE;
        } else if (shakeToggle) {
           animX += SHAKE_SPEED * RUtil::Game_Input::delta_time();
           if (animX > SHAKE_THRESHOLD / 2.0F) {
              shakeToggle = !shakeToggle;
           }
        } else {
           animX -= SHAKE_SPEED * RUtil::Game_Input::delta_time();
           if (animX < -SHAKE_THRESHOLD / 2.0F) {
              shakeToggle = !shakeToggle;
           }
        }
    }
    void Characters::updateShakeAnimation(){
        animationTimer -= RUtil::Game_Input::delta_time();
        if (animationTimer < 0.0F) {
           animationTimer = 0.0F;
           animX = 0.0F;
           animation=Animation::NONE;
        } else if (shakeToggle) {
           animX += SHAKE_SPEED * RUtil::Game_Input::delta_time();
           if (animX > SHAKE_THRESHOLD) {
              shakeToggle = !shakeToggle;
           }
        } else {
           animX -= SHAKE_SPEED * RUtil::Game_Input::delta_time();
           if (animX < -SHAKE_THRESHOLD) {
              shakeToggle = !shakeToggle;
           }
        }
    }
    const std::shared_ptr<Draw::ReTexture>  &Characters::_SHADOW_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/leftBg.png"),&Characters::_SHADOW_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/rightBg.png"),&Characters::_SHADOW_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/bodyBg.png"),
                                            &Characters::HEALTH_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/body7.png"),&Characters::HEALTH_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/left7.png"),&Characters::HEALTH_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/right7.png"),
                                            &Characters::BLOCK_BAR_B=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockBody3.png"),&Characters::BLOCK_BAR_R=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockRight3.png"),&Characters::BLOCK_BAR_L=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockLeft3.png"),
                                            &Characters::BLOCK_ICON=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/block.png");

}