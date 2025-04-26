#include <SDL_ttf.h>

#include "Draw/Text_layout_normal.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/ReText.hpp"

namespace Draw
{
    void Text_layout_normal::text_img_set(){
        auto &font=Fonts::GetFont(this->fw);
        std::shared_ptr<ReText> ori_text_img=std::make_shared<ReText>(font,this->text);
        TTF_SizeUTF8(font.get(),this->text.c_str(),&this->width,&this->height);
        this->text_img=std::make_shared<Image_Region>(ori_text_img, 0, 0, this->width, this->height);
        this->font_scale=Fonts::CalFontScale(this->fontsize,this->fw);
    }

    void Text_layout_normal::render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float origin_x,const float origin_y,const float scale)const{
        r2->draw(this->text_img, center_x-(float)this->width/2.0F, center_y-(float)this->height/2.0F, (float)this->width, (float)this->height, angle, (float)this->width/2.0F+origin_x, (float)this->height/2.0F+origin_y, scale*font_scale, scale*font_scale);
    }
    
    void Text_layout_normal::render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y)const{
        r2->draw(this->text_img, x, y-this->height, this->width, this->height, 0.0F, this->width/2.0F, this->height/2.0F, font_scale, font_scale);
    }
} // namespace Draw
