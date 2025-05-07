#include <math.h>

#include "Game_object/dungeon/Grid_screen_action/Render_arrow.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Dungeon{
namespace GridScreenAction{
    void Render_arrow::arrow_render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        float now_x=START_X;
        r2->SetColor(RUtil::WHITE);
        float scale=0.8F + (std::cos(oscillate_timer)+1.0F)/8.0F;
        r2->draw(ARROW, now_x, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F - 32.0F, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, scale, scale);
        
        now_x+=64.0F*Setting::SCALE;
        scale=0.8F + (std::cos(oscillate_timer-0.8F)+1.0F)/8.0F;
        r2->draw(ARROW, now_x, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F - 32.0F, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, scale, scale);
        
        now_x+=64.0F*Setting::SCALE;
        scale=0.8F + (std::cos(oscillate_timer-1.6F)+1.0F)/8.0F;
        r2->draw(ARROW, now_x, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F - 32.0F, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, scale, scale);
    }

    const std::shared_ptr<Draw::ReTexture> &Render_arrow::ARROW=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/upgradeArrow.png");
}
}