#include "Game_object/effect/Flash_attack_effect.hpp"
#include "Game_object/Damage_info.hpp"//Include for AttackType enum
#include "RUtil/All_Image.hpp"//for loading img
#include "RUtil/Random.hpp"//random rotation
#include "RUtil/ColorValuesOnly.hpp"//white color
#include "RUtil/Some_Math.hpp"//math fade
#include "Draw/Atlas_Region.hpp"//img
#include "Draw/Draw_2D.hpp"//for rendering
#include "WindowSize.hpp"//Setting::SCALE

#include "Util/Logger.hpp"

namespace Effect{
    static inline auto& loadimg(const AttackType type){
        switch(type){
            case AttackType::blunt_heavy:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_blunt_heavy);
            case AttackType::blunt_light:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_blunt_light);
            case AttackType::fire:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_fire);
            case AttackType::poison:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_poison);
            case AttackType::shield:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_shield);
            case AttackType::slash_diagonal:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_slash_light);
            case AttackType::slash_heavy:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_slash_heavy);
            case AttackType::slash_horizontal:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_slash_horizontal);
            case AttackType::slash_vertical:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_slash_vertical);
            default:return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_attack_slash_light);
        }
    }

    void Flash_attack_effect::Initial(const float x,const float y,const AttackType type){
        if(type==AttackType::NONE) LOG_ERROR("Try to draw NONE AttackType");
        auto&img=loadimg(type);
        this->x = x - (float)img->GetRegionWidth() / 2.0F;
        this->y = y - (float)img->GetRegionHeight() / 2.0F;
        this->type=type;
        this->duration=DUR;
        this->scale=Setting::SCALE;
        this->rotation=(type==AttackType::blunt_heavy?RUtil::Random::GetRandomFloat(0.0F,360.0F):0.0F);
        this->is_done=false;
        if(type==AttackType::shield){
            this->color_a=RUtil::Math::interpolation_fade(1.0F, 0.0F, 0.75F);
            this->target_y=this->y;
            this->y+=80.0F*Setting::SCALE;
            this->start_y=this->y;
        }else{
            this->color_a=1.0F;
            this->target_y=this->start_y=this->y;
        }
    }
    void Flash_attack_effect::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        auto &img=loadimg(type);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(RUtil::Colors::WHITE,color_a);
        r2->draw(img, this->x, this->y, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), this->rotation, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, this->scale, this->scale);
    }
    void Flash_attack_effect::update(){
        if(this->type==AttackType::shield){
            if(this->duration<0.2F){
                this->color_a=duration*5.0F;//1.0F->0.0F
            }else{
                this->color_a=RUtil::Math::interpolation_fade(1.0F, 0.0F, this->duration*(0.75F/DUR));//dur:0.75F->0.25F //color_a:0.1F->0.9F
            }
            this->y=RUtil::Math::interpolation_exp10in(this->target_y,this->start_y,this->duration/DUR);//because duration goes from big to small, we need to swap target_y and start_y for the interpolation work correctly.
        }else{
            if(this->duration<DUR/2.0F){
                this->color_a=this->duration/(DUR/2.0F);
            }
        }
        TimeGo();
    }
}