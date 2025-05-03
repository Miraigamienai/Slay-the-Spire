#include "Game_object/effect/Slash_eff.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    const std::shared_ptr<Draw::ReTexture> &Slash_eff::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/slash_1.png");

    void Slash_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        using namespace RUtil;
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(this->color2,this->color_a);
        r2->draw(IMG, this->pos.x, this->pos.y, 128.0F, 128.0F, this->angle, 64.0F, 64.0F, this->m_scale.x*0.4F*Random::GetRandomFloat(0.95F,1.05F)*Setting::SCALE, this->m_scale.y*0.7F*Random::GetRandomFloat(0.95F,1.05F)*Setting::SCALE);
        r2->SetColor(this->color,this->color_a);
        r2->draw(IMG, this->pos.x, this->pos.y, 128.0F, 128.0F, this->angle, 64.0F, 64.0F, this->m_scale.x*0.7F*Random::GetRandomFloat(0.95F,1.05F)*Setting::SCALE, this->m_scale.y*Random::GetRandomFloat(0.95F,1.05F)*Setting::SCALE);
    }

    void Slash_eff::update(){
        using namespace RUtil;
        if(this->duration>DUR/2.0F){
            const float the_a=(this->duration/(DUR/2.0F))-1.0F;
            this->color_a=Math::interpolation_exp10in(0.8F, 0.0F, the_a);
            this->m_scale.x=this->m_scale.y=Math::interpolation_exp10in(scale, 0.1F, the_a);
            this->pos=Math::interpolation_fade(this->target_pos, this->start_pos, the_a);
        }else{
            const float the_a=(this->duration/(DUR/2.0F));
            this->m_scale.x=Math::Apply(0.5F, scale, std::pow(the_a, 2));
            this->color_a=Math::Apply(0.0F, 0.8F, std::pow(the_a, 5));
        }
        TimeGo();
    }

    void Slash_eff::Initial(glm::vec2 pos, glm::vec2 distant, float angle, float target_scale, Uint32 color1, Uint32 color2){
        this->is_done=false;
        this->pos=pos-64.0F- distant/2.0F*Setting::SCALE;
        this->start_pos=this->pos;
        this->target_pos=pos-64.0F;
        this->color=color1;
        this->color2=color2;
        this->color_a=0.0F;
        this->duration=DUR;
        this->scale=target_scale;//scale is target_scale
        this->m_scale.x=0.01F;
        this->m_scale.y=0.01F;
        this->angle=angle;
    }
}