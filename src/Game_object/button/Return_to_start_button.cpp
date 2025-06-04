#include "Game_object/button/Return_to_start_button.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"
#include "WindowSize.hpp"

namespace Button{
    Return_to_start_button::Return_to_start_button()
        :hb(240.0F*Setting::SCALE, 160.0F*Setting::SCALE),
        text(nullptr){}

    void Return_to_start_button::update(){
        hb.update();
    }

    void Return_to_start_button::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(hb.ClickStarted() ? RUtil::ToRGBA(RUtil::Colors::LIGHT_GRAY) : TEXT_NORMAL_COLOR, 1.0F);
        static auto&IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/buttonL.png");
        r2->draw(IMG, hb.CenterX()-256.0F, hb.CenterY()-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, Setting::SCALE, Setting::SCALE);
        if(text!=nullptr){
            text->SetFontSize(30);
            text->SetFontAlpha(1.0F);
            if(hb.ClickStarted()){
                text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::LIGHT_GRAY));
            }else{
                text->SetFontColor(TEXT_NORMAL_COLOR);   
            }
            text->render_center(r2, hb.CenterX(), hb.CenterY(), 0.0F, 0.0F, 0.0F, Setting::SCALE);
        }
    }
}