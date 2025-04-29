#include "Draw/Text_box.hpp"
#include "Draw/Text_layout.hpp"
#include "RUtil/ColorValuesOnly.hpp"//gold color
#include "RUtil/Image_book.hpp"//for loading img
#include "Draw/ReTexture.hpp"//img
#include "Draw/Draw_2D.hpp"//for rendering
namespace Draw
{
    Text_box::Text_box(const std::shared_ptr<Text_layout> &title,const std::shared_ptr<Text_layout> &body,const float x,const float y):title(title),body(body),x(x),y(y){
        title->SetFontSize(TITLE_FONT_SIZE);
        title->SetFontColor(RUtil::GOLD_COLOR);
        // title->ChangeFontWeight(FontWeight::bold);
        body->SetFontSize(BODY_FONT_SIZE);
        body->SetFontColor(BASE_COLOR);
    }

    void Text_box::render(const std::shared_ptr<Draw_2D> &r2)const{
        render_box(r2);
    }
    void Text_box::render_box(const std::shared_ptr<Draw_2D> &r2)const{
        const float h=body->GetHeight();
        //bottom-right shadow
        r2->SetColor(RUtil::Colors::BLACK,SHADOW_A);
        r2->draw(s_tip_top, this->x + SHADOW_DIST_X, this->y - SHADOW_DIST_Y, BOX_W, BOX_EDGE_H);
        r2->draw(s_tip_mid, this->x + SHADOW_DIST_X, this->y - SHADOW_DIST_Y - h , BOX_W, h);
        r2->draw(s_tip_bot, this->x + SHADOW_DIST_X, this->y - SHADOW_DIST_Y - h , BOX_W, BOX_EDGE_H);
        r2->SetColor(-1);
        r2->draw(s_tip_top, this->x, this->y, BOX_W, BOX_EDGE_H);
        r2->draw(s_tip_mid, this->x, this->y - h, BOX_W, h);
        r2->draw(s_tip_bot, this->x, this->y - h , BOX_W, BOX_EDGE_H);
        //text
        title->render_top_left(r2, x + TEXT_OFFSET_X, y + HEADER_OFFSET_Y, Setting::SCALE);
        body->render_top_left(r2, x + TEXT_OFFSET_X, y + BODY_OFFSET_Y, Setting::SCALE);
    }
    
    const std::shared_ptr<ReTexture> &Text_box::s_tip_top=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipTop.png"),&Text_box::s_tip_mid=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipMid.png"),&Text_box::s_tip_bot=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipBot.png");
} // namespace RUtil
