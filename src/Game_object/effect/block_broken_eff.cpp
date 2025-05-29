#include "Game_object/effect/block_broken_eff.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Effect{
    void block_broken_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(COLOR, this->color_a);
        r2->draw(BLOCK_L_IMG, x+offset_x, y+offset_y, 64.0F, 64.0F, angle, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
        r2->draw(BLOCK_R_IMG, x-offset_x, y+offset_y, 64.0F, 64.0F, -angle, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
    }
    void block_broken_eff::update(){
        if(duration<0.7F){
            const float t = 1.0F - duration/0.7F;
            offset_x = RUtil::Math::interpolation_circle_out(0.0F, -15.0F*Setting::SCALE, t);
            offset_y = RUtil::Math::interpolation_fade(0.0F, -10.0F*Setting::SCALE, t);
            color_a = RUtil::Math::interpolation_fade(1.0F, 0.0F, t);
            angle += DT*55.0F;
        }else{
            offset_x-=DT*5.0F*Setting::SCALE;
            angle+=DT*5.0F;
        }
        TimeGo();
    }
    
    const std::shared_ptr<Draw::ReTexture> &block_broken_eff::BLOCK_L_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockL.png"),
                                           &block_broken_eff::BLOCK_R_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/combat/blockR.png");
}
