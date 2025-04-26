#include "Draw/Text_layout_color.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReText.hpp"

namespace Draw
{ 
    void Text_layout_color::render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float origin_x,const float origin_y,const float scale)const{

    }
    void Text_layout_color::render_top_left(const std::shared_ptr<Draw::Draw_2D> &r2,const float x,const float y)const{
        
    }

    void Text_layout_color::text_rows_set(){
        text_rows.clear();//Ensure text_rows is empty.
        auto text_vec=color_string_split(text);

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
        std::shared_ptr<ReText> ori_text_img=std::make_shared<ReText>(font,this->text);
        int now_y=0,now_x=0;
        int img_w=0,img_h=0;
        text_rows.emplace_back(text_row{0,{}});
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
                        now_y+=img_h;
                        now_x=0;
                        text_rows.emplace_back(text_row{0,{}});//new line
                        last_nl_pos=nl_pos;
                        nl_pos=it.find('\n', nl_pos+1);//find next
                    }while(nl_pos!=std::string::npos);
                    TTF_SizeUTF8(font.get(), it.substr(last_nl_pos+1).c_str(), &img_w, &img_h);   
                    text_rows.back().row.emplace_back(text_img{now_x, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                    now_x+=img_w;
                }
            }
        }
        
        //set width & height
        this->height=now_y+img_h;
        this->width=0;
        for(const auto&it:text_rows){
            int row_width = it.row.back().x + it.row.back().img->GetRegionWidth();
            if(width<row_width) width=row_width;
        }
    }
} // namespace Draw
