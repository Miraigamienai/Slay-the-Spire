#pragma once

#include <memory>
#include <string>
#include <vector>

#include "WindowSize.hpp"
#include "Draw/Fonts.hpp"//inline
#include "RUtil/ColorValuesOnly.hpp"//WHITE

//fwd decl
namespace Draw{
    class Draw_2D;
}
enum class FontWeight:int;

namespace Draw{

enum class NumStatus{
    normal, up, down
};

struct number_info{
    int damage, defense, magic_number;
    NumStatus damage_status, defense_status, magic_status;
};
    
class Text_layout
{
public:
    Text_layout(const std::string &text):text(text){};
    virtual ~Text_layout()=default;
    

    virtual void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const=0;
    virtual void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const=0;
    virtual void render_center_with_nums(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale,const number_info &/* num_info */)const{
        render_center(r2, center_x, center_y, angle, center_origin_x, center_origin_y, scale);
    }
    virtual void ChangeFontWeight(FontWeight fw)=0;

    void SetFontSize(int fontsize){
        if(this->fontsize==fontsize) return;
        this->fontsize=fontsize;
        font_scale=Fonts::CalFontScale(fontsize,this->fw);
    }
    void SetFontAlpha(float a)noexcept{this->font_color_alpha=a;}
    void SetFontColor(Uint32 color)noexcept{this->font_color=color;}
    float GetWidth()const noexcept{return static_cast<float>(width)*font_scale;}
    float GetHeight()const noexcept{return static_cast<float>(height)*font_scale;}
protected:
    int width,height;
    std::string text;
    Uint32 font_color=RUtil::WHITE;
    float font_color_alpha=1.0F;
    float font_scale=1.0F;
    int fontsize=Setting::BIGGIST_SIZE;
    FontWeight fw=FontWeight::regular;

    static void replace(std::string &text, const char* from, const char* to);
    static std::vector<std::string> color_string_split(const std::string &text);
    static std::vector<std::string> num_tag_string_split(const std::string &text){return tag_string_split('!','!',text);}
    static std::vector<std::string> orb_string_split(const std::string &text){return tag_string_split('[',']',text);}
    static std::vector<std::string> tag_string_split(char front_char,char back_char,const std::string &text);
    static constexpr Uint32 GetColor(char c){
        switch(c){
            case 'y': return RUtil::GOLD_COLOR;
            case 'g': return RUtil::GREEN_TEXT_COLOR;
            case 'r': return RUtil::RED_TEXT_COLOR;
            case 'b': return RUtil::BLUE_TEXT_COLOR;
            case 'p': return RUtil::PURPLE_COLOR;
            default: return RUtil::WHITE;
        }
    }
};
}