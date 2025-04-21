#include <GL/glew.h> 

#include "Game_object/effect/End_turn_button_glow.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Effect
{
    void End_turn_button_glow::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA,GL_ONE);
        r2->SetColor(-1,color_a);
        r2->draw(img, *button_x-128.0F, *button_y-128.0F, 256.0F, 256.0F, 0.0F, 128.0F, 128.0F, this->scale, this->scale);
    }
    void End_turn_button_glow::update(){
        this->TimeGo();
        this->scale=RUtil::Math::interpolation_fade(Setting::SCALE, 2.0F*Setting::SCALE, 1.0F-this->duration/2.0F);
        this->color_a=RUtil::Math::interpolation_fade(0.4F, 0.0F, 1.0F-this->duration/2.0F)/2.0F;
    }
    const std::shared_ptr<Draw::ReTexture> End_turn_button_glow::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image//topPanel/endTurnButtonGlow.png");
} // namespace Effect
