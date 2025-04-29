#include <SDL_ttf.h>

#include "Draw/Text_layout_normal.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/ReText.hpp"
namespace Draw
{
    void Text_layout_normal::text_img_set(){
        text_rows.clear();//Ensure text_rows is empty.
        auto &font=Fonts::GetFont(this->fw);
        std::shared_ptr<ReText> ori_text_img=std::make_shared<ReText>(font,this->text);
        TTF_SizeUTF8(font.get(),this->text.c_str(),&this->width,&this->height);
        text_imgs.emplace_back(text_img{0,nullptr});
        auto nl_pos=this->text.find('\n');
        if(nl_pos==std::string::npos){
            text_imgs.back().img=std::make_shared<Image_Region>(ori_text_img, 0, 0, this->width, this->height);
            this->height*=2;
        }else{
            decltype(nl_pos) last_nl_pos=0;
            int now_y=0;
            int img_w=0,img_h=0;
            do{
                TTF_SizeUTF8(font.get(), this->text.substr(last_nl_pos, nl_pos-last_nl_pos).c_str(), &img_w, &img_h);

                text_imgs.back().img=std::make_shared<Image_Region>(ori_text_img, 0, now_y, img_w, img_h);
                now_y+=img_h;
                text_imgs.emplace_back(text_img{now_y,nullptr});
                last_nl_pos=nl_pos+1;
                nl_pos=this->text.find('\n', nl_pos+1);//find next
            }while(nl_pos!=std::string::npos);
            TTF_SizeUTF8(font.get(), this->text.substr(last_nl_pos).c_str(), &img_w, &img_h);  
            text_imgs.back().img=std::make_shared<Image_Region>(ori_text_img, 0, now_y, img_w, img_h);
            this->height=now_y+img_h;
        }

    }

    void Text_layout_normal::render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const{
        r2->SetColor(this->font_color, this->font_color_alpha);
        for(const auto&it:text_imgs){
            const float offset_x=((float)(-it.img->GetRegionWidth())/2.0F)*font_scale;
            const float offset_y=((float)height/2.0F-(float)(it.y+it.img->GetRegionHeight()))*font_scale;
            r2->draw(it.img, center_x+offset_x, center_y+offset_y, (float)it.img->GetRegionWidth()*font_scale, (float)it.img->GetRegionHeight()*font_scale, angle, -offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
        }
    }
    
    void Text_layout_normal::render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const{
        r2->SetColor(this->font_color, this->font_color_alpha);
        for(const auto&it:text_imgs){
            r2->draw(it.img, x, y-(float)(it.y+it.img->GetRegionHeight()), (float)it.img->GetRegionWidth(), (float)it.img->GetRegionHeight(), 0.0F, 0.0F, (float)(it.y+it.img->GetRegionHeight()), font_scale*scale, font_scale*scale);
        }
    }
} // namespace Draw
