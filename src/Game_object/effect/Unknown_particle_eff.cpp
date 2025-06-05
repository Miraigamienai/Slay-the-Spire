#include "Game_object/effect/Unknown_particle_eff.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Random.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    static inline auto&IMG(){
        static auto&_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/intent/unknownL.png");
        return _IMG;
    }

    void Unknown_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        r2->draw(IMG(), x, y, 128.0F, 128.0F, angle, 64.0F, 64.0F, scale, scale);
    }

    void Unknown_particle_eff::update(){
        if(duration>0.5F) scale=RUtil::Math::interpolation_elastic_out(0.01F, target_scale, DUR-duration);
        else color_a=duration*2.0F;
        TimeGo();
    }

    void Unknown_particle_eff::Initial(float x, float y){
        is_done=false;
        scale=0.01F;
        color_a=1.0F;
        duration=DUR;
        this->x = x-64.0F;
        this->y = y-64.0F;
        switch(s_num++){
            case 0:
                color=RUtil::Random::GetRandomBoolean() ? RUtil::ToRGBA(RUtil::Colors::GOLDENROD) : RUtil::ToRGBA(RUtil::Colors::GOLD);
                this->x-=24.0F*Setting::SCALE;
                this->y-=RUtil::Random::GetRandomFloat(6.0F, 10.0F)*Setting::SCALE;
                angle=24.0F;
                target_scale=Setting::SCALE*0.8F;
                break;
            case 1:
                color=RUtil::WHITE;
                angle=0.0F;
                target_scale=Setting::SCALE*1.2F;
                break;
            default:
                color=RUtil::Random::GetRandomBoolean() ? RUtil::ToRGBA(RUtil::Colors::GOLDENROD) : RUtil::ToRGBA(RUtil::Colors::GOLD);
                this->x+=24.0F*Setting::SCALE;
                this->y-=RUtil::Random::GetRandomFloat(6.0F, 10.0F)*Setting::SCALE;
                angle=-24.0F;
                target_scale=Setting::SCALE*0.8F;
                break;
        }
        if(s_num>=3) s_num=0;
    }

    int Unknown_particle_eff::s_num=0;
} // namespace Effect

