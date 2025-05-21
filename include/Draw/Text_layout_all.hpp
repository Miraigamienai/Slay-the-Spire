#pragma once

#include "Draw/Text_layout.hpp"
#include "Draw/NumberDrawer.hpp"

namespace Draw{
class Text_layout_all final:public Text_layout
{
public:
    //$n:newline
    //#y:yellow #g:green #r:red #b:blue #p:purple
    //!D!:damage !B!:block !M!:magic_num
    //[R]:orb_red [G]:orb_green [B]:orb_blue [W]:orb_purple 
    //[C]:orb_card [P]:orb_potion [T]:orb_relic [S]:orb_special
    Text_layout_all(const std::string &text):Text_layout(text){set_member();};
    ~Text_layout_all()override=default;
    
    void set_member();
    void render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const override;
    void render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const override;
    void set_num_info(const number_info &num_info)override{this->num_info=num_info;}
private:
    struct text_item{
        bool is_num;
        bool is_orb;
        Uint32 c;//NOTE: when is_num is true,'c' represents the number type (e.g. damage, block, magic).
        std::shared_ptr<Image_Region> img;
    };

    struct text_row{
        int y;
        int img_row_width;
        std::vector<text_item> row;
    };

    NumberDrawer num_draw;
    std::vector<text_row> text_rows;
    number_info num_info;
    void calculate_width();
};
}