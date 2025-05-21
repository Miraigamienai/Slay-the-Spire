#pragma once

#include <vector>

#include "Draw/Text_layout.hpp"

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
        set_member();
    }
    ~Text_layout_normal()override=default;
    void set_member()override;
    void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const override;
    void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const override;
private:
    struct text_img{
        int y;
        std::shared_ptr<Image_Region> img;
    };
    std::vector<text_img> text_imgs;
};
}