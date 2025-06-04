#include <GL/glew.h>//blend func
#include <array>

#include "Game_object/button/Menu_button.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Text_layout.hpp"
#include "WindowSize.hpp"

namespace Button{
    static SETTING_CONSTEXPR float FONT_X = 120.0F * Setting::SCALE,
                                   START_Y = 120.0F * Setting::SCALE,
                                   SPACE_Y = 50.0F * Setting::SCALE;
        
    static constexpr auto text_id_convert=[]()constexpr{
        std::array<int, static_cast<int>(MenuButtonType::quit)+1> temp{};
        temp[static_cast<int>(MenuButtonType::play)] = 1;
        temp[static_cast<int>(MenuButtonType::info)] = 14;
        temp[static_cast<int>(MenuButtonType::stat)] = 6;
        temp[static_cast<int>(MenuButtonType::setting)] = 12;
        temp[static_cast<int>(MenuButtonType::patch_notes)] = 9;
        temp[static_cast<int>(MenuButtonType::quit)] = 8;
        return temp;
    }();

    static inline auto&TEXT(MenuButtonType type){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::MenuButton)[text_id_convert[static_cast<int>(type)]];
    }
    
    Menu_button::Menu_button(MenuButtonType type, int index):
        type(type),
        hb((TEXT(type)->SetFontSize(FONTSIZE), TEXT(type)->GetWidth()*Setting::SCALE + 100.0F*Setting::SCALE), SPACE_Y),
        x(0.0F),
        target_x(0.0F),
        highlight_a(0.0F)
    {
        hb.move(hb.Width()/2.0F+75.0F*Setting::SCALE, START_Y+static_cast<float>(index)*SPACE_Y);
    }

    void Menu_button::update(){
        if(x!=target_x)
            x = RUtil::Math::varlerp(x, target_x, 9.0F, Setting::SCALE);
        hb.update();
        if(hb.Hovered()){
            highlight_a=0.9F;
            target_x=25.0F*Setting::SCALE;
        }else{
            highlight_a=RUtil::Math::fadelerp(highlight_a, 0.0F);
            target_x=0.0F;
        }
    }

    void Menu_button::render(const std::shared_ptr<Draw::Draw_2D> &r2, bool activate)const{
        if(activate){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE, highlight_a);
            r2->draw(HIGHLIGHT_IMG, this->x + FONT_X + 120.0F*Setting::SCALE - 179.0F, hb.CenterY() - 52.0F, 358.0F, 104.0F, 0.0F, 179.0F, 52.0F, Setting::SCALE, Setting::SCALE*0.8F);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }else{
            r2->SetColor(RUtil::BLACK, 1.0F);
            r2->draw(HIGHLIGHT_IMG, FONT_X + 120.0F*Setting::SCALE - 179.0F, hb.CenterY() - 52.0F, 358.0F, 104.0F, 0.0F, 179.0F, 52.0F, Setting::SCALE, Setting::SCALE*0.8F);
        }

        auto &text=TEXT(type);
        text->ChangeFontWeight(FontWeight::bold);
        text->SetFontSize(FONTSIZE);
        if(activate) text->SetFontColor(RUtil::CREAM_COLOR);
        else text->SetFontColor(RUtil::ToRGBA(RUtil::Colors::DARK_RED));
        text->SetFontAlpha(1.0F);

        text->render_center(r2, hb.CenterX() + (activate ? x : 0.0F), hb.CenterY(), 0.0F, 0.0F, 0.0F, Setting::SCALE);
    }

    const std::shared_ptr<Draw::ReTexture> &Menu_button::HIGHLIGHT_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/startScreen/menu_option_highlight.png");
}