#include <algorithm>

#include "Game_object/effect/Vertical_aura.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto&GetIMG()noexcept(noexcept(RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_verticalAura))){
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_verticalAura);
    }

    static inline Uint32 ColorJitter(Uint32 color,float amount){
        int r = (color&0xff000000)>>24;
        int g = (color&0x00ff0000)>>16;
        int b = (color&0x0000ff00)>>8;
        r = std::clamp(r + static_cast<int>(RUtil::Random::GetRandomFloat(-amount,amount) * 255), 0, 255);
        g = std::clamp(g + static_cast<int>(RUtil::Random::GetRandomFloat(-amount,amount) * 255), 0, 255);
        b = std::clamp(b + static_cast<int>(RUtil::Random::GetRandomFloat(-amount,amount) * 255), 0, 255);
        return static_cast<Uint32>((r<<24)|(g<<16)|(b<<8));
    }

    void Vertical_aura::Initial(Uint32 color, float x, float y){
        this->is_done=false;
        this->x = x + RUtil::Random::GetRandomFloat(-200.0F, 200.0F)*Setting::SCALE - static_cast<float>(GetIMG()->GetRegionWidth())/2.0F;
        this->y = y + RUtil::Random::GetRandomFloat(-200.0F, 200.0F)*Setting::SCALE - static_cast<float>(GetIMG()->GetRegionHeight())/2.0F;
        this->speed_y = RUtil::Random::GetRandomFloat(-300.0F, 300.0F)*Setting::SCALE;
        this->wait_timer = RUtil::Random::GetRandomFloat(0.0F, 0.2F);
        this->scale = RUtil::Random::GetRandomFloat(0.6F, 1.7F)*Setting::SCALE;
        this->color = ColorJitter(color, 0.1F);
        this->color_a = 0.0F;
        this->duration=1.0F;
    }
    
    
    void Vertical_aura::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(this->color, this->color_a);
        r2->draw(GetIMG(), this->x, this->y, static_cast<float>(GetIMG()->GetRegionWidth()), static_cast<float>(GetIMG()->GetRegionHeight()), 0.0F, static_cast<float>(GetIMG()->GetRegionWidth())/2.0F, static_cast<float>(GetIMG()->GetRegionHeight())/2.0F, this->scale, this->scale);
    }

    void Vertical_aura::update(){
        if(0.0F < wait_timer){
            wait_timer-=DT;
        }else{
            this->y+=speed_y*DT;
            if(duration<0.8F){
                //duration[0.8F,0.0F] -> fadeout
                //color_a: 0.5F -> 0.0F
                this->color_a=RUtil::Math::interpolation_fade(0.0F, 0.5F, this->duration/0.8F);
            }else{
                //duration[1.0F,0.8F] -> fadein
                //color_a: 0.0F -> 0.5F
                this->color_a=RUtil::Math::interpolation_fade(0.5F, 0.0F, (this->duration-0.8F)/0.2F);
            }
            TimeGo();
        }
    }
} // namespace Effect
