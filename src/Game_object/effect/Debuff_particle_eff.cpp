#include "Game_object/effect/Debuff_particle_eff.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect
{
    using namespace RUtil;

    template <int N>
    static inline auto &IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/intent/buffVFX" + std::to_string(N) + ".png");
        return IMG;
    }

    static inline auto& IMG(int img_type){
        switch(img_type){
            case 0:return IMG<1>();
            case 1:return IMG<2>();
            default:return IMG<3>();
        }
    }

    void Debuff_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(RUtil::WHITE, color_a);
        r2->draw(IMG(img_type), x, y, 32.0F, 32.0F, angle, 16.0F, 16.0F, scale, scale);
    }

    void Debuff_particle_eff::update(){
        if(clockwise) angle+=DT*120.0F;
        else angle-=DT*120.0F;
        if(duration>3.0F){
            color_a=Math::interpolation_fade(0.0F, 1.0F, DUR-duration);
        }else if(duration<1.0F){
            color_a=Math::interpolation_fade(1.0F, 0.0F, 1.0F - duration);
            scale=Math::interpolation_fade(Setting::SCALE, 0.0F, 1.0F - duration);
        }

        if(duration>2.0F) scale=Math::Apply(0.0F, Setting::SCALE, Math::BounceOut((DUR - duration)/2.0F));
        TimeGo();
    }

    void Debuff_particle_eff::Initial(float x, float y){
        is_done=false;
        duration=DUR;
        color_a=0.0F;
        scale=0.0F;
        this->x = x-16.0F + Random::GetRandomFloat(-36.0F, 36.0F)*Setting::SCALE;
        this->y = y-16.0F + Random::GetRandomFloat(-36.0F, 36.0F)*Setting::SCALE;
        angle=Random::GetRandomFloat(0.0F, 360.0F);
        clockwise=Random::GetRandomBoolean();
        img_type=s_img_type++;
        if(s_img_type>=3)s_img_type=0;
    }

    int Debuff_particle_eff::s_img_type = 0;
} // namespace Effect
