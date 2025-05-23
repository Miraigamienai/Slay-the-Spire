#include <vector>

#include "Draw/NumberDrawer.hpp"
#include "Draw/ReText.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/Draw_2D.hpp"

#include "Util/Logger.hpp"


namespace Draw{
    template <size_t N>
    static inline constexpr int strlen(const char (&str)[N]){
        //string is null-terminated ('\0' at the end)
        //the N will not be 0
        return N-1;
    }

    static void NumsLoader(FontWeight fw,std::vector<std::shared_ptr<Image_Region>>& vec){
        auto &font=Fonts::GetFont(fw);
        constexpr char data[]="01234\n56789\n/-+ ";
        std::shared_ptr<ReText> nums_text=std::make_shared<ReText>(font,data);
        int now_y=0,now_x=0;
        int img_w=0,img_h=0;
        for(int i=0;i<strlen(data);i++){
            if(data[i]=='\n'){
                now_x=0;
                now_y+=img_h;
            }else{
                const char str[2]={data[i],'\0'};
                TTF_SizeUTF8(font.get(),str,&img_w,&img_h);
                vec.emplace_back(std::make_shared<Draw::Image_Region>(nums_text, now_x, now_y, img_w, img_h));
                now_x+=img_w;
            }
        }
    }

    template <FontWeight fw>
    static const std::vector<std::shared_ptr<Image_Region>> &GetNums(){
        static const std::vector<std::shared_ptr<Image_Region>> nums=[](){
            std::vector<std::shared_ptr<Image_Region>> re;
            NumsLoader(fw,re);
            return re;
        }();
        return nums;
    }

    static inline const std::vector<std::shared_ptr<Image_Region>> &GetNums(FontWeight fw){
        switch(fw){
            case FontWeight::medium:return GetNums<FontWeight::medium>();
            case FontWeight::bold:return GetNums<FontWeight::bold>();
            default:return GetNums<FontWeight::regular>();
        }
    }

    const std::shared_ptr<Image_Region>&NumberDrawer::GetNumIMG(char c, FontWeight fw){
        if('0'<=c&&c<='9') return GetNums(fw)[c^48];
        if(c=='/') return GetNums(fw)[10];
        if(c=='-') return GetNums(fw)[11];
        if(c=='+') return GetNums(fw)[12];
        if(c==' ') return GetNums(fw)[13];
        LOG_ERROR("NumberDrawer can't draw '{}'",c);
        return GetNums(fw)[0];
    }

    const std::shared_ptr<Image_Region>&NumberDrawer::GetNumIMG(char c)const{
        if('0'<=c&&c<='9') return GetNums(fw)[c^48];
        if(c=='/') return GetNums(fw)[10];
        if(c=='-') return GetNums(fw)[11];
        if(c=='+') return GetNums(fw)[12];
        if(c==' ') return GetNums(fw)[13];
        LOG_ERROR("NumberDrawer can't draw '{}'",c);
        return GetNums(this->fw)[0];
    }

    void NumberDrawer::render_center(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float center_x,const float center_y,const float scale)const{
        const int width=PureWidth(num_str);
        const int height=GetNums(this->fw)[0]->GetRegionHeight();
        int now_x=0;
        const float offset_y=-(float)height/2.0F;
        for(const auto&it:num_str){
            const float offset_x=((float)now_x-(float)width/2.0F);
            auto& img=GetNumIMG(it);
            r2->draw(img, center_x+offset_x, center_y+offset_y, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, -offset_x, -offset_y, font_scale*scale, font_scale*scale);
            now_x+=img->GetRegionWidth();
        }
    }

    void NumberDrawer::render_center(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float center_x,const float center_y,const float angle,const float center_origin_x,const float center_origin_y,const float scale)const{
        // const int width=PureWidth(num_str);
        // const int height=GetNums(this->fw)[0]->GetRegionHeight();
        // for(const auto&it:num_str){
        //     const float offset_x=((float)(-it.img->GetRegionWidth())/2.0F)*font_scale;
        //     const float offset_y=((float)height/2.0F-(float)(it.y+it.img->GetRegionHeight()))*font_scale;
        //     r2->draw(it.img, center_x+offset_x, center_y+offset_y, (float)it.img->GetRegionWidth()*font_scale, (float)it.img->GetRegionHeight()*font_scale, angle, -offset_x+center_origin_x, -offset_y+center_origin_y, scale, scale);
        // }
    }

    void NumberDrawer::render_bot_right(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float right_x,const float y,const float scale)const{
        int now_x = -PureWidth(num_str);
        for(const auto&it:num_str){
            auto& img=GetNumIMG(it);
            r2->draw(img, right_x + (float)now_x, y, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, (float)(-now_x), 0.0F, font_scale*scale, font_scale*scale);
            now_x+=img->GetRegionWidth();
        }
    }
}