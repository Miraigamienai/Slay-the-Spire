#include <glm/vec2.hpp>

#include "Game_object/effect/Shine_particle.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"

namespace Effect{
    
    static inline auto&GetIMG(bool img_bool){
        if(img_bool) return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_strikeLine2);
        return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_glowSpark2);
    }

    void Shine_particle::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(this->color, this->color_a);
        auto &img=GetIMG(img_bool);
        r2->draw(img, this->x, this->y, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), this->angle, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, this->scale*RUtil::Random::GetRandomFloat(0.7F,1.3F), this->scale*RUtil::Random::GetRandomFloat(0.7F,1.3F));
    }

    void Shine_particle::update(){
        this->speed_y-= GRAVITY*this->scale*DT;
        this->x+=this->speed_x*DT;
        this->y+=this->speed_y*DT;
        this->angle=RUtil::Math::GetDegress(glm::vec2{speed_x, speed_y});
        if(this->y<this->floor){
            this->speed_y*=-0.75F;//reverse and slow
            this->y=this->floor+0.1F;//let the y bigger than floor
            this->speed_x*=1.1F;
        }

        if(this->duration>0.9F){//duration (0.9F,1.0F)
            //color_a to 1.0F;
            this->color_a=RUtil::Math::interpolation_fade(0.0F, 1.0F, (1.0F-this->duration)*10.0F);
        }else{
            //color_a to 0.0F;
            this->color_a=RUtil::Math::interpolation_powout2(0.0F, 1.0F, this->duration);
        }
        TimeGo();
    }

    void Shine_particle::Initial(float x, float y,float jitter){
        this->is_done=false;
        this->img_bool=RUtil::Random::GetRandomBoolean();
        auto &img=GetIMG(img_bool);
        this->x= x - (float)img->GetRegionWidth()/2.0F + RUtil::Random::GetRandomFloat(-jitter, jitter)*Setting::SCALE;
        this->y= y - (float)img->GetRegionHeight()/2.0F+ RUtil::Random::GetRandomFloat(-jitter, jitter)*Setting::SCALE;
        this->color=RUtil::Math::GetColorUint32_RGB(
            RUtil::Random::GetRandomFloat(0.5F,1.0F),
            RUtil::Random::GetRandomFloat(0.4F,0.6F),
            RUtil::Random::GetRandomFloat(0.0F,0.2F)
        );
        this->color_a=0.0F;
        this->angle=RUtil::Random::GetRandomFloat(0.0F,360.0F);
        this->duration=RUtil::Random::GetRandomFloat(0.5F,1.0F);
        this->scale=RUtil::Random::GetRandomFloat(0.5F,2.0F)*Setting::SCALE;
        this->speed_x=RUtil::Random::GetRandomFloat(-900.0F,900.0F)*Setting::SCALE;
        this->speed_y=RUtil::Random::GetRandomFloat(-500.0F,1000.0F)*Setting::SCALE;
        this->floor=RUtil::Random::GetRandomFloat(100.0F,250.0F)*Setting::SCALE;
    }
}