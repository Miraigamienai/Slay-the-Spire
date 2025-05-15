#include "Game_object/effect/Damage_impact_curvy_eff.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "WindowSize.hpp"

namespace Effect{
    Damage_impact_curvy_eff::Damage_impact_curvy_eff(glm::vec2 pos, Uint32 color_rgb)
        :now_vec_pos(0),
        now_vec_size(0),
        pos(pos),
        start_duration(RUtil::Random::GetRandomFloat(0.8F, 1.1F)),
        current_speed(RUtil::Random::GetRandomFloat(400.0F, 900.0F)*Setting::SCALE),
        speed_start(current_speed),
        speed_target(RUtil::Random::GetRandomFloat(0.1F, 2.0F)*Setting::SCALE),
        wave_speed(RUtil::Random::GetRandomFloat(-20.0F, 20.0F)),
        wave_height(RUtil::Random::GetRandomFloat(5.0F, 30.0F)),
        angle(RUtil::Random::GetRandomFloat(0.0F, 360.0F))
    {
        this->duration=start_duration;
        this->color=color;
        this->scale=Setting::SCALE;
    }

    void Damage_impact_curvy_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        float temp_a=COLOR_ALPHA;
        for(int i=0,j=now_vec_pos;i<now_vec_size;++i,++j){
            if(j>=MAX_VEC_SIZE) j=0;
            r2->SetColor(this->color, temp_a);
            temp_a*=0.95F;
            auto&img=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_combat_strikeLine3);
            r2->draw(img, pos_vec[j].x, pos_vec[j].y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), this->angle, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale*2.0F, this->scale*2.0F);
        }
    }

    void Damage_impact_curvy_eff::update(){
        if(now_vec_size<MAX_VEC_SIZE){
            pos_vec[RUtil::Math::SimpleRangeChange(now_vec_pos+now_vec_size, MAX_VEC_SIZE)]=this->pos;
            ++now_vec_size;
        }else{
            pos_vec[now_vec_pos++]=this->pos;//remove oldest.
            if(now_vec_pos>=MAX_VEC_SIZE) now_vec_pos=0;
        }
        this->current_speed=RUtil::Math::Apply(speed_start, speed_target, 1.0F-sqrt(duration/start_duration));
        glm::vec2 unit={std::cos(glm::radians(angle)), std::sin(glm::radians(angle))};
        this->pos += unit * current_speed * DT;
        this->angle+=std::cos(duration*wave_speed)*wave_height*DT*60.0F;
        this->scale=Setting::SCALE*0.75F*(duration/start_duration);
        if(duration<start_duration/2.0F){
            this->color_a=this->duration/(start_duration/2.0F);
        }
        TimeGo();
    }
}