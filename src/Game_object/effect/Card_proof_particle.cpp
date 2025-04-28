#include "Game_object/effect/Card_proof_particle.hpp"
#include "RUtil/All_Image.hpp"//for loading img
#include "RUtil/Random.hpp"//ramdom something
#include "RUtil/Some_Math.hpp"
#include "Draw/Atlas_Region.hpp"//smoke img
#include "Draw/Draw_2D.hpp"

#include "WindowSize.hpp"//Setting::Scale

namespace Effect{
    void Card_proof_particle::Initial(const float x,const float y){
        is_done=false;
        scale=Setting::SCALE;
        this->flip_x=RUtil::Random::GetRandomBoolean();
        this->flip_y=RUtil::Random::GetRandomBoolean();
        switch(RUtil::Random::GetRandomInt(3)){
            case 0:img=&SMOKE1;
            case 1:img=&SMOKE2;
            default:img=&SMOKE3;
        }
        this->duration=DUR;
        this->delay_time=RUtil::Random::GetRandomFloat(0.0F, 0.1F);
        float jiltter=   RUtil::Random::GetRandomFloat(-160.0F, 160.0F) * Setting::SCALE;
        this->x= x - static_cast<float>((*img)->GetRegionWidth())/2.0F + jiltter;
        jiltter = RUtil::Random::GetRandomFloat(-180.0F, 180.0F) * Setting::SCALE;
        this->y= y - static_cast<float>((*img)->GetRegionHeight())/2.0F + jiltter;
        jiltter = RUtil::Random::GetRandomFloat(0.4F, 0.8F);
        this->color=RUtil::Math::GetColorUint32_RGB(jiltter+0.05F, jiltter, jiltter+0.05F);
        rotate_speed=RUtil::Random::GetRandomFloat(-400.0F, 400.0F) * Setting::SCALE;
        x_speed=RUtil::Random::GetRandomFloat(-170.0F, 170.0F) * Setting::SCALE;
        y_speed=RUtil::Random::GetRandomFloat(-170.0F, 170.0F) * Setting::SCALE;
        this->scale=RUtil::Random::GetRandomFloat(0.8F, 2.5F) * Setting::SCALE;
        this->rotation=RUtil::Random::GetRandomFloat(0.0F, 360.0F);
        this->color_a=0.0F;
    }
    
    void Card_proof_particle::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(this->color, this->color_a);
        r2->draw(*img, this->x, this->y, (float)(*img)->GetRegionWidth(), (float)(*img)->GetRegionHeight(), this->rotation, (float)(*img)->GetRegionWidth()/2.0F, (float)(*img)->GetRegionHeight()/2.0F, this->scale, this->scale, flip_x, flip_y);
    }

    void Card_proof_particle::update(){
        if(this->delay_time>0.0F)
            this->delay_time-=DT;
        else{
            this->rotation+=rotate_speed*DT;
            this->x+=x_speed*DT;
            this->y+=y_speed*DT;
            this->scale+=5.0F*DT;
            if(this->duration>DUR/2.0F){
                this->color_a=RUtil::Math::interpolation_powout2(0.0F, 0.7F, 1.0F-this->duration);//0.4F->0.7F
            }else{
                this->color_a=RUtil::Math::interpolation_fade(0.0F, 0.7F, this->duration*2.0F);//0.6F->0.0F
            }

            TimeGo();
        }
    }

    const std::shared_ptr<Draw::Atlas_Region> &Card_proof_particle::SMOKE1=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1),
                                              &Card_proof_particle::SMOKE2=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke2),
                                              &Card_proof_particle::SMOKE3=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke3);
}
