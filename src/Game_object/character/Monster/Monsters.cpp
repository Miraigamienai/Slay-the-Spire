#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/Damage_info.hpp"
#include "Draw/Draw_2D.hpp"

#include "RUtil/Random.hpp"

namespace Monster
{
    Monsters::Monsters(float offset_x, float offset_y, float width, float height, 
        float hb_offset_x, float hb_offset_y, int HP_min, int HP_max, 
        const std::shared_ptr<Draw::ReTexture> &img)
    {

    }
    

    void Monsters::damage(const Damage_info& damage_info){
        if(current_Block>=damage_info.dmg){
            current_Block-=damage_info.dmg;
            useStaggerAnimation();
            return;
        }
        else if (current_Block){
            current_Block=0;
            current_HP-=damage_info.dmg-current_Block;
        }
        else if (current_HP){
            if(current_HP>damage_info.dmg){
                current_HP-=damage_info.dmg;
            }
            else if (current_HP<=damage_info.dmg){
                current_HP=0;
            }
        }
        useStaggerAnimation();
    }
    void Monsters::setHP(int min,int max){
        this->max_HP=max-int(RUtil::Random::GetRandomFloat(0.0F,max-min+1));
        this->current_HP=max_HP;
    }

    void Monsters::update(){
        update_HP_and_power();
        update_animation();
        //fade update
        if(IsDie() && dying_fade_timer!=0.0F){
            dying_fade_timer-=RUtil::Game_Input::delta_time();
            if(dying_fade_timer<0.0F) dying_fade_timer=0.0F;
            img_color_a = RUtil::Math::varlerp(img_color_a, 0.0F, 3.0F, 0.005F);
        }
    }

    void Monsters::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(RUtil::WHITE, img_color_a);
        r2->draw(img, getAnimX()+orgX, getAnimY()+orgY, GetWidth(), GetHeight()); 
        render_HP_and_power(r2);
    }
} // namespace Monster