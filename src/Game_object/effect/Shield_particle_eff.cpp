#include "Game_object/effect/Shield_particle_eff.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"

namespace Effect{
    static inline auto&IMG(){
        static auto&_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/intent/defend.png");
        return _IMG;
    }

    void Shield_particle_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::WHITE, color_a);
        r2->draw(IMG(), x, y, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, scale, scale);
    }

    void Shield_particle_eff::update(){
        scale+=DT*1.1F*Setting::SCALE;
        if(duration>1.0F) color_a=RUtil::Math::interpolation_fade(0.0F, 0.3F, DUR-duration);
        else color_a=RUtil::Math::interpolation_fade(0.3F, 0.0F, 1.0F-duration);
        TimeGo();
    }
}