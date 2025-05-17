#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "Draw/Text_layout.hpp"
#include "RUtil/ColorValuesOnly.hpp"

//fwd decl
namespace Draw{
    class Image_Region;
}

namespace Draw{
class Text_layout_color final:public Text_layout
{
public:
    //$n:newline
    //#y:yellow #g:green #r:red #b:blue #p:purple
    Text_layout_color(const std::string &text):Text_layout(text){set_member();}
    ~Text_layout_color()override=default;
    void set_member()override;
    void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const override;
    void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const override;
private:
    struct text_img{
        int x;
        Uint32 c;
        std::shared_ptr<Image_Region> img;
    };
    struct text_row{
        int y;
        int row_width;
        std::vector<text_img> row;
    };
    
    std::vector<text_row> text_rows;
};
}