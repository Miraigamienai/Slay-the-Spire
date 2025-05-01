#pragma once

#include <vector>

#include "Draw/Text_layout.hpp"
#include "Draw/Fonts.hpp"//inline 

//fwd decl
namespace Draw{
    class Image_Region;
}

namespace Draw{
class Text_layout_normal final:public Text_layout
{
public:
    //$n:newline
    Text_layout_normal(const std::string &text):Text_layout(text){
        replace(this->text,"$n","\n");
        text_img_set();
    }
    ~Text_layout_normal()override=default;
    void ChangeFontWeight(FontWeight fw)override{
        if(fw!=this->fw){
            this->fw=fw;
            text_img_set();
            if(fontsize!=Setting::BIGGIST_SIZE) font_scale=Fonts::CalFontScale(fontsize,fw);
        }
    }
    void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const override;
    void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const override;
private:
    struct text_img{
        int y;
        std::shared_ptr<Image_Region> img;
    };
    std::vector<text_img> text_imgs;
    void text_img_set();
};
}