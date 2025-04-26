#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "Draw/Text_layout2.hpp"
#include "RUtil/ColorValuesOnly.hpp"

//fwd decl
namespace Draw{
    class Image_Region;
}

namespace Draw{
class Text_layout_color final:public Text_layout2
{
public:
    //$n:newline
    //#y:yellow #g:green #r:red #b:blue #p:purple
    Text_layout_color(const std::string &text):Text_layout2(text){text_rows_set();}
    ~Text_layout_color()override=default;

    void ChangeFontWeight(FontWeight fw)override{
        if(fw!=this->fw){
            this->fw=fw;
            text_rows_set();
        }
    }
    void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float origin_x,const float origin_y,const float scale)const override;
    void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y)const override;
private:
    struct text_img{
        int x;
        Uint32 c;
        std::shared_ptr<Image_Region> img;
    };
    struct text_row{
        int y;
        std::vector<text_img> row;
    };
    
    std::vector<text_row> text_rows;
    void text_rows_set();

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