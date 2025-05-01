#include "Draw/Text_layout_color.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReText.hpp"

namespace Draw
{ 
    void Text_layout_color::render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const{
        for(const auto&it:text_rows){
            if(it.row.empty()) continue;
            const float offset_y=((float)height/2.0F - (float)(it.y + it.row[0].img->GetRegionHeight()))*font_scale;
            for(const auto&it2:it.row){
                if(it2.c==RUtil::WHITE) r2->SetColor(this->font_color, this->font_color_alpha);
                else r2->SetColor(it2.c, this->font_color_alpha);
                const float offset_x=((float)it2.x-(float)it.row_width/2.0F)*font_scale;
                r2->draw(it2.img, center_x+offset_x, center_y+offset_y, (float)it2.img->GetRegionWidth()*font_scale, (float)it2.img->GetRegionHeight()*font_scale, angle, -offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
            }
        }
    }
    void Text_layout_color::render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y,const float scale)const{
        for(const auto&it:text_rows){
            for(const auto&it2:it.row){
                if(it2.c==RUtil::WHITE) r2->SetColor(this->font_color, this->font_color_alpha);
                else r2->SetColor(it2.c, this->font_color_alpha);
                r2->draw(it2.img, x+(float)it2.x, y-(float)(it.y+it2.img->GetRegionHeight()), (float)it2.img->GetRegionWidth(), (float)it2.img->GetRegionHeight(), 0.0F, (float)(-it2.x), (float)(it.y + it2.img->GetRegionHeight()), font_scale*scale, font_scale*scale);
            }
        }
    }

    void Text_layout_color::text_rows_set(){
        text_rows.clear();//Ensure text_rows is empty.
        auto text_vec=color_string_split(this->text);
        //if "$n" appears inside a color tag text, that "$n" will be ignored.
        std::string total_text="";
        for(auto&it:text_vec){
            if(it.empty()) continue;
            if(it[0]!='#'){
                replace(it,"$n","\n");
                total_text+=it;
            }else{
                total_text+=it.substr(2);
            }
        }


        auto &font=Fonts::GetFont(this->fw);
        std::shared_ptr<ReText> ori_text_img=std::make_shared<ReText>(font,total_text);
        int now_y=0,now_x=0;
        int img_w=0,img_h=0;
        text_rows.emplace_back(text_row{now_y,0,{}});
        for(const auto&it:text_vec){
            if(it.empty()) continue;
            if(it[0]=='#'&&it.size()>3){
                TTF_SizeUTF8(font.get(), it.substr(2).c_str(), &img_w, &img_h);
                text_rows.back().row.emplace_back(text_img{now_x, GetColor(it[1]), std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                now_x+=img_w;
            }else{ 
                auto nl_pos=it.find('\n');
                if(nl_pos==std::string::npos){
                    TTF_SizeUTF8(font.get(), it.c_str(), &img_w, &img_h);
                    text_rows.back().row.emplace_back(text_img{now_x, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                    now_x+=img_w;
                }else{
                    decltype(nl_pos) last_nl_pos=0;
                    do{
                        TTF_SizeUTF8(font.get(), it.substr(last_nl_pos, nl_pos-last_nl_pos).c_str(), &img_w, &img_h);
                        text_rows.back().row.emplace_back(text_img{now_x, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                        text_rows.back().row_width=now_x+img_w;//set previous row width.
                        now_y+=img_h;
                        now_x=0;
                        text_rows.emplace_back(text_row{now_y,0,{}});//new row
                        last_nl_pos=nl_pos+1;
                        nl_pos=it.find('\n', last_nl_pos);//find next
                    }while(nl_pos!=std::string::npos);
                    TTF_SizeUTF8(font.get(), it.substr(last_nl_pos).c_str(), &img_w, &img_h);   
                    text_rows.back().row.emplace_back(text_img{now_x, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                    now_x+=img_w;
                }
            }
        }
        text_rows.back().row_width=now_x+img_w;//set last row width.
                        
        //set width & height
        this->height=now_y+img_h;
        this->width=0;
        for(const auto&it:text_rows)
            if(width<it.row_width) width=it.row_width;
    }
} // namespace Draw

// 全形 32 半形 18 半形空白 7