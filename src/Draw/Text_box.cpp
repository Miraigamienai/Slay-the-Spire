#include "Draw/Text_box.hpp"
#include "Draw/Text_layout.hpp"
#include "RUtil/ColorValuesOnly.hpp"//gold color
#include "RUtil/Image_book.hpp"//for loading img
#include "Draw/ReTexture.hpp"//img
#include "Draw/Draw_2D.hpp"//for rendering
namespace Draw
{
    Text_box::Text_box(const std::shared_ptr<Text_layout> &title,const std::shared_ptr<Text_layout> &body):title(title),body(body){
        title->ChangeFontWeight(FontWeight::bold);
    }

    void Text_box::render(const std::shared_ptr<Draw_2D> &r2, float x, float y)const{
        render_box(r2,x,y);
    }
    void Text_box::render_box(const std::shared_ptr<Draw_2D> &r2, float x, float y)const{
        const float h=body->GetHeight()*Setting::SCALE;
        //bottom-right shadow
        r2->SetColor(RUtil::Colors::BLACK,SHADOW_A);
        r2->draw(s_tip_top, x + SHADOW_DIST_X, y - SHADOW_DIST_Y, BOX_W, BOX_EDGE_H);
        r2->draw(s_tip_mid, x + SHADOW_DIST_X, y - SHADOW_DIST_Y - h - BOX_EDGE_H, BOX_W, h + BOX_EDGE_H);
        r2->draw(s_tip_bot, x + SHADOW_DIST_X, y - SHADOW_DIST_Y - h - BOX_BODY_H, BOX_W, BOX_EDGE_H);
        r2->SetColor(-1);
        r2->draw(s_tip_top, x, y, BOX_W, BOX_EDGE_H);
        r2->draw(s_tip_mid, x, y - h - BOX_EDGE_H, BOX_W, h + BOX_EDGE_H);
        r2->draw(s_tip_bot, x, y - h - BOX_BODY_H, BOX_W, BOX_EDGE_H);
        //text
        if(title!=nullptr){
            title->SetFontSize(TITLE_FONT_SIZE);
            title->SetFontColor(RUtil::GOLD_COLOR);
            title->render_top_left(r2, x + TEXT_OFFSET_X, y + HEADER_OFFSET_Y, Setting::SCALE);
        }
        if(body!=nullptr){
            body->SetFontSize(BODY_FONT_SIZE);
            body->SetFontColor(BASE_COLOR);    
            body->render_top_left(r2, x + TEXT_OFFSET_X, y + BODY_OFFSET_Y, Setting::SCALE);
        }
    }
    
    const std::shared_ptr<ReTexture> &Text_box::s_tip_top=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipTop.png"),&Text_box::s_tip_mid=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipMid.png"),&Text_box::s_tip_bot=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/tip/tipBot.png");
} // namespace RUtil
