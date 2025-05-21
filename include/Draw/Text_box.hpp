#pragma once

#include <memory>

#include "WindowSize.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Text_layout.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
    class Draw_2D;
}

namespace Draw{
class Text_box
{
public:
    Text_box()noexcept:title(nullptr),body(nullptr){};
    Text_box(const std::shared_ptr<Text_layout> &title):title(title),body(nullptr){title->ChangeFontWeight(FontWeight::bold);}
    Text_box(const std::shared_ptr<Text_layout> &title, const std::shared_ptr<Text_layout> &body):title(title),body(body){title->ChangeFontWeight(FontWeight::bold);}
    ~Text_box()=default;
    void render(const std::shared_ptr<Draw_2D> &r2, float x, float y)const;
    void change_body(const std::shared_ptr<Text_layout> &body){this->body=body;}
    auto&get_body()const noexcept{return this->body;}
    auto&get_title()const noexcept{return this->title;}
private:
    void render_box(const std::shared_ptr<Draw_2D> &r2, float x, float y)const;
    std::shared_ptr<Text_layout> title,body;
    static const std::shared_ptr<ReTexture> &s_tip_top,&s_tip_mid,&s_tip_bot;
    static constexpr int SHADOW_A=64,TITLE_FONT_SIZE=23,BODY_FONT_SIZE=23;
    static constexpr Uint32 BASE_COLOR = RUtil::Math::GetColorUint32_RGB(1.0F, 0.9725F, 0.8745F);
    static constexpr float SHADOW_DIST_Y = 14.0F * Setting::SCALE,
                           SHADOW_DIST_X = 9.0F * Setting::SCALE,
                           BOX_BODY_H = 64.0F * Setting::SCALE,
                           BOX_W = 320.0F * Setting::SCALE,
                           TEXT_OFFSET_X = 22.0F *Setting::SCALE,
                           HEADER_OFFSET_Y = 12.0F * Setting::SCALE,
                           BODY_OFFSET_Y = -20.0F * Setting::SCALE;
public:
    static constexpr float BOX_EDGE_H = 32.0F * Setting::SCALE;
      
};
}