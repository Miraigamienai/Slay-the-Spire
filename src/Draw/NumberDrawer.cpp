#include <vector>

#include "Draw/NumberDrawer.hpp"
#include "Draw/ReText.hpp"
#include "Draw/Image_Region.hpp"
#include "Draw/Draw_2D.hpp"

#include "Util/Logger.hpp"


namespace Draw{
    static void NumsLoader(FontWeight fw,std::vector<std::shared_ptr<Image_Region>>& vec){
        auto &font=Fonts::GetFont(fw);
        constexpr auto data="01234\n56789/";
        std::shared_ptr<ReText> nums_text=std::make_shared<ReText>(font,data);
        int now_y=0,now_x=0;
        int img_w=0,img_h=0;
        for(int i=0;i<12;i++){
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

    const std::shared_ptr<Image_Region>&NumberDrawer::GetNumIMG(char c)const{
        if('0'<=c&&c<='9')
            return GetNums(this->fw)[c^48];
        if(c=='/')
            return GetNums(this->fw)[10];
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
}