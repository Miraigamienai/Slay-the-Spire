#include "Draw/Text_layout_all.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReText.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"

#include "Util/Logger.hpp"

namespace Draw
{
    static inline auto&GetOrb(char c){
        switch (c){
            case 'R':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_red);
            case 'G':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_green);
            case 'B':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_blue);
            case 'W':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_purple);
            case 'C':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_card);
            case 'P':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_potion);
            case 'T':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_relic);
            case 'S':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_special);
            default:
                LOG_ERROR("The orb ID:\"{}\" dosen't exist.",c);
                return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_red);
        }
    }

    static inline Uint32 NumType(char c){
        switch(c){
            case 'D': return 1;
            case 'B': return 2;
            case 'M': return 3;
            default:
                LOG_ERROR("The num ID:\"{}\" dosen't exist.",c);
                return 1;
        }
    }

    static inline constexpr auto GetNum(Uint32 num_type, const number_info &num_info){
        switch(num_type){
            case 'D': return num_info.damage;
            case 'B': return num_info.defense;
            default: return num_info.magic_number;
        }
    }

    static inline constexpr auto GetNumColor(Uint32 num_type, const number_info &num_info){
        switch(num_type){
            case 'D': return Draw::GetNumColor(num_info.damage_status);
            case 'B': return Draw::GetNumColor(num_info.defense_status);
            default: return Draw::GetNumColor(num_info.magic_status);
        }
    }

    void Text_layout_all::render_top_left(const std::shared_ptr<Draw::Draw_2D> &/* r2 */,const float /* x */,const float /* y */,const float /* scale */)const{

    }

    void Text_layout_all::render_center(const std::shared_ptr<Draw_2D> &r2,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const{
        for(const auto&it:text_rows){
            if(it.row.empty()) continue;
            //calculate row width
            //Use float here because orbs may not have integer when scaled to match text.
            float row_width=static_cast<float>(it.img_row_width);
            for(const auto&it2:it.row){
                if(it2.is_num){
                    //add number width
                    row_width += static_cast<float>(num_draw.PureWidth(std::to_string(GetNum(it2.c, num_info))));
                }else if(it2.is_orb){
                    //add orb width
                    row_width += static_cast<float>(num_draw.PureHeight()) / static_cast<float>(it2.img->GetRegionHeight()) * static_cast<float>(it2.img->GetRegionWidth());
                }
            }
            //calculate offset_y
            const float offset_y=(static_cast<float>(height)/2.0F - static_cast<float>(it.y + it.row[0].img->GetRegionHeight()))*font_scale;
            float now_x=0.0F;
            for(const auto&it2:it.row){
                //calculate offset_x
                const float offset_x=(now_x-row_width/2.0F)*font_scale;
                if(it2.is_num){
                    //draw number
                    r2->SetColor(GetNumColor(it2.c, num_info), this->font_color_alpha);
                    auto the_number_str=std::to_string(GetNum(it2.c, num_info));
                    float num_offset_x=offset_x;
                    for(const auto &num_digit:the_number_str){
                        auto &img=num_draw.GetNumIMG(num_digit);
                        r2->draw(img, center_x+num_offset_x, center_y+offset_y, (float)img->GetRegionWidth()*font_scale, (float)img->GetRegionHeight()*font_scale, angle, -num_offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
                        now_x += (float)img->GetRegionWidth();
                        num_offset_x = (now_x-row_width/2.0F)*font_scale;
                    }
                }else if(it2.is_orb){
                    //draw orb
                    r2->SetColor(RUtil::WHITE, this->font_color_alpha);
                    const float orb_scale=static_cast<float>(num_draw.PureHeight()) / static_cast<float>(it2.img->GetRegionHeight()) * static_cast<float>(it2.img->GetRegionWidth());
                    r2->draw(it2.img, center_x+offset_x, center_y+offset_y, (float)it2.img->GetRegionWidth()*orb_scale*font_scale, (float)num_draw.PureHeight()*font_scale, angle, -offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
                    now_x+=(float)it2.img->GetRegionWidth()*orb_scale;
                }else{
                    
                    if(it2.c==RUtil::WHITE) r2->SetColor(this->font_color, this->font_color_alpha);
                    else r2->SetColor(it2.c, this->font_color_alpha);
                    r2->draw(it2.img, center_x+offset_x, center_y+offset_y, (float)it2.img->GetRegionWidth()*font_scale, (float)it2.img->GetRegionHeight()*font_scale, angle, -offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
                    now_x+=(float)it2.img->GetRegionWidth();
                }
            }
        }
    }

    void Text_layout_all::set_member(){
        text_rows.clear();//Ensure text_rows is empty.
        num_draw.ChangeFontWeight(this->fw);
        auto text_vec=color_string_split(this->text);
        //split number string
        for(int i=static_cast<int>(text_vec.size())-1;i>=0;--i){
            auto temp=num_tag_string_split(text_vec[i]);
            if(temp.size()>=2){
                text_vec[i]=std::move(temp[0]);
                text_vec.insert(text_vec.begin()+i+1,std::make_move_iterator(temp.begin()+1),std::make_move_iterator(temp.end()));
            }
        }
        //split orb string
        for(int i=static_cast<int>(text_vec.size())-1;i>=0;--i){
            
            auto temp=orb_string_split(text_vec[i]);
            if(temp.size()>=2){
                text_vec[i]=std::move(temp[0]);
                text_vec.insert(text_vec.begin()+i+1,std::make_move_iterator(temp.begin()+1),std::make_move_iterator(temp.end()));
            }
        }
        //get total string
        std::string total_text="";
        for(auto&it:text_vec){
            if(it.empty()) continue;
            if(it.size()==3 &&((it[0]=='[' && it[2]==']') || (it[0]=='!' && it[2]=='!'))) continue;
            if(it[0]!='#'){
                replace(it,"$n","\n");
                total_text+=it;
            }else{
                total_text+=it.substr(2);
            }
        }
        //get font
        auto &font=Fonts::GetFont(this->fw);
        //get total string texture
        std::shared_ptr<ReText> ori_text_img=std::make_shared<ReText>(font,total_text);
        //set texutres
        int now_y=0,now_x=0;
        int img_w=0,img_h=0;
        text_rows.emplace_back(text_row{now_y, 0, {}});
        for(const auto&it:text_vec){
            if(it.empty())continue;
            
            if(it[0]=='!' && it.size()==3 && it[2]=='!'){
                //num string
                text_rows.back().row.emplace_back(text_item{true, false, NumType(it[1]), nullptr});
            }else if(it[0]=='[' && it.size()==3 && it[2]==']'){
                //orb string
                text_rows.back().row.emplace_back(text_item{false, true, RUtil::WHITE, GetOrb(it[1])});
            }else if(it[0]=='#' && it.size()>=3){
                //color string
                TTF_SizeUTF8(font.get(), it.substr(2).c_str(), &img_w, &img_h);
                text_rows.back().row.emplace_back(text_item{false, false, GetColor(it[1]), std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                now_x+=img_w;
            }else{
                //normal string
                auto nl_pos=it.find('\n');
                if(nl_pos==std::string::npos){
                    TTF_SizeUTF8(font.get(), it.c_str(), &img_w, &img_h);
                    text_rows.back().row.emplace_back(text_item{false, false, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                    now_x+=img_w;
                }else{
                    decltype(nl_pos) last_nl_pos=0;
                    do{
                        TTF_SizeUTF8(font.get(), it.substr(last_nl_pos, nl_pos-last_nl_pos).c_str(), &img_w, &img_h);
                        text_rows.back().row.emplace_back(text_item{false, false, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                        text_rows.back().img_row_width=now_x+img_w;//set previous img row width.
                        now_y+=img_h;
                        now_x=0;
                        text_rows.emplace_back(text_row{now_y, 0, {}});//new row
                        last_nl_pos=nl_pos+1;
                        nl_pos=it.find('\n', last_nl_pos);//find next
                    }while(nl_pos!=std::string::npos);
                    TTF_SizeUTF8(font.get(), it.substr(last_nl_pos).c_str(), &img_w, &img_h);   
                    text_rows.back().row.emplace_back(text_item{false, false, RUtil::WHITE, std::make_shared<Image_Region>(ori_text_img, now_x, now_y, img_w, img_h)});
                    now_x+=img_w;
                }
            }
        }
        //set last img row width.
        text_rows.back().img_row_width=now_x+img_w;
        //set width & height
        this->height=now_y+img_h;
        this->calculate_width();
    }

    void Text_layout_all::calculate_width(){
        width=0;
        for(const auto&it1:text_rows){
            float now_w=0;
            for(const auto&it2:it1.row){
                if(it2.is_num){
                    now_w += static_cast<float>(num_draw.PureWidth(GetNum(it2.c, num_info)));
                }else if(it2.is_orb){
                    const float orb_scale=static_cast<float>(num_draw.PureHeight()) / static_cast<float>(it2.img->GetRegionHeight()) * static_cast<float>(it2.img->GetRegionWidth());
                    now_w += (float)it2.img->GetRegionWidth()*orb_scale;
                }else{
                    now_w += (float)it2.img->GetRegionWidth();
                }
            }
            if(now_w>width)
                width=now_w;
        }
    }
} // namespace Draw
